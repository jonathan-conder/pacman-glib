/* pacman-install.c
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

#include <stdlib.h>
#include <glib/gi18n-lib.h>
#include <alpm.h>
#include "pacman-error.h"
#include "pacman-list.h"
#include "pacman-missing-dependency.h"
#include "pacman-conflict.h"
#include "pacman-file-conflict.h"
#include "pacman-package.h"
#include "pacman-private.h"
#include "pacman-install.h"

/**
 * SECTION:pacman-install
 * @title: PacmanInstall
 * @short_description: Install packages from files
 *
 * A #PacmanInstall transaction can be used to install packages from local or remote files (equivalent to pacman -U). To do so, pass a list of file locations and/or URLs as targets to pacman_transaction_prepare(). Currently, missing dependencies for these packages will not be installed automatically.
 */

/**
 * PacmanInstall:
 *
 * Represents an installation transaction.
 */

G_DEFINE_TYPE (PacmanInstall, pacman_install, PACMAN_TYPE_TRANSACTION);

static void pacman_install_init (PacmanInstall *install) {	
	g_return_if_fail (install != NULL);
}

static void pacman_install_finalize (GObject *object) {
	g_return_if_fail (object != NULL);
	
	G_OBJECT_CLASS (pacman_install_parent_class)->finalize (object);
}

/**
 * pacman_manager_install:
 * @manager: A #PacmanManager.
 * @flags: A set of #PacmanTransactionFlags.
 * @error: A #GError, or %NULL.
 *
 * Initializes a transaction that can install packages from files, configured according to @flags.
 *
 * Returns: A #PacmanInstall transaction, or %NULL if @error is set. Free with g_object_unref().
 */
PacmanTransaction *pacman_manager_install (PacmanManager *manager, guint32 flags, GError **error) {
	PacmanTransaction *result;
	
	g_return_val_if_fail (manager != NULL, NULL);
	
	if (!pacman_transaction_start (PM_TRANS_TYPE_UPGRADE, flags, error)) {
		return NULL;
	}
	
	return pacman_manager_new_transaction (manager, PACMAN_TYPE_INSTALL);
}

static gboolean pacman_install_prepare (PacmanTransaction *transaction, const PacmanList *targets, GError **error) {
	const PacmanList *i;
	PacmanList *data = NULL;
	
	g_return_val_if_fail (transaction != NULL, FALSE);
	g_return_val_if_fail (targets != NULL, FALSE);
	
	if (pacman_transaction_get_packages (transaction) != NULL) {
		/* reinitialize so transaction can be prepared multiple times */
		if (!pacman_transaction_restart (transaction, error)) {
			return FALSE;
		}
	}
	
	for (i = targets; i != NULL; i = pacman_list_next (i)) {
		int result;
		gchar *target = (gchar *) pacman_list_get (i);
		
		if (strstr (target, "://") != NULL) {
			target = alpm_fetch_pkgurl (target);
			if (target == NULL) {
				g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not download package with url '%s': %s"), (gchar *) pacman_list_get (i), alpm_strerrorlast ());
				return FALSE;
			}
			
			result = alpm_trans_addtarget (target);
			free (target);
		} else {
			result = alpm_trans_addtarget (target);
		}
		
		if (result < 0) {
			g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not mark the file '%s' for installation: %s"), target, alpm_strerrorlast ());
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
			/* TODO: offer option to sync dependencies first? (like makepkg -s) */
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
		} else if (pm_errno == PACMAN_ERROR_FILE_CONFLICT) {
			gchar *conflict = pacman_file_conflict_make_list (data);
			pacman_transaction_set_file_conflicts (transaction, data);
			
			g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not prepare transaction: %s"), conflict);
			g_free (conflict);
			return FALSE;
		} else if (data != NULL) {
			g_debug ("Possible memory leak for install error: %s\n", alpm_strerrorlast ());
		}
		
		g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not prepare transaction: %s"), alpm_strerrorlast ());
		return FALSE;
	}
	
	return TRUE;
}

static void pacman_install_class_init (PacmanInstallClass *klass) {
	g_return_if_fail (klass != NULL);
	
	G_OBJECT_CLASS (klass)->finalize = pacman_install_finalize;
	
	PACMAN_TRANSACTION_CLASS (klass)->prepare = pacman_install_prepare;
}
