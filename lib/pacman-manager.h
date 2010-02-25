/* pacman-manager.h
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

#if !defined (__PACMAN_H_INSIDE__) && !defined (PACMAN_COMPILATION)
#error "Only <pacman.h> can be included directly."
#endif

#ifndef __PACMAN_MANAGER_H__
#define __PACMAN_MANAGER_H__

#include <glib.h>
#include <glib-object.h>
#include "pacman-types.h"

G_BEGIN_DECLS

#define PACMAN_TYPE_MANAGER (pacman_manager_get_type ())
#define PACMAN_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PACMAN_TYPE_MANAGER, PacmanManager))
#define PACMAN_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PACMAN_TYPE_MANAGER, PacmanManagerClass))
#define PACMAN_IS_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PACMAN_TYPE_MANAGER))
#define PACMAN_IS_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PACMAN_TYPE_MANAGER))
#define PACMAN_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PACMAN_TYPE_MANAGER, PacmanManagerClass))

struct _PacmanManager {
	GObject parent_instance;
};

typedef struct _PacmanManagerClass {
	GObjectClass parent_class;
} PacmanManagerClass;

GType pacman_manager_get_type (void);

PacmanManager *pacman_manager_get (GError **error);

const gchar *pacman_manager_get_root_path (PacmanManager *manager);
gboolean pacman_manager_set_root_path (PacmanManager *manager, const gchar *path, GError **error);

const gchar *pacman_manager_get_database_path (PacmanManager *manager);
gboolean pacman_manager_set_database_path (PacmanManager *manager, const gchar *path, GError **error);

const gchar *pacman_manager_get_log_file (PacmanManager *manager);
void pacman_manager_set_log_file (PacmanManager *manager, const gchar *filename);

const PacmanList *pacman_manager_get_cache_paths (PacmanManager *manager);
void pacman_manager_add_cache_path (PacmanManager *manager, const gchar *path);
gboolean pacman_manager_remove_cache_path (PacmanManager *manager, const gchar *path);
void pacman_manager_set_cache_paths (PacmanManager *manager, PacmanList *paths);

gboolean pacman_manager_get_i_love_candy (PacmanManager *manager);
void pacman_manager_set_i_love_candy (PacmanManager *manager, gboolean value);

gboolean pacman_manager_get_show_size (PacmanManager *manager);
void pacman_manager_set_show_size (PacmanManager *manager, gboolean value);

gboolean pacman_manager_get_total_download (PacmanManager *manager);
void pacman_manager_set_total_download (PacmanManager *manager, gboolean value);

gboolean pacman_manager_get_no_passive_ftp (PacmanManager *manager);
void pacman_manager_set_no_passive_ftp (PacmanManager *manager, gboolean value);

gboolean pacman_manager_get_use_delta (PacmanManager *manager);
void pacman_manager_set_use_delta (PacmanManager *manager, gboolean value);

gboolean pacman_manager_get_use_syslog (PacmanManager *manager);
void pacman_manager_set_use_syslog (PacmanManager *manager, gboolean value);

/**
 * PacmanTransferFunc:
 * @manager: A #PacmanManager.
 * @url: A URL.
 * @filename: A file name.
 * @mtime: A modification time.
 * @user_data: User data specified when the transfer handler was set.
 *
 * The type of function used to download files. The function should download a file from @url and save it at @filename. Initially, @mtime is set to the modification time of the most recent file downloaded to @filename, or 0 if this is unknown. The function should update this value if it is able to, and use it to avoid having to download the same file twice.
 *
 * Returns: %TRUE if the download succeeded, %FALSE otherwise.
 */
typedef gboolean (*PacmanTransferFunc) (PacmanManager *manager, const gchar *url, const gchar *filename, time_t *mtime, gpointer user_data);
void pacman_manager_set_transfer_closure (PacmanManager *manager, GClosure *closure);
void pacman_manager_set_transfer_handler (PacmanManager *manager, PacmanTransferFunc func, gpointer user_data, GClosureNotify destroy_data);
void pacman_manager_set_transfer_command (PacmanManager *manager, const gchar *command);

