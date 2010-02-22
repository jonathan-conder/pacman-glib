/* pacman-update.c
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
#include "pacman-update.h"

/**
 * SECTION:pacman-update
 * @title: PacmanUpdate
 * @short_description: Update package databases
 *
 * A #PacmanUpdate transaction can be used to update the package databases (equivalent to pacman -Sy). To do so, pass a list of names of databases to update to pacman_transaction_prepare(), or an empty list to update them all.
 */

/**
 * PacmanUpdate:
 *
 * Represents a database update transaction.
 */

#define PACMAN_UPDATE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), PACMAN_TYPE_UPDATE, PacmanUpdatePrivate))

G_DEFINE_TYPE (PacmanUpdate, pacman_update, PACMAN_TYPE_TRANSACTION);

typedef struct _PacmanUpdatePrivate {
	PacmanList *databases;
} PacmanUpdatePrivate;

static void pacman_update_init (PacmanUpdate *update) {
	g_return_if_fail (update != NULL);
}

static void pacman_update_finalize (GObject *object) {
	PacmanUpdatePrivate *priv;
	
	g_return_if_fail (object != NULL);
	
	priv = PACMAN_UPDATE_GET_PRIVATE (PACMAN_UPDATE (object));
	pacman_list_free (priv->databases);
	
	G_OBJECT_CLASS (pacman_update_parent_class)->finalize (object);
}

/**
 * pacman_update_get_databases:
 * @update: A #PacmanUpdate.
 *
 * Gets a list of databases that will be upgraded when @update is committed.
 *
 * Returns: A list of #PacmanDatabase. Do not free.
 */
const PacmanList *pacman_update_get_databases (PacmanUpdate *update) {
	PacmanUpdatePrivate *priv;
	
	g_return_val_if_fail (update != NULL, NULL);
	
	priv = PACMAN_UPDATE_GET_PRIVATE (update);
	return priv->databases;
}

/**
 * pacman_manager_update:
 * @manager: A #PacmanManager.
 * @flags: A set of #PacmanTransactionFlags.
 * @error: A #GError, or %NULL.
 *
 * Initializes a transaction that can update sync databases, configured according to @flags.
 *
 * Returns: A #PacmanUpdate transaction, or %NULL if @error is set. Free with g_object_unref().
 */
PacmanTransaction *pacman_manager_update (PacmanManager *manager, guint32 flags, GError **error) {
	PacmanTransaction *result;
	
	g_return_val_if_fail (manager != NULL, NULL);
	
	alpm_logaction ("synchronizing package lists\n");
	
	if (!pacman_transaction_start (PM_TRANS_TYPE_SYNC, flags, error)) {
		return NULL;
	}
	
	return pacman_manager_new_transaction (manager, PACMAN_TYPE_UPDATE);
}

static gboolean pacman_update_prepare (PacmanTransaction *transaction, const PacmanList *targets, GError **error) {
	PacmanUpdatePrivate *priv;
	const PacmanList *i, *j;
	
	g_return_val_if_fail (transaction != NULL, FALSE);
	g_return_val_if_fail (pacman_manager != NULL, FALSE);
	
	priv = PACMAN_UPDATE_GET_PRIVATE (PACMAN_UPDATE (transaction));
	
	/* have the same multiple-call behaviour as other transactions */
	if (priv->databases != NULL) {
		pacman_list_free (priv->databases);
		priv->databases = NULL;
	}
	
	if (targets != NULL) {
		for (i = targets; i != NULL; i = pacman_list_next (i)) {
			gchar *target = (gchar *) pacman_list_get (i);
			
			for (j = pacman_manager_get_sync_databases (pacman_manager); j != NULL; j = pacman_list_next (j)) {
				PacmanDatabase *database = (PacmanDatabase *) pacman_list_get (j);
				
				if (g_strcmp0 (target, pacman_database_get_name (database)) == 0) {
					priv->databases = pacman_list_add (priv->databases, database);
					break;
				}
			}
			
			if (j == NULL) {
				g_set_error (error, PACMAN_ERROR, PACMAN_ERROR_DATABASE_NOT_FOUND, _("Could not find sync database named [%s]"), target);
				return FALSE;
			}
		}
	} else {
		priv->databases = pacman_list_copy (pacman_manager_get_sync_databases (pacman_manager));
		
		if (priv->databases == NULL) {
			g_set_error (error, PACMAN_ERROR, PACMAN_ERROR_DATABASE_NOT_FOUND, _("Could not find any sync databases"));
			return FALSE;
		}
	}
	
	return TRUE;
}

static gboolean pacman_update_commit (PacmanTransaction *transaction, GError **error) {
	PacmanList *i, *databases;
	gboolean force, result = FALSE;
	
	g_return_val_if_fail (transaction != NULL, FALSE);
	
	databases = PACMAN_UPDATE_GET_PRIVATE (PACMAN_UPDATE (transaction))->databases;
	force = ((pacman_transaction_get_flags (transaction) & PACMAN_TRANSACTION_FLAGS_UPDATE_ALLOW_DOWNGRADE) != 0);
	
	if (databases == NULL) {
		g_set_error (error, PACMAN_ERROR, PACMAN_ERROR_TRANSACTION_NOT_PREPARED, _("Could not commit transaction: %s"), alpm_strerror (PM_ERR_TRANS_NOT_PREPARED));
		return FALSE;
	}
	
	for (i = databases; i != NULL; i = pacman_list_next (i)) {
		PacmanDatabase *database = (PacmanDatabase *) pacman_list_get (i);
		int code = alpm_db_update ((int) force, database);
		
		if (code == 0) {
			result = TRUE;
		} else if (code < 0) {
			g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not update database named [%s]: %s"), pacman_database_get_name (database), alpm_strerrorlast ());
			return FALSE;
		}
	}
	
	return result;
}

static void pacman_update_class_init (PacmanUpdateClass *klass) {
	g_return_if_fail (klass != NULL);
	
	g_type_class_add_private (klass, sizeof (PacmanUpdatePrivate));
	
	G_OBJECT_CLASS (klass)->finalize = pacman_update_finalize;
	
	PACMAN_TRANSACTION_CLASS (klass)->prepare = pacman_update_prepare;
	PACMAN_TRANSACTION_CLASS (klass)->commit = pacman_update_commit;
}
