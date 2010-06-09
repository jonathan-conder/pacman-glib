/* pacman-modify.c
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
#include "pacman-database.h"
#include "pacman-manager.h"
#include "pacman-private.h"
#include "pacman-modify.h"

/**
 * SECTION:pacman-modify
 * @title: PacmanModify
 * @short_description: Modify package metadata
 *
 * A #PacmanModify transaction can be used to modify information about installed packages (equivalent to pacman -D). Currently, this can only be used to change whether a package should be considered a dependency. To do so, pass a list of package names to pacman_transaction_prepare().
 */

/**
 * PacmanModify:
 *
 * Represents a transaction that can modify package metadata.
 */

#define PACMAN_MODIFY_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), PACMAN_TYPE_MODIFY, PacmanModifyPrivate))

G_DEFINE_TYPE (PacmanModify, pacman_modify, PACMAN_TYPE_TRANSACTION);

typedef struct _PacmanModifyPrivate {
	PacmanList *packages;
} PacmanModifyPrivate;

static void pacman_modify_init (PacmanModify *modify) {
	g_return_if_fail (modify != NULL);
}

static void pacman_modify_finalize (GObject *object) {
	PacmanModifyPrivate *priv;
	
	g_return_if_fail (object != NULL);
	
	priv = PACMAN_MODIFY_GET_PRIVATE (PACMAN_MODIFY (object));
	pacman_list_free_full (priv->packages, (GDestroyNotify) g_free);
	
	G_OBJECT_CLASS (pacman_modify_parent_class)->finalize (object);
}

/**
 * pacman_modify_get_packages:
 * @modify: A #PacmanModify.
 *
 * Gets a list of packages with metadata that will be changed when @modify is committed.
 *
 * Returns: A list of package names. Do not free.
 */
const PacmanList *pacman_modify_get_packages (PacmanModify *modify) {
	PacmanModifyPrivate *priv;
	
	g_return_val_if_fail (modify != NULL, NULL);
	
	priv = PACMAN_MODIFY_GET_PRIVATE (modify);
	return priv->packages;
}

/**
 * pacman_manager_modify:
 * @manager: A #PacmanManager.
 * @flags: A set of #PacmanTransactionFlags.
 * @error: A #GError, or %NULL.
 *
 * Initializes a transaction that can modify package metadata, configured according to @flags. If %PACMAN_TRANSACTION_FLAGS_INSTALL_IMPLICIT is set, the transaction will make packages appear to have been installed as a dependency for another package. Otherwise, if %PACMAN_TRANSACTION_FLAGS_INSTALL_EXPLICIT is set, the transaction will make packages appear to have been installed explicitly.
 *
 * Returns: A #PacmanModify transaction, or %NULL if @error is set. Free with g_object_unref().
 */
PacmanTransaction *pacman_manager_modify (PacmanManager *manager, guint32 flags, GError **error) {
	PacmanTransaction *result;
	
	g_return_val_if_fail (manager != NULL, NULL);
	
	if (!pacman_transaction_start (flags, error)) {
		return NULL;
	}
	
	return pacman_manager_new_transaction (manager, PACMAN_TYPE_MODIFY);
}

static gboolean pacman_modify_prepare (PacmanTransaction *transaction, const PacmanList *targets, GError **error) {
	PacmanModifyPrivate *priv;
	const PacmanList *i;
	
	g_return_val_if_fail (transaction != NULL, FALSE);
	g_return_val_if_fail (targets != NULL, FALSE);
	
	priv = PACMAN_MODIFY_GET_PRIVATE (PACMAN_MODIFY (transaction));
	
	/* have the same multiple-call behaviour as other transactions */
	if (priv->packages != NULL) {
		pacman_list_free (priv->packages);
		priv->packages = NULL;
	}
	
	for (i = targets; i != NULL; i = pacman_list_next (i)) {
		const gchar *target = (const gchar *) pacman_list_get (i);
		priv->packages = pacman_list_add (priv->packages, g_strdup (target));
	}
	
	return TRUE;
}

static gboolean pacman_modify_commit (PacmanTransaction *transaction, GError **error) {
	PacmanList *i, *packages;
	PacmanDatabase *database;
	pmpkgreason_t reason;
	
	g_return_val_if_fail (transaction != NULL, FALSE);
	g_return_val_if_fail (pacman_manager != NULL, FALSE);
	
	database = pacman_manager_get_local_database (pacman_manager);
	g_return_val_if_fail (database != NULL, FALSE);
	
	packages = PACMAN_MODIFY_GET_PRIVATE (PACMAN_MODIFY (transaction))->packages;
	
	if (packages == NULL) {
		g_set_error (error, PACMAN_ERROR, PACMAN_ERROR_TRANSACTION_NOT_PREPARED, _("Could not commit transaction: %s"), alpm_strerror (PM_ERR_TRANS_NOT_PREPARED));
		return FALSE;
	}
	
	if ((pacman_transaction_get_flags (transaction) & PACMAN_TRANSACTION_FLAGS_INSTALL_IMPLICIT) != 0) {
		reason = PM_PKG_REASON_DEPEND;
	} else if ((pacman_transaction_get_flags (transaction) & PACMAN_TRANSACTION_FLAGS_INSTALL_EXPLICIT) != 0) {
		reason = PM_PKG_REASON_EXPLICIT;
	} else {
		g_set_error (error, PACMAN_ERROR, PACMAN_ERROR_TRANSACTION_INVALID_OPERATION, _("Could not commit transaction: %s"), _("no install reason specified"));
		return FALSE;
	}
	
	for (i = packages; i != NULL; i = pacman_list_next (i)) {
		const gchar *package = (const gchar *) pacman_list_get (i);
		if (alpm_db_set_pkgreason (database, package, reason) < 0) {
			g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not set install reason for package %s: %s"), package, alpm_strerrorlast ());
			return FALSE;
		}
	}
	
	return TRUE;
}

static void pacman_modify_class_init (PacmanModifyClass *klass) {
	g_return_if_fail (klass != NULL);
	
	g_type_class_add_private (klass, sizeof (PacmanModifyPrivate));
	
	G_OBJECT_CLASS (klass)->finalize = pacman_modify_finalize;
	
	PACMAN_TRANSACTION_CLASS (klass)->prepare = pacman_modify_prepare;
	PACMAN_TRANSACTION_CLASS (klass)->commit = pacman_modify_commit;
}