const gchar *pacman_manager_get_clean_method (PacmanManager *manager);
void pacman_manager_set_clean_method (PacmanManager *manager, const gchar *method);

const PacmanList *pacman_manager_get_ignore_groups (PacmanManager *manager);
void pacman_manager_add_ignore_group (PacmanManager *manager, const gchar *group);
gboolean pacman_manager_remove_ignore_group (PacmanManager *manager, const gchar *group);
void pacman_manager_set_ignore_groups (PacmanManager *manager, PacmanList *groups);

const PacmanList *pacman_manager_get_hold_packages (PacmanManager *manager);
void pacman_manager_add_hold_package (PacmanManager *manager, const gchar *package);
gboolean pacman_manager_remove_hold_package (PacmanManager *manager, const gchar *package);
void pacman_manager_set_hold_packages (PacmanManager *manager, PacmanList *packages);

const PacmanList *pacman_manager_get_sync_firsts (PacmanManager *manager);
void pacman_manager_add_sync_first (PacmanManager *manager, const gchar *package);
gboolean pacman_manager_remove_sync_first (PacmanManager *manager, const gchar *package);
void pacman_manager_set_sync_firsts (PacmanManager *manager, PacmanList *packages);

const PacmanList *pacman_manager_get_ignore_packages (PacmanManager *manager);
void pacman_manager_add_ignore_package (PacmanManager *manager, const gchar *package);
gboolean pacman_manager_remove_ignore_package (PacmanManager *manager, const gchar *package);
void pacman_manager_set_ignore_packages (PacmanManager *manager, PacmanList *packages);

const PacmanList *pacman_manager_get_no_extracts (PacmanManager *manager);
void pacman_manager_add_no_extract (PacmanManager *manager, const gchar *filename);
gboolean pacman_manager_remove_no_extract (PacmanManager *manager, const gchar *filename);
void pacman_manager_set_no_extracts (PacmanManager *manager, PacmanList *filenames);

const PacmanList *pacman_manager_get_no_upgrades (PacmanManager *manager);
void pacman_manager_add_no_upgrade (PacmanManager *manager, const gchar *filename);
gboolean pacman_manager_remove_no_upgrade (PacmanManager *manager, const gchar *filename);
void pacman_manager_set_no_upgrades (PacmanManager *manager, PacmanList *filenames);

PacmanDatabase *pacman_manager_get_local_database (PacmanManager *manager);
PacmanDatabase *pacman_manager_register_local_database (PacmanManager *manager, GError **error);

const PacmanList *pacman_manager_get_sync_databases (PacmanManager *manager);
PacmanDatabase *pacman_manager_find_sync_database (PacmanManager *manager, const gchar *name);
PacmanDatabase *pacman_manager_register_sync_database (PacmanManager *manager, const gchar *name, GError **error);

gboolean pacman_manager_unregister_database (PacmanManager *manager, PacmanDatabase *database, GError **error);
gboolean pacman_manager_unregister_all_databases (PacmanManager *manager, GError **error);

gboolean pacman_manager_configure (PacmanManager *manager, const gchar *filename, GError **error);

const gchar *pacman_manager_get_version (PacmanManager *manager);
PacmanTransaction *pacman_manager_get_transaction (PacmanManager *manager);

PacmanTransaction *pacman_manager_install (PacmanManager *manager, guint32 flags, GError **error);
PacmanTransaction *pacman_manager_remove (PacmanManager *manager, guint32 flags, GError **error);
PacmanTransaction *pacman_manager_sync (PacmanManager *manager, guint32 flags, GError **error);
PacmanTransaction *pacman_manager_update (PacmanManager *manager, guint32 flags, GError **error);

PacmanList *pacman_manager_find_missing_dependencies (PacmanManager *manager, const PacmanList *remove, const PacmanList *install);
PacmanList *pacman_manager_test_dependencies (PacmanManager *manager, const PacmanList *dependencies);

G_END_DECLS

#endif
