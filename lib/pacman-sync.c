/* pacman-sync.c
 *
 * Copyright (C) 2010 Jonathan Conder <j@skurvy.no-ip.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib/gi18n-lib.h>
#include <alpm.h>
#include "pacman-error.h"
#include "pacman-list.h"
#include "pacman-package.h"
#include "pacman-group.h"
#include "pacman-database.h"
#include "pacman-missing-dependency.h"
#include "pacman-conflict.h"
#include "pacman-file-conflict.h"
#include "pacman-manager.h"
#include "pacman-private.h"
#include "pacman-sync.h"

/**
 * SECTION:pacman-sync
 * @title: PacmanSync
 * @short_description: Install packages
 *
 * A #PacmanSync transaction can be used to install packages from a database (equivalent to pacman -S). To do so, pass a list of package and/or group names as targets to pacman_transaction_prepare(). Alternatively, pass an empty list to mark outdated packages for upgrade (equivalent to pacman -Su). If some of those packages are marked as SyncFirst, then others will be ignored if the user agrees to %PACMAN_TRANSACTION_QUESTION_SYNC_FIRST.
 */

/**
 * PacmanSync:
 *
 * Represents a sync transaction.
 */

G_DEFINE_TYPE (PacmanSync, pacman_sync, PACMAN_TYPE_TRANSACTION);

static void pacman_sync_init (PacmanSync *sync) {
	g_return_if_fail (sync != NULL);
}

static void pacman_sync_finalize (GObject *object) {
	g_return_if_fail (object != NULL);
	
	G_OBJECT_CLASS (pacman_sync_parent_class)->finalize (object);
}

/**
 * pacman_manager_sync:
 * @manager: A #PacmanManager.
 * @flags: A set of #PacmanTransactionFlags.
 * @error: A #GError, or %NULL.
 *
 * Initializes a transaction that can install packages from sync databases, configured according to @flags.
 *
 * Returns: A #PacmanSync transaction, or %NULL if @error is set. Free with g_object_unref().
 */
PacmanTransaction *pacman_manager_sync (PacmanManager *manager, guint32 flags, GError **error) {
	PacmanTransaction *result;
	
	g_return_val_if_fail (manager != NULL, NULL);
	
	if (!pacman_transaction_start (PM_TRANS_TYPE_SYNC, flags, error)) {
		return NULL;
	}
	
	return pacman_manager_new_transaction (manager, PACMAN_TYPE_SYNC);
}

