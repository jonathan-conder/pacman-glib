/* pacman-remove.c
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
#include "pacman-manager.h"
#include "pacman-private.h"
#include "pacman-remove.h"

/**
 * SECTION:pacman-remove
 * @title: PacmanRemove
 * @short_description: Remove packages
 *
 * A #PacmanRemove transaction can be used to remove packages from the system (equivalent to pacman -R). To do so, pass a list of package and/or group names as targets to pacman_transaction_prepare(). If some of those packages are marked as HoldPkg, the operation will fail unless the user agrees to %PACMAN_TRANSACTION_QUESTION_REMOVE_HOLD_PACKAGES.
 */

/**
 * PacmanRemove:
 *
 * Represents a remove transaction.
 */

G_DEFINE_TYPE (PacmanRemove, pacman_remove, PACMAN_TYPE_TRANSACTION);

static void pacman_remove_init (PacmanRemove *remove) {
	g_return_if_fail (remove != NULL);
}

static void pacman_remove_finalize (GObject *object) {
	g_return_if_fail (object != NULL);
	
	G_OBJECT_CLASS (pacman_remove_parent_class)->finalize (object);
}

/**
 * pacman_manager_remove:
 * @manager: A #PacmanManager.
 * @flags: A set of #PacmanTransactionFlags.
 * @error: A #GError, or %NULL.
 *
 * Initializes a transaction that can remove packages from the system, configured according to @flags.
 *
 * Returns: A #PacmanRemove transaction, or %NULL if @error is set. Free with g_object_unref().
 */
PacmanTransaction *pacman_manager_remove (PacmanManager *manager, guint32 flags, GError **error) {
	PacmanTransaction *result;
	
	g_return_val_if_fail (manager != NULL, NULL);
	
	if (!pacman_transaction_start (flags, error)) {
		return NULL;
	}
	
	return pacman_manager_new_transaction (manager, PACMAN_TYPE_REMOVE);
}

static gboolean pacman_remove_prepare (PacmanTransaction *transaction, const PacmanList *targets, GError **error) {
	const PacmanList *i;
	PacmanList *data = NULL;
	
	g_return_val_if_fail (transaction != NULL, FALSE);
	g_return_val_if_fail (targets != NULL, FALSE);
	g_return_val_if_fail (pacman_manager != NULL, FALSE);
	
	if (pacman_transaction_get_removes (transaction) != NULL) {
		/* reinitialize so transaction can be prepared multiple times */
		if (!pacman_transaction_restart (transaction, error)) {
			return FALSE;
		}
	}
	
	for (i = targets; i != NULL; i = pacman_list_next (i)) {
		const gchar *target = (const gchar *) pacman_list_get (i);
		
		if (alpm_remove_target ((gchar *) target) < 0) {
			g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not mark the package %s for removal: %s"), target, alpm_strerrorlast ());
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
		} else if (data != NULL) {
			g_debug ("Possible memory leak for remove error: %s\n", alpm_strerrorlast ());
		}
		
		g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not prepare transaction: %s"), alpm_strerrorlast ());
		return FALSE;
	}
	
	for (i = pacman_transaction_get_removes (transaction); i != NULL; i = pacman_list_next (i)) {
		PacmanPackage *package = (PacmanPackage *) pacman_list_get (i);
		const gchar *name = pacman_package_get_name (package);
		
		if (pacman_list_find_string (pacman_manager_get_hold_packages (pacman_manager), name) != NULL) {
			pacman_transaction_mark_package (transaction, package);
		}
	}
	
	if (pacman_transaction_get_marked_packages (transaction) != NULL) {
		gchar *packages = pacman_package_make_list (pacman_transaction_get_marked_packages (transaction));
		gboolean result = pacman_transaction_ask (transaction, PACMAN_TRANSACTION_QUESTION_REMOVE_HOLD_PACKAGES, _("The following packages are marked as held: %s. Do you want to remove them anyway?"), packages);
		pacman_transaction_set_marked_packages (transaction, NULL);
		
		if (!result) {
			g_set_error (error, PACMAN_ERROR, PACMAN_ERROR_PACKAGE_HELD, _("The following packages were marked as held: %s."), packages);
			g_free (packages);
			return FALSE;
		}
		g_free (packages);
	}
	
	return TRUE;
}

static void pacman_remove_class_init (PacmanRemoveClass *klass) {
	g_return_if_fail (klass != NULL);
	
	G_OBJECT_CLASS (klass)->finalize = pacman_remove_finalize;
	
	PACMAN_TRANSACTION_CLASS (klass)->prepare = pacman_remove_prepare;
}