static gboolean pacman_sync_real_prepare (PacmanTransaction *transaction, const PacmanList *targets, GError **error, gboolean ask_sync_first) {
	const PacmanList *i;
	PacmanList *data = NULL;
	
	g_return_val_if_fail (transaction != NULL, FALSE);
	g_return_val_if_fail (pacman_manager != NULL, FALSE);
	
	if (pacman_transaction_get_packages (transaction) != NULL) {
		/* reinitialize so transaction can be prepared multiple times */
		if (!pacman_transaction_restart (transaction, error)) {
			return FALSE;
		}
	}
	
	if (targets != NULL) {
		for (i = targets; i != NULL; i = pacman_list_next (i)) {
			const gchar *target = (const gchar *) pacman_list_get (i);
			
			if (alpm_trans_addtarget ((gchar *) target) < 0) {
				if (pm_errno == PACMAN_ERROR_TRANSACTION_DUPLICATE_TARGET || pm_errno == PACMAN_ERROR_PACKAGE_IGNORED) {
					/* don't get in a tizzy over this */
					target = NULL;
				} else if (pm_errno == PACMAN_ERROR_PACKAGE_NOT_FOUND) {
					const PacmanList *j;
					for (j = pacman_manager_get_sync_databases (pacman_manager); j != NULL; j = pacman_list_next (j)) {
						PacmanDatabase *database = (PacmanDatabase *) pacman_list_get (j);
						PacmanGroup *group = pacman_database_find_group (database, target);
						
						if (group != NULL) {
							const PacmanList *k;
							for (k = pacman_group_get_packages (group); k != NULL; k = pacman_list_next (k)) {
								PacmanPackage *package = (PacmanPackage *) pacman_list_get (k);
								target = pacman_package_get_name (package);
								
								if (alpm_trans_addtarget ((gchar *) target) < 0) {
									/* report error further down */
									break;
								}
							}
							
							if (k == NULL) {
								/* added all packages in group */
								target = NULL;
								break;
							}
						}
					}
				}
				
				if (target == NULL) {
					/* something handled it above */
					continue;
				}
				
				g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not mark the package '%s' for installation: %s"), target, alpm_strerrorlast ());
				return FALSE;
			}
		}
	} else {
		/* TODO: provide an option to do alpm_logaction ("starting full system upgrade\n");*/
		if (alpm_trans_sysupgrade ((pacman_transaction_get_flags (transaction) & PACMAN_TRANSACTION_FLAGS_SYNC_ALLOW_DOWNGRADE) != 0) < 0) {
			g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not prepare transaction: %s"), alpm_strerrorlast ());
			return FALSE;
		}
	}
	
	if (alpm_trans_prepare (&data) < 0) {
		if (pm_errno == PACMAN_ERROR_PACKAGE_WRONG_ARCHITECTURE) {
			gchar *packages = pacman_package_make_list (data);
			pacman_transaction_set_marked_packages (transaction, data);
			
			g_set_error (error, PACMAN_ERROR, pm_errno, _("The following packages have the wrong architecture: %s"), packages);
			g_free (packages);
			return FALSE;
		} else if (pm_errno == PACMAN_ERROR_DEPENDENCY_UNSATISFIED) {
			gchar *missing = pacman_missing_dependency_make_list (data);
			pacman_transaction_set_missing_dependencies (transaction, data);
			
			g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not prepare transaction: %s"), missing);
			g_free (missing);
			return FALSE;
		} else if (pm_errno == PACMAN_ERROR_CONFLICT) {
			gchar *conflict = pacman_conflict_make_list (data);
			pacman_transaction_set_conflicts (transaction, data);
			
			g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not prepare transaction: %s"), conflict);
			g_free (conflict);
			return FALSE;
		} else if (data != NULL) {
			g_debug ("Possible memory leak for sync error: %s\n", alpm_strerrorlast ());
		}
		
		g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not prepare transaction: %s"), alpm_strerrorlast ());
		return FALSE;
	}
	
	/* slightly different behaviour to pacman */
	if (ask_sync_first) {
		PacmanList *sync_firsts = NULL;
		ask_sync_first = FALSE;
		
		for (i = pacman_transaction_get_packages (transaction); i != NULL; i = pacman_list_next (i)) {
			PacmanPackage *package = (PacmanPackage *) pacman_list_get (i);
			const gchar *name = pacman_package_get_name (package);
		
			if (pacman_list_find_string (pacman_manager_get_sync_firsts (pacman_manager), name) != NULL) {
				sync_firsts = pacman_list_add (sync_firsts, (gchar *) name);
				pacman_transaction_mark_package (transaction, package);
			} else {
				/* not everything is in SyncFirst */
				ask_sync_first = TRUE;
			}
		}
		
		if (sync_firsts != NULL) {
			if (ask_sync_first) {
				gchar *packages = pacman_package_make_list (pacman_transaction_get_marked_packages (transaction));
				gboolean result = pacman_transaction_ask (transaction, PACMAN_TRANSACTION_QUESTION_SYNC_FIRST, _("The following packages are marked as sync first: %s. Do you want to cancel the transaction and install them now?"), packages);
				pacman_transaction_set_marked_packages (transaction, NULL);
				g_free (packages);
				
				if (result) {
					result = pacman_sync_real_prepare (transaction, sync_firsts, error, FALSE);
					pacman_list_free (sync_firsts);
					return result;
				}
			} else {
				pacman_transaction_set_marked_packages (transaction, NULL);
			}
			pacman_list_free (sync_firsts);
		}
	}
	
	return TRUE;
}

static gboolean pacman_sync_prepare (PacmanTransaction *transaction, const PacmanList *targets, GError **error) {
	return pacman_sync_real_prepare (transaction, targets, error, TRUE);
}

static gchar *pacman_file_make_list (const PacmanList *files) {
	GString *result;
	const PacmanList *i;
	
	result = g_string_new (_("Invalid files:"));
	
	for (i = files; i != NULL; i = pacman_list_next (i)) {
		const gchar *file = (const gchar *) pacman_list_get (i);
		g_string_append_printf (result, _("\n%s"), file);
	}
	
	return g_string_free (result, FALSE);
}

static gboolean pacman_sync_commit (PacmanTransaction *transaction, GError **error) {
	PacmanList *data;
	
	g_return_val_if_fail (transaction != NULL, FALSE);
	
	if (alpm_trans_commit (&data) < 0) {
		if (pm_errno == PACMAN_ERROR_FILE_CONFLICT) {
			gchar *conflict = pacman_file_conflict_make_list (data);
			pacman_transaction_set_file_conflicts (transaction, data);
			
			g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not commit transaction: %s"), conflict);
			g_free (conflict);
			return FALSE;
		} else if (pm_errno == PACMAN_ERROR_PACKAGE_INVALID || pm_errno == PACMAN_ERROR_DELTA_INVALID) {
			gchar *file = pacman_file_make_list (data);
			pacman_transaction_set_invalid_files (transaction, data);
			
			g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not commit transaction: %s"), file);
			g_free (file);
			return FALSE;
		}
		
		g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not commit transaction: %s"), alpm_strerrorlast ());
		return FALSE;
	}
	
	return TRUE;
}

static void pacman_sync_class_init (PacmanSyncClass *klass) {
	g_return_if_fail (klass != NULL);
	
	G_OBJECT_CLASS (klass)->finalize = pacman_sync_finalize;
	
	PACMAN_TRANSACTION_CLASS (klass)->prepare = pacman_sync_prepare;
	PACMAN_TRANSACTION_CLASS (klass)->commit = pacman_sync_commit;
}
