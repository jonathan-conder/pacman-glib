/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007 Andreas Obergrusberger <tradiaz@yahoo.de>
 * Copyright (C) 2008, 2009 Valeriy Lyasotskiy <onestep@ukr.net>
 * Copyright (C) 2010 Jonathan Conder <j@skurvy.no-ip.org>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#define _GNU_SOURCE

#include <string.h>
#include <gmodule.h>
#include <glib.h>
#include <pk-backend.h>
#include <egg-debug.h>

#include <gpacman.h>

#define PACMAN_LOCAL_DB_ALIAS "installed"

PacmanManager *pacman = NULL;
GHashTable *group_map = NULL;

typedef enum {
	PK_ALPM_SEARCH_TYPE_NULL,
	PK_ALPM_SEARCH_TYPE_RESOLVE,
	PK_ALPM_SEARCH_TYPE_NAME,
	PK_ALPM_SEARCH_TYPE_DETAILS,
	PK_ALPM_SEARCH_TYPE_GROUP,
	PK_ALPM_SEARCH_TYPE_PROVIDES
} PkAlpmSearchType;

static int
package_compare (PacmanPackage *first, PacmanPackage *second) {
	int result;

	/* check for no package */
	if (first == NULL)
		return (second == NULL) ? 0 : -1;
	if (second == NULL)
		return 1;

	/* compare package names */
	result = g_strcmp0 (pacman_package_get_name (first), pacman_package_get_name (second));
	if (result != 0)
		return result;

	/* compare package versions */
	result = pacman_package_compare_version (pacman_package_get_version (first), pacman_package_get_version (second));
	return result;
}

static gchar *
package_to_package_id (PacmanPackage *package, const gchar *repo)
{
	const gchar *arch = pacman_package_get_arch (package);
	if (arch == NULL)
		arch = "unknown";

	if (repo == NULL) {
		PacmanDatabase *database = pacman_package_get_database (package);
		if (database == NULL)
			repo = "unknown";
		else if (database == pacman_manager_get_local_database (pacman))
			repo = PACMAN_LOCAL_DB_ALIAS;
		else
			repo = pacman_database_get_name (database);
	}

	return pk_package_id_build (pacman_package_get_name (package), pacman_package_get_version (package), arch, repo);
}

static PacmanPackage *
package_from_package_id (const gchar *package_id)
{
	PacmanDatabase *database = NULL;
	PacmanPackage *result = NULL;
	gchar **package_id_data = pk_package_id_split (package_id);

	/* do all this fancy stuff */
	if (g_strcmp0 (PACMAN_LOCAL_DB_ALIAS, package_id_data[PK_PACKAGE_ID_DATA]) == 0)
		database = pacman_manager_get_local_database (pacman);
	else {
		const PacmanList *list;
		for (list = pacman_manager_get_sync_databases (pacman); list != NULL; list = pacman_list_next (list)) {
			PacmanDatabase *sync = (PacmanDatabase *) pacman_list_get (list);
			if (g_strcmp0 (pacman_database_get_name (sync), package_id_data[PK_PACKAGE_ID_DATA]) == 0) {
				database = sync;
				break;
			}
		}
	}

	if (database != NULL) {
		PacmanPackage *package = pacman_database_find_package (database, package_id_data[PK_PACKAGE_ID_NAME]);
		if (package != NULL && g_strcmp0 (pacman_package_get_version (package), package_id_data[PK_PACKAGE_ID_VERSION]) == 0)
			result = package;
	}

	g_strfreev (package_id_data);
	return result;
}

static gboolean
str_has_prefixes (const gchar *str, const gchar *prefix, ...)
{
	va_list args;
	va_start (args, prefix);
	
	while (prefix != NULL) {
		while (*prefix != '\0') {
			if (*str != *prefix)
				break;
			++str;
			++prefix;
		}

		/* didn't match */
		if (*prefix != '\0')
			break;
		else
			prefix = va_arg (args, const gchar *);
	}

	va_end (args);
	/* matched all if prefix is NULL */
	return prefix == NULL;
}

static PacmanPackage *
package_from_filename (const gchar *filename, const gchar **repo)
{
	const PacmanList *databases;
	for (databases = pacman_manager_get_sync_databases (pacman); databases != NULL; databases = pacman_list_next (databases)) {
		const PacmanList *packages;
		PacmanDatabase *database = (PacmanDatabase *) pacman_list_get (databases);

		for (packages = pacman_database_get_packages (database); packages != NULL; packages = pacman_list_next (packages)) {
			PacmanPackage *package = (PacmanPackage *) pacman_list_get (packages);
			/* TODO: could we speed this up because the list is sorted? */
			if (str_has_prefixes (filename, pacman_package_get_name (package), "-", pacman_package_get_version (package), "-", pacman_package_get_arch (package), NULL)) {
				*repo = pacman_database_get_name (database);
				return package;
			}
		}
	}
	egg_debug ("alpm: failed to find package from filename %s", filename);
	return NULL;
}

static void
emit_package (PkBackend *backend, PacmanPackage *package, const gchar *repo, PkInfoEnum info)
{
	gchar *package_id;

	egg_debug ("alpm: emitting package with name %s", pacman_package_get_name (package));

	package_id = package_to_package_id (package, repo);
	pk_backend_package (backend, info, package_id, pacman_package_get_description (package));
	g_free (package_id);
}

static void
backend_message (PkBackend *backend, const gchar *message)
{
	gchar **messages = g_strsplit_set (message, "\r\n", -1);
	guint iterator;

	for (iterator = 0; messages[iterator] != NULL; ++iterator) {
		g_strstrip (messages[iterator]);
		if (*messages[iterator] != '\0')
			pk_backend_message (backend, PK_MESSAGE_ENUM_UNKNOWN, "%s", messages[iterator]);
	}

	g_strfreev (messages);
}

static void
backend_error (PkBackend *backend, GError *error)
{
	PkErrorEnum code = PK_ERROR_ENUM_UNKNOWN;
	switch (error->code) {
		case PACMAN_ERROR_MEMORY:
			code = PK_ERROR_ENUM_OOM;
			break;

		case PACMAN_ERROR_SYSTEM:
		case PACMAN_ERROR_INVALID_ARGS:
		case PACMAN_ERROR_NOT_INITIALIZED:
		case PACMAN_ERROR_DATABASE_NOT_INITIALIZED:
		case PACMAN_ERROR_SERVER_INVALID_URL:
		case PACMAN_ERROR_REGEX_INVALID:
		case PACMAN_ERROR_LIBARCHIVE:
		case PACMAN_ERROR_LIBFETCH:
		case PACMAN_ERROR_DOWNLOAD_HANDLER:
			code = PK_ERROR_ENUM_INTERNAL_ERROR;
			break;

		case PACMAN_ERROR_NOT_PERMITTED:
			code = PK_ERROR_ENUM_NOT_AUTHORIZED;
			break;

		case PACMAN_ERROR_FILE_NOT_FOUND:
		case PACMAN_ERROR_DIRECTORY_NOT_FOUND:
			code = PK_ERROR_ENUM_FILE_NOT_FOUND;
			break;

		case PACMAN_ERROR_ALREADY_INITIALIZED:
		case PACMAN_ERROR_DATABASE_ALREADY_INITIALIZED:
			code = PK_ERROR_ENUM_FAILED_INITIALIZATION;
			break;

		case PACMAN_ERROR_ALREADY_RUNNING:
			code = PK_ERROR_ENUM_CANNOT_GET_LOCK;
			break;

		case PACMAN_ERROR_DATABASE_OPEN_FAILED:
			code = PK_ERROR_ENUM_REPO_NOT_FOUND;
			break;

		case PACMAN_ERROR_DATABASE_CREATE_FAILED:
			code = PK_ERROR_ENUM_CANNOT_WRITE_REPO_CONFIG;
			break;

		case PACMAN_ERROR_DATABASE_NOT_FOUND:
			code = PK_ERROR_ENUM_REPO_NOT_FOUND;
			break;

		case PACMAN_ERROR_DATABASE_UPDATE_FAILED:
			code = PK_ERROR_ENUM_REPO_NOT_AVAILABLE;
			break;

		case PACMAN_ERROR_DATABASE_REMOVE_FAILED:
			code = PK_ERROR_ENUM_REPO_CONFIGURATION_ERROR;
			break;

		case PACMAN_ERROR_SERVER_NONE_AVAILABLE:
			code = PK_ERROR_ENUM_NO_MORE_MIRRORS_TO_TRY;
			break;

		case PACMAN_ERROR_TRANSACTION_ALREADY_INITIALIZED:
		case PACMAN_ERROR_TRANSACTION_NOT_INITIALIZED:
		case PACMAN_ERROR_TRANSACTION_DUPLICATE_TARGET:
		case PACMAN_ERROR_TRANSACTION_NOT_READY:
		case PACMAN_ERROR_TRANSACTION_NOT_PREPARED:
		case PACMAN_ERROR_TRANSACTION_INVALID_OPERATION:
		case PACMAN_ERROR_TRANSACTION_NOT_LOCKED:
			code = PK_ERROR_ENUM_TRANSACTION_ERROR;
			break;

		case PACMAN_ERROR_TRANSACTION_ABORTED:
			code = PK_ERROR_ENUM_TRANSACTION_CANCELLED;
			break;

		case PACMAN_ERROR_PACKAGE_NOT_FOUND:
			code = PK_ERROR_ENUM_PACKAGE_NOT_FOUND;
			break;

		case PACMAN_ERROR_PACKAGE_IGNORED:
			code = PK_ERROR_ENUM_PACKAGE_INSTALL_BLOCKED;
			break;

		case PACMAN_ERROR_DELTA_INVALID:
		case PACMAN_ERROR_PACKAGE_INVALID:
			code = PK_ERROR_ENUM_INVALID_PACKAGE_FILE;
			break;

		case PACMAN_ERROR_PACKAGE_OPEN_FAILED:
			code = PK_ERROR_ENUM_PACKAGE_NOT_FOUND;
			break;

		case PACMAN_ERROR_PACKAGE_REMOVE_FAILED:
			code = PK_ERROR_ENUM_PACKAGE_FAILED_TO_REMOVE;
			break;

		case PACMAN_ERROR_PACKAGE_UNKNOWN_FILENAME:
		case PACMAN_ERROR_PACKAGE_DATABASE_NOT_FOUND:
			code = PK_ERROR_ENUM_PACKAGE_FAILED_TO_CONFIGURE;
			break;

		case PACMAN_ERROR_DELTA_PATCH_FAILED:
			code = PK_ERROR_ENUM_PACKAGE_FAILED_TO_BUILD;
			break;

		case PACMAN_ERROR_DEPENDENCY_UNSATISFIED:
			code = PK_ERROR_ENUM_DEP_RESOLUTION_FAILED;
			break;

		case PACMAN_ERROR_CONFLICT:
			code = PK_ERROR_ENUM_PACKAGE_CONFLICTS;
			break;

		case PACMAN_ERROR_FILE_CONFLICT:
			code = PK_ERROR_ENUM_FILE_CONFLICTS;
			break;

		case PACMAN_ERROR_DOWNLOAD_FAILED:
			code = PK_ERROR_ENUM_PACKAGE_DOWNLOAD_FAILED;
			break;

		case PACMAN_ERROR_CONFIG_INVALID:
			code = PK_ERROR_ENUM_FAILED_CONFIG_PARSING;
			break;

		case PACMAN_ERROR_PACKAGE_HELD:
			code = PK_ERROR_ENUM_CANNOT_REMOVE_SYSTEM_PACKAGE;
			break;
	}

	/* TODO: various transaction errors report extra information */
	pk_backend_error_code (backend, code, "%s", error->message);
	g_error_free (error);
}

static void
transaction_download_cb (PacmanTransaction *transaction, const gchar *filename, guint complete, guint total, gpointer user_data)
{
	static guint total_complete = 0, total_total = 0;
	
	if (filename == NULL) {
		pk_backend_set_sub_percentage ((PkBackend *) user_data, 0);
		pk_backend_set_percentage ((PkBackend *) user_data, 0);

		total_complete = complete;
		total_total = total;
	} else {
		if (total != 0)
			pk_backend_set_sub_percentage ((PkBackend *) user_data, complete * 100 / total);
		if (total_total != 0)
			pk_backend_set_percentage ((PkBackend *) user_data, (total_complete + complete) * 100 / total_total);

		/* don't report on databases */
		if (g_str_has_suffix (filename, ".pkg.tar.gz")) {
			const gchar *repo = NULL;
			PkInfoEnum info = PK_INFO_ENUM_UNKNOWN;
			PacmanPackage *package = NULL;

			if (complete == 0) {
				package = package_from_filename (filename, &repo);
				info = PK_INFO_ENUM_DOWNLOADING;
			} else if (complete == total) {
				package = package_from_filename (filename, &repo);
				info = PK_INFO_ENUM_FINISHED;

				/* report for backend_download_packages */
				if (package != NULL && (pacman_transaction_get_flags (transaction) & PACMAN_TRANSACTION_FLAGS_SYNC_DOWNLOAD_ONLY)) {
					gchar *path, *package_id = package_to_package_id (package, repo);
					const gchar *directory = pk_backend_get_string ((PkBackend *) user_data, "directory");

					path = g_build_filename (directory, filename, NULL);
					pk_backend_files ((PkBackend *) user_data, package_id, path);

					g_free (path);
					g_free (package_id);
				}
			}

			if (package != NULL)
				emit_package ((PkBackend *) user_data, package, repo, info);
		}

		if (complete == total)
			total_complete += total;
	}
}

static void
transaction_progress_cb (PacmanTransaction *transaction, PacmanTransactionProgress type, const gchar *target, guint percent, guint current, guint targets, gpointer user_data)
{
	switch (type) {
		case PACMAN_TRANSACTION_PROGRESS_INSTALL:
		case PACMAN_TRANSACTION_PROGRESS_UPGRADE:
		case PACMAN_TRANSACTION_PROGRESS_REMOVE:
		{
			guint total_percent = ((current - 1) * 100 + percent) / targets;
			pk_backend_set_sub_percentage ((PkBackend *) user_data, percent);
			pk_backend_set_percentage ((PkBackend *) user_data, total_percent);
		}
		default:
			egg_debug ("alpm progress: %d", type);
	}
}

static gboolean
transaction_question_cb (PacmanTransaction *transaction, PacmanTransactionQuestion question, const gchar *message, gpointer user_data)
{
	switch (question) {
		case PACMAN_TRANSACTION_QUESTION_INSTALL_IGNORE_PACKAGE:
		{
			gchar *packages = pacman_package_make_list (pacman_transaction_get_marked_packages (transaction));
			gchar *warning = g_strdup_printf ("The following packages are marked as ignored:\n%s\n", packages);

			backend_message ((PkBackend *) user_data, warning);

			g_free (warning);
			g_free (packages);
			return TRUE;
		}
		case PACMAN_TRANSACTION_QUESTION_REPLACE_PACKAGE:
		{
			PacmanConflict *conflict = (PacmanConflict *) pacman_list_get (pacman_transaction_get_conflicts (transaction));
			const gchar *first = pacman_conflict_get_second_package (conflict), *second = pacman_conflict_get_first_package (conflict);
			gchar *warning = g_strdup_printf ("Package %s will be replaced with %s\n", second, first);

			backend_message ((PkBackend *) user_data, warning);

			g_free (warning);
			return TRUE;
		}
		case PACMAN_TRANSACTION_QUESTION_SYNC_FIRST:
		{
			gchar *packages = pacman_package_make_list (pacman_transaction_get_marked_packages (transaction));
			gchar *warning = g_strdup_printf ("The following packages should probably be installed first:\n%s\n", packages);

			pk_backend_message ((PkBackend *) user_data, PK_MESSAGE_ENUM_UNKNOWN, warning);

			g_free (warning);
			g_free (packages);
			return FALSE;
		}
		case PACMAN_TRANSACTION_QUESTION_REMOVE_CONFLICTING_PACKAGE:
		case PACMAN_TRANSACTION_QUESTION_SKIP_UNRESOLVABLE_PACKAGES:
		case PACMAN_TRANSACTION_QUESTION_REMOVE_HOLD_PACKAGES:
			return FALSE;

		case PACMAN_TRANSACTION_QUESTION_INSTALL_OLDER_PACKAGE:
		case PACMAN_TRANSACTION_QUESTION_DELETE_CORRUPTED_PACKAGE:
			return TRUE;

		default:
			egg_debug ("alpm question: %s", message);
			return FALSE;
	}
}

static void
transaction_status_cb (PacmanTransaction *transaction, PacmanTransactionStatus status, const gchar *message, gpointer user_data)
{
	/* TODO: add more code here, and possibly allow cancel */
	switch (status) {
		case PACMAN_TRANSACTION_STATUS_INSTALL_START:
		{
			const PacmanList *packages;
			pk_backend_set_allow_cancel ((PkBackend *) user_data, FALSE);

			for (packages = pacman_transaction_get_marked_packages (transaction); packages != NULL; packages = pacman_list_next (packages)) {
				PacmanPackage *package = (PacmanPackage *) pacman_list_get (packages);
				emit_package ((PkBackend *) user_data, package, NULL, PK_INFO_ENUM_INSTALLING);
			}
			break;
		}
		case PACMAN_TRANSACTION_STATUS_UPGRADE_START:
		{
			const PacmanList *packages;
			pk_backend_set_allow_cancel ((PkBackend *) user_data, FALSE);

			for (packages = pacman_transaction_get_marked_packages (transaction); packages != NULL; packages = pacman_list_next (packages)) {
				PacmanPackage *package = (PacmanPackage *) pacman_list_get (packages);
				emit_package ((PkBackend *) user_data, package, PACMAN_LOCAL_DB_ALIAS, PK_INFO_ENUM_UPDATING);
			}
			break;
		}
		case PACMAN_TRANSACTION_STATUS_REMOVE_START:
		{
			const PacmanList *packages;
			pk_backend_set_allow_cancel ((PkBackend *) user_data, FALSE);

			for (packages = pacman_transaction_get_marked_packages (transaction); packages != NULL; packages = pacman_list_next (packages)) {
				PacmanPackage *package = (PacmanPackage *) pacman_list_get (packages);
				emit_package ((PkBackend *) user_data, package, PACMAN_LOCAL_DB_ALIAS, PK_INFO_ENUM_REMOVING);
			}
			break;
		}
		default:
			egg_debug ("alpm status: %s", message);
			break;
	}
}

static void
pacman_message_cb (const gchar *domain, GLogLevelFlags level, const gchar *message, gpointer user_data)
{
	switch (level) {
		case G_LOG_LEVEL_WARNING:
		case G_LOG_LEVEL_MESSAGE:
		{
			backend_message ((PkBackend *) user_data, message);
			break;
		}
		case G_LOG_LEVEL_INFO:
		case G_LOG_LEVEL_DEBUG:
			egg_debug ("alpm: %s", message);
			break;
		default:
			break;
	}
}

static gboolean
backend_transaction_run (PkBackend *backend, PacmanTransaction *transaction, const PacmanList *targets, GError **error)
{
	g_signal_connect (transaction, "download", G_CALLBACK (transaction_download_cb), backend);
	g_signal_connect (transaction, "progress", G_CALLBACK (transaction_progress_cb), backend);
	g_signal_connect (transaction, "question", G_CALLBACK (transaction_question_cb), backend);
	g_signal_connect (transaction, "status", G_CALLBACK (transaction_status_cb), backend);
	
	if (!pacman_transaction_prepare (transaction, targets, error) || !pacman_transaction_commit (transaction, error)) {
		backend_error (backend, *error);
		return FALSE;
	}
	
	return TRUE;
}

/**
 * backend_initialize:
 */
static void
backend_initialize (PkBackend *backend)
{
	GError *error = NULL;
	
	GLogLevelFlags flags = G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG;
	g_log_set_handler ("Pacman", flags, pacman_message_cb, backend);

	egg_debug ("alpm: initializing backend");

	pacman = pacman_manager_get (&error);
	if (pacman == NULL) {
		backend_error (backend, error);
		return;
	}

	if (!pacman_manager_configure (pacman, NULL, &error)) {
		backend_error (backend, error);
		return;
	}

	/* fill in group mapping */
	group_map = g_hash_table_new (g_str_hash, g_str_equal);
	g_hash_table_insert (group_map, (gchar *) "gnome", (gchar *) "desktop-gnome");
	g_hash_table_insert (group_map, (gchar *) "gnome-extra", (gchar *) "desktop-gnome");
	g_hash_table_insert (group_map, (gchar *) "compiz-gnome", (gchar *) "desktop-gnome");
	g_hash_table_insert (group_map, (gchar *) "kde", (gchar *) "desktop-kde");
	g_hash_table_insert (group_map, (gchar *) "compiz-kde", (gchar *) "desktop-kde");
	g_hash_table_insert (group_map, (gchar *) "compiz-fusion-kde", (gchar *) "desktop-kde");
	g_hash_table_insert (group_map, (gchar *) "lxde", (gchar *) "desktop-other");
	g_hash_table_insert (group_map, (gchar *) "rox-desktop", (gchar *) "desktop-other");
	g_hash_table_insert (group_map, (gchar *) "e17-cvs", (gchar *) "desktop-other");
	g_hash_table_insert (group_map, (gchar *) "e17-extra-cvs", (gchar *) "desktop-other");
	g_hash_table_insert (group_map, (gchar *) "e17-libs-cvs", (gchar *) "desktop-other");
	g_hash_table_insert (group_map, (gchar *) "xfce4", (gchar *) "desktop-xfce");
	g_hash_table_insert (group_map, (gchar *) "xfce4-goodies", (gchar *) "desktop-xfce");
	g_hash_table_insert (group_map, (gchar *) "bmp-io-plugins", (gchar *) "multimedia");
	g_hash_table_insert (group_map, (gchar *) "bmp-plugins", (gchar *) "multimedia");
	g_hash_table_insert (group_map, (gchar *) "bmp-visualization-plugins", (gchar *) "multimedia");
	g_hash_table_insert (group_map, (gchar *) "gstreamer0.10-plugins", (gchar *) "multimedia");
	g_hash_table_insert (group_map, (gchar *) "ladspa-plugins", (gchar *) "multimedia");
	g_hash_table_insert (group_map, (gchar *) "pvr", (gchar *) "multimedia");
	g_hash_table_insert (group_map, (gchar *) "mythtv-extras", (gchar *) "multimedia");
	g_hash_table_insert (group_map, (gchar *) "xmms-effect-plugins", (gchar *) "multimedia");
	g_hash_table_insert (group_map, (gchar *) "xmms-io-plugins", (gchar *) "multimedia");
	g_hash_table_insert (group_map, (gchar *) "xmms-plugins", (gchar *) "multimedia");
	g_hash_table_insert (group_map, (gchar *) "base-devel", (gchar *) "programming");
	g_hash_table_insert (group_map, (gchar *) "texlive-lang", (gchar *) "publishing");
	g_hash_table_insert (group_map, (gchar *) "texlive-lang-doc", (gchar *) "publishing");
	g_hash_table_insert (group_map, (gchar *) "texlive-most", (gchar *) "publishing");
	g_hash_table_insert (group_map, (gchar *) "texlive-most-doc", (gchar *) "publishing");
	g_hash_table_insert (group_map, (gchar *) "texlive-most-svn", (gchar *) "publishing");
	g_hash_table_insert (group_map, (gchar *) "base", (gchar *) "system");

	egg_debug ("alpm: ready to go");
}

/**
 * backend_destroy:
 */
static void
backend_destroy (PkBackend *backend)
{
	g_hash_table_destroy (group_map);
	if (pacman != NULL)
		g_object_unref (pacman);
}

/**
 * backend_get_groups:
 */
static PkBitfield
backend_get_groups (PkBackend *backend)
{
	return pk_bitfield_from_enums (
		PK_GROUP_ENUM_DESKTOP_GNOME,
		PK_GROUP_ENUM_DESKTOP_KDE,
		PK_GROUP_ENUM_DESKTOP_OTHER,
		PK_GROUP_ENUM_DESKTOP_XFCE,
		PK_GROUP_ENUM_MULTIMEDIA,
		PK_GROUP_ENUM_OTHER,
		PK_GROUP_ENUM_PROGRAMMING,
		PK_GROUP_ENUM_PUBLISHING,
		PK_GROUP_ENUM_SYSTEM,
		-1);
}

/**
 * backend_get_filters:
 */
static PkBitfield
backend_get_filters (PkBackend *backend)
{
	return pk_bitfield_from_enums (PK_FILTER_ENUM_INSTALLED, -1);
}

/**
 * backend_get_mime_types:
 */
static gchar *
backend_get_mime_types (PkBackend *backend)
{
	return g_strdup ("application/x-compressed-tar");
}

/**
 * backend_cancel:
 **/
static void
backend_cancel (PkBackend *backend)
{
	PacmanTransaction *transaction;
	GError *error = NULL;

	pk_backend_set_status (backend, PK_STATUS_ENUM_CANCEL);

	/* TODO: is this right? */
	transaction = pacman_manager_get_transaction (pacman);
	if (transaction != NULL && !pacman_transaction_cancel (transaction, &error))
		backend_error (backend, error);
}

/**
 * backend_download_packages_thread:
 */
static gboolean
backend_download_packages_thread (PkBackend *backend)
{
	gchar **package_ids = pk_backend_get_strv (backend, "package_ids");
	const gchar *directory = pk_backend_get_string (backend, "directory");

	guint iterator;
	PacmanList *list = NULL;
	PacmanList *cache_paths;

	PacmanTransaction *transaction;
	PacmanTransactionFlags flags = PACMAN_TRANSACTION_FLAGS_IGNORE_DEPENDENCIES | PACMAN_TRANSACTION_FLAGS_IGNORE_DEPENDENCY_CONFLICTS | PACMAN_TRANSACTION_FLAGS_SYNC_DOWNLOAD_ONLY;
	gboolean result;
	GError *error = NULL;

	egg_debug ("alpm: downloading packages to %s", directory);

	/* force a download to PackageKit directory */
	cache_paths = pacman_list_strdup (pacman_manager_get_cache_paths (pacman));
	pacman_manager_set_cache_paths (pacman, NULL);
	pacman_manager_add_cache_path (pacman, directory);

	/* create a new transaction */
	transaction = pacman_manager_sync (pacman, flags, &error);
	if (transaction == NULL) {
		backend_error (backend, error);
		pacman_manager_set_cache_paths (pacman, cache_paths);
		pacman_list_free_full (cache_paths, g_free);
		pk_backend_finished (backend);
		return FALSE;
	}

	/* add targets to the transaction */
	for (iterator = 0; package_ids[iterator] != NULL; ++iterator) {
		gchar **package_id_data = pk_package_id_split (package_ids[iterator]);
		list = pacman_list_add (list, g_strdup (package_id_data[PK_PACKAGE_ID_NAME]));
		g_strfreev (package_id_data);
	}

	/* prepare and commit transaction */
	result = backend_transaction_run (backend, transaction, list, &error);

	pacman_list_free_full (list, g_free);
	g_object_unref (transaction);
	pacman_manager_set_cache_paths (pacman, cache_paths);
	pacman_list_free_full (cache_paths, g_free);

	pk_backend_finished (backend);
	return result;
}

/**
 * backend_download_packages:
 */
static void
backend_download_packages (PkBackend *backend, gchar **package_ids, const gchar *directory)
{
	pk_backend_set_status (backend, PK_STATUS_ENUM_DOWNLOAD);
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);

	pk_backend_thread_create (backend, backend_download_packages_thread);
}

/**
 * backend_get_depends:
 */
static void
backend_get_depends (PkBackend *backend, PkBitfield filters, gchar **package_ids, gboolean recursive)
{
	guint iterator;
	PacmanDatabase *local = pacman_manager_get_local_database (pacman);

	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_allow_cancel (backend, FALSE);

	/* TODO: recursive */
	for (iterator = 0; package_ids[iterator] != NULL; ++iterator) {
		const PacmanList *depends;

		PacmanPackage *package = package_from_package_id (package_ids[iterator]);
		if (package == NULL) {
			pk_backend_error_code (backend, PK_ERROR_ENUM_PACKAGE_ID_INVALID, "Could not find package with ID %s", package_ids[iterator]);
			pk_backend_finished (backend);
			return;
		}

		for (depends = pacman_package_get_dependencies (package); depends != NULL; depends = pacman_list_next (depends)) {
			PacmanDependency *depend = (PacmanDependency *) pacman_list_get (depends);
			PacmanPackage *provider = NULL;

			if (!pk_bitfield_contain (filters, PK_FILTER_ENUM_INSTALLED)) {
				/* search in sync dbs */
				const PacmanList *databases;
				for (databases = pacman_manager_get_sync_databases (pacman); databases != NULL; databases = pacman_list_next (databases)) {
					PacmanDatabase *sync = (PacmanDatabase *) pacman_list_get (databases);

					egg_debug ("alpm: searching for %s in %s", pacman_dependency_get_name (depend), pacman_database_get_name (sync));

					provider = pacman_database_find_package (sync, pacman_dependency_get_name (depend));
					if (provider != NULL && pacman_dependency_satisfied_by (depend, provider) && package_compare (provider, pacman_database_find_package (local, pacman_package_get_name (provider))) != 0) {
						emit_package (backend, provider, pacman_database_get_name (sync), PK_INFO_ENUM_AVAILABLE);
						break;
					}
				}
			}

			if (!pk_bitfield_contain (filters, PK_FILTER_ENUM_NOT_INSTALLED)) {
				egg_debug ("alpm: searching for %s in local db", pacman_dependency_get_name (depend));

				/* search in local db */
				provider = pacman_database_find_package (local, pacman_dependency_get_name (depend));
				if (provider != NULL && pacman_dependency_satisfied_by (depend, provider))
					emit_package (backend, provider, PACMAN_LOCAL_DB_ALIAS, PK_INFO_ENUM_INSTALLED);
			}
		}
	}

	pk_backend_finished (backend);
}

/**
 * backend_get_details:
 */
static void
backend_get_details (PkBackend *backend, gchar **package_ids)
{
	guint iterator;

	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_allow_cancel (backend, FALSE);

	for (iterator = 0; package_ids[iterator] != NULL; ++iterator) {
		const PacmanList *list;
		GString *licenses;
		gchar *result;

		PacmanPackage *package = package_from_package_id (package_ids[iterator]);
		if (package == NULL) {
			pk_backend_error_code (backend, PK_ERROR_ENUM_PACKAGE_ID_INVALID, "Could not find package with ID %s", package_ids[iterator]);
			pk_backend_finished (backend);
			return;
		}

		list = pacman_package_get_licenses (package);
		if (list == NULL)
			licenses = g_string_new ("unknown");
		else {
			licenses = g_string_new ((const gchar *) pacman_list_get (list));
			for (list = pacman_list_next (list); list != NULL; list = pacman_list_next (list)) {
				g_string_append_printf (licenses, ", %s", (const gchar *) pacman_list_get (list));
			}
		}	

		result = g_string_free (licenses, FALSE);
		pk_backend_details (backend, package_ids[iterator], result, PK_GROUP_ENUM_OTHER, pacman_package_get_description (package), pacman_package_get_url (package), pacman_package_get_installed_size (package));
		g_free (result);
	}

	pk_backend_finished (backend);
}

/**
 * backend_get_files:
 */
static void
backend_get_files (PkBackend *backend, gchar **package_ids)
{
	guint iterator;

	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_allow_cancel (backend, FALSE);

	for (iterator = 0; package_ids[iterator] != NULL; ++iterator) {
		const PacmanList *list;
		GString *files;
		gchar *result;

		PacmanPackage *package = package_from_package_id (package_ids[iterator]);
		if (package == NULL) {
			pk_backend_error_code (backend, PK_ERROR_ENUM_PACKAGE_ID_INVALID, "Could not find package with ID %s", package_ids[iterator]);
			pk_backend_finished (backend);
			return;
		}

		list = pacman_package_get_files (package);
		if (list == NULL)
			files = g_string_new ("");
		else {
			const gchar *root_path = pacman_manager_get_root_path (pacman);
			files = g_string_new (root_path);
			g_string_append (files, (const gchar *) pacman_list_get (list));

			for (list = pacman_list_next (list); list != NULL; list = pacman_list_next (list)) {
				g_string_append_printf (files, ";%s%s", root_path, (const gchar *) pacman_list_get (list));
			}
		}	

		result = g_string_free (files, FALSE);
		pk_backend_files (backend, package_ids[iterator], result);
		g_free (result);
	}

	pk_backend_finished (backend);
}

static void
backend_search (PkBackend *backend, PacmanDatabase *database, const gchar *needle, PkAlpmSearchType search_type) {
	const PacmanList *list;
	const gchar *repo;
	PkInfoEnum info;
	PacmanDatabase *local;

	if (database == pacman_manager_get_local_database (pacman)) {
		repo = PACMAN_LOCAL_DB_ALIAS;
		info = PK_INFO_ENUM_INSTALLED;
		local = NULL;
	} else {
		repo = pacman_database_get_name (database);
		info = PK_INFO_ENUM_AVAILABLE;
		local = pacman_manager_get_local_database (pacman);
	}

	/* iterate package cache */
	for (list = pacman_database_get_packages (database); list != NULL; list = pacman_list_next (list)) {
		PacmanPackage *package = (PacmanPackage *) pacman_list_get (list);

		switch (search_type) {
			case PK_ALPM_SEARCH_TYPE_NULL:
				break;

			case PK_ALPM_SEARCH_TYPE_RESOLVE:
				if (g_strcmp0 (pacman_package_get_name (package), needle) != 0)
					package = NULL;
				break;

			case PK_ALPM_SEARCH_TYPE_NAME:
				if (strstr (pacman_package_get_name (package), needle) == NULL)
					package = NULL;
				break;

			case PK_ALPM_SEARCH_TYPE_DETAILS:
			{
				const gchar *description = pacman_package_get_description (package);
				/* TODO: strcasestr is a non-standard extension, replace it? */
				if (description == NULL)
					package = NULL;
				else if (strcasestr (description, needle) == NULL)
					package = NULL;
				break;
			}
			case PK_ALPM_SEARCH_TYPE_GROUP:
			{
				const PacmanList *groups;
				for (groups = pacman_package_get_groups (package); groups != NULL; groups = pacman_list_next (groups)) {
					const gchar *group = g_hash_table_lookup (group_map, (const gchar *) pacman_list_get (groups));
					if (group == NULL)
						group = "other";
					if (g_strcmp0 (needle, group) == 0)
						break;
				}

				/* groups is still set if the loop finished prematurely */
				if (groups == NULL)
					package = NULL;
				break;
			}
			case PK_ALPM_SEARCH_TYPE_PROVIDES:
			{
				const PacmanList *provides;
				for (provides = pacman_package_get_provides (package); provides != NULL; provides = pacman_list_next (provides)) {
					if (g_strcmp0 (needle, (const gchar *) pacman_list_get (provides)) == 0)
						break;
				}

				/* provides is still set if the loop finished prematurely */
				if (provides == NULL)
					package = NULL;
				break;
			}
			default:
				package = NULL;
		}

		if (package != NULL && (local == NULL || package_compare (package, pacman_database_find_package (local, pacman_package_get_name (package))) != 0))
			emit_package (backend, package, repo, info);
	}
}

/**
 * backend_search_values:
 */
static void
backend_search_values (PkBackend *backend, PacmanDatabase *database, gchar **values, PkAlpmSearchType search_type) {
	guint iterator;

	for (iterator = 0; values[iterator] != NULL; ++iterator)
		backend_search (backend, database, values[iterator], search_type);
}

/**
 * backend_get_packages_thread:
 */
static gboolean
backend_get_packages_thread (PkBackend *backend)
{
	PkBitfield filters = pk_backend_get_uint (backend, "filters");

	if (!pk_bitfield_contain (filters, PK_FILTER_ENUM_INSTALLED)) {
		/* search in local db */
		backend_search (backend, pacman_manager_get_local_database (pacman), NULL, PK_ALPM_SEARCH_TYPE_NULL);
	}

	if (!pk_bitfield_contain (filters, PK_FILTER_ENUM_NOT_INSTALLED)) {
		/* search in sync repos */
		const PacmanList *databases;
		for (databases = pacman_manager_get_sync_databases (pacman); databases != NULL; databases = pacman_list_next (databases))
			backend_search (backend, (PacmanDatabase *) pacman_list_get (databases), NULL, PK_ALPM_SEARCH_TYPE_NULL);
	}

	pk_backend_finished (backend);
	return TRUE;
}

/**
 * backend_get_packages:
 */
static void
backend_get_packages (PkBackend *backend, PkBitfield filters)
{
	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);

	pk_backend_thread_create (backend, backend_get_packages_thread);
}

/**
 * backend_get_repo_list:
 */
static void
backend_get_repo_list (PkBackend *backend, PkBitfield filters)
{
	const PacmanList *list;

	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);

	/* iterate on repo list */
	for (list = pacman_manager_get_sync_databases (pacman); list != NULL; list = pacman_list_next (list)) {
		PacmanDatabase *database = (PacmanDatabase *) pacman_list_get (list);
		pk_backend_repo_detail (backend, pacman_database_get_name (database), pacman_database_get_name (database), TRUE);
	}

	pk_backend_finished (backend);
}

/**
 * backend_get_update_detail:
 */
static void
backend_get_update_detail (PkBackend *backend, gchar **package_ids)
{
	guint iterator;
	PacmanDatabase *local = pacman_manager_get_local_database (pacman);

	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_allow_cancel (backend, FALSE);

	for (iterator = 0; package_ids[iterator] != NULL; ++iterator) {
		const PacmanList *list;
		gchar *upgrades_id, *replaces_id = NULL;
		const gchar *vendor_url, *message;

		PkRestartEnum restart;
		PkUpdateStateEnum state;

		PacmanDatabase *database;
		PacmanPackage *package = package_from_package_id (package_ids[iterator]), *upgrades;
		if (package == NULL) {
			pk_backend_error_code (backend, PK_ERROR_ENUM_PACKAGE_ID_INVALID, "Could not find package with ID %s", package_ids[iterator]);
			pk_backend_finished (backend);
			return;
		}
		database = pacman_package_get_database (package);
		upgrades = pacman_database_find_package (local, pacman_package_get_name (package));

		upgrades_id = (upgrades != NULL) ? package_to_package_id (upgrades, PACMAN_LOCAL_DB_ALIAS) : NULL;
		for (list = pacman_package_get_replaces (package); list != NULL; list = pacman_list_next (list)) {
			PacmanPackage *replaces = pacman_database_find_package (local, (const gchar *) pacman_list_get (list));
			if (replaces != NULL) {
				replaces_id = package_to_package_id (replaces, PACMAN_LOCAL_DB_ALIAS);
				break;
			}
		}

		vendor_url = pacman_package_get_url (package);
		message = (upgrades != NULL) ? "Update to latest available version" : "Install as a dependency for another update";

		restart = (strstr (pacman_package_get_name (package), "kernel") != NULL) ? PK_RESTART_ENUM_SYSTEM : PK_RESTART_ENUM_NONE;
		state = (strstr (pacman_database_get_name (database), "testing") != NULL) ? PK_UPDATE_STATE_ENUM_TESTING : PK_UPDATE_STATE_ENUM_STABLE;

		pk_backend_update_detail (backend, package_ids[iterator], upgrades_id, replaces_id, vendor_url, NULL, NULL, restart, message, NULL, state, NULL, NULL);

		g_free (replaces_id);
		g_free (upgrades_id);
	}

	pk_backend_finished (backend);
}

/**
 * backend_get_updates:
 */
static void
backend_get_updates (PkBackend *backend, PkBitfield filters)
{
	const PacmanList *list, *databases = pacman_manager_get_sync_databases (pacman);

	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_allow_cancel (backend, FALSE);

	/* iterate through list of installed packages to find update for each */
	for (list = pacman_database_get_packages (pacman_manager_get_local_database (pacman)); list != NULL; list = pacman_list_next (list)) {
		PacmanPackage *upgrade, *package = (PacmanPackage *) pacman_list_get (list);
		upgrade = pacman_package_find_new_version (package, databases);
		
		if (upgrade != NULL)
			emit_package (backend, upgrade, NULL, PK_INFO_ENUM_NORMAL);
	}

	pk_backend_finished (backend);
}

/**
 * backend_install_files_thread:
 */
static gboolean
backend_install_files_thread (PkBackend *backend)
{
	PacmanTransaction *transaction;
	guint iterator;
	PacmanList *list = NULL;
	gboolean result;
	GError *error = NULL;

	gchar **full_paths = pk_backend_get_strv (backend, "full_paths");

	/* create a new transaction */
	transaction = pacman_manager_install (pacman, PACMAN_TRANSACTION_FLAGS_NONE, &error);
	if (transaction == NULL) {
		backend_error (backend, error);
		pk_backend_finished (backend);
		return FALSE;
	}

	/* add targets to the transaction */
	for (iterator = 0; full_paths[iterator] != NULL; ++iterator) {
		list = pacman_list_add (list, full_paths[iterator]);
		egg_debug ("alpm: %s added to transaction queue", full_paths[iterator]);
	}

	/* prepare and commit transaction */
	result = backend_transaction_run (backend, transaction, list, &error);
	
	pacman_list_free (list);
	g_object_unref (transaction);

	pk_backend_finished (backend);
	return result;
}

/**
 * backend_install_files:
 */
static void
backend_install_files (PkBackend *backend, gboolean only_trusted, gchar **full_paths)
{
	pk_backend_set_status (backend, PK_STATUS_ENUM_INSTALL);
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);

	pk_backend_thread_create (backend, backend_install_files_thread);
}

/**
 * backend_install_packages_thread:
 */
static gboolean
backend_install_packages_thread (PkBackend *backend)
{
	PacmanTransaction *transaction;
	guint iterator;
	PacmanList *list = NULL;
	gboolean result;
	GError *error = NULL;

	/* FIXME: support only_trusted */
	gchar **package_ids = pk_backend_get_strv (backend, "package_ids");

	/* create a new transaction */
	transaction = pacman_manager_sync (pacman, PACMAN_TRANSACTION_FLAGS_NONE, &error);
	if (transaction == NULL) {
		backend_error (backend, error);
		pk_backend_finished (backend);
		return FALSE;
	}

	/* add targets to the transaction */
	for (iterator = 0; package_ids[iterator] != NULL; ++iterator) {
		gchar **package_id_data = pk_package_id_split (package_ids[iterator]);
		list = pacman_list_add (list, g_strdup (package_id_data[PK_PACKAGE_ID_NAME]));
		g_strfreev (package_id_data);
	}

	/* prepare and commit transaction */
	result = backend_transaction_run (backend, transaction, list, &error);

	pacman_list_free_full (list, g_free);
	g_object_unref (transaction);

	pk_backend_finished (backend);
	return result;
}

/**
 * backend_install_packages:
 */
static void
backend_install_packages (PkBackend *backend, gboolean only_trusted, gchar **package_ids)
{
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);

	pk_backend_thread_create (backend, backend_install_packages_thread);
}

/**
 * backend_refresh_cache_thread:
 */
static gboolean
backend_refresh_cache_thread (PkBackend *backend)
{
	PacmanTransaction *transaction;
	PacmanTransactionFlags flags = PACMAN_TRANSACTION_FLAGS_NONE;
	gboolean result;
	GError *error = NULL;

	if (pk_backend_get_bool (backend, "force"))
		flags |= PACMAN_TRANSACTION_FLAGS_UPDATE_ALLOW_DOWNGRADE;

	/* create a new transaction */
	transaction = pacman_manager_update (pacman, flags, &error);
	if (transaction == NULL) {
		backend_error (backend, error);
		pk_backend_finished (backend);
		return FALSE;
	}

	/* prepare and commit transaction */
	result = backend_transaction_run (backend, transaction, NULL, &error);

	g_object_unref (transaction);

	pk_backend_finished (backend);
	return result;
}

/**
 * backend_refresh_cache:
 */
static void
backend_refresh_cache (PkBackend *backend, gboolean force)
{
	if (!pk_backend_is_online (backend)) {
		pk_backend_error_code (backend, PK_ERROR_ENUM_NO_NETWORK, "Can not refresh cache in offline mode");
		pk_backend_finished (backend);
		return;
	}

	pk_backend_set_status (backend, PK_STATUS_ENUM_REFRESH_CACHE);
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);

	pk_backend_thread_create (backend, backend_refresh_cache_thread);
}

/**
 * backend_remove_packages_thread:
 */
static gboolean
backend_remove_packages_thread (PkBackend *backend)
{
	PacmanTransaction *transaction;
	guint iterator;
	PacmanList *list = NULL;
	gboolean result;
	GError *error = NULL;

	gchar **package_ids = pk_backend_get_strv (backend, "package_ids");

	PacmanTransactionFlags flags = PACMAN_TRANSACTION_FLAGS_NONE;
	if (pk_backend_get_bool (backend, "allow_deps"))
		flags |= PACMAN_TRANSACTION_FLAGS_REMOVE_CASCADE;
	if (pk_backend_get_bool (backend, "autoremove"))
		flags |= PACMAN_TRANSACTION_FLAGS_REMOVE_RECURSIVE;

	/* create a new transaction */
	transaction = pacman_manager_remove (pacman, flags, &error);
	if (transaction == NULL) {
		backend_error (backend, error);
		pk_backend_finished (backend);
		return FALSE;
	}

	/* add targets to the transaction */
	for (iterator = 0; package_ids[iterator] != NULL; ++iterator) {
		gchar **package_id_data = pk_package_id_split (package_ids[iterator]);
		list = pacman_list_add (list, g_strdup (package_id_data[PK_PACKAGE_ID_NAME]));
		g_strfreev (package_id_data);
	}

	/* prepare transaction */
	result = backend_transaction_run (backend, transaction, list, &error);
	
	pacman_list_free_full (list, g_free);
	g_object_unref (transaction);

	pk_backend_finished (backend);
	return result;
}

/**
 * backend_remove_packages:
 */
static void
backend_remove_packages (PkBackend *backend, gchar **package_ids, gboolean allow_deps, gboolean autoremove)
{
	pk_backend_set_status (backend, PK_STATUS_ENUM_REMOVE);
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);

	pk_backend_thread_create (backend, backend_remove_packages_thread);
}

/**
 * backend_resolve_thread:
 */
static gboolean
backend_resolve_thread (PkBackend *backend)
{
	guint iterator;

	gchar **package_ids = pk_backend_get_strv (backend, "package_ids");
	PkBitfield filters = pk_backend_get_uint (backend, "filters");

	gboolean search_installed = pk_bitfield_contain (filters, PK_FILTER_ENUM_INSTALLED);
	gboolean search_not_installed = pk_bitfield_contain (filters, PK_FILTER_ENUM_NOT_INSTALLED);

	for (iterator = 0; package_ids[iterator] != NULL; ++iterator) {
		PacmanDatabase *database;

		PacmanPackage *package = package_from_package_id (package_ids[iterator]);
		if (package == NULL) {
			pk_backend_error_code (backend, PK_ERROR_ENUM_PACKAGE_ID_INVALID, "Could not find package with ID %s", package_ids[iterator]);
			pk_backend_finished (backend);
			return FALSE;
		}
		
		database = pacman_package_get_database (package);
		if (!search_not_installed && database == pacman_manager_get_local_database (pacman))
			emit_package (backend, package, PACMAN_LOCAL_DB_ALIAS, PK_INFO_ENUM_INSTALLED);
		if (!search_installed && database != pacman_manager_get_local_database (pacman))
			emit_package (backend, package, pacman_database_get_name (database), PK_INFO_ENUM_AVAILABLE);
	}

	pk_backend_finished (backend);
	return TRUE;
}

/**
 * backend_resolve:
 */
static void
backend_resolve (PkBackend *backend, PkBitfield filters, gchar **package_ids)
{
	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);

	pk_backend_thread_create (backend, backend_resolve_thread);
}

/**
 * backend_search_thread:
 */
static gboolean
backend_search_thread (PkBackend *backend)
{
	gchar **values = pk_backend_get_strv (backend, "search");
	PkBitfield filters = pk_backend_get_uint (backend, "filters");
	PkAlpmSearchType search_type = pk_backend_get_uint (backend, "search-type");

	gboolean search_installed = pk_bitfield_contain (filters, PK_FILTER_ENUM_INSTALLED);
	gboolean search_not_installed = pk_bitfield_contain (filters, PK_FILTER_ENUM_NOT_INSTALLED);

	if (!search_not_installed) {
		/* search in local db */
		backend_search_values (backend, pacman_manager_get_local_database (pacman), values, search_type);
	}

	if (!search_installed) {
		/* search in sync repos */
		const PacmanList *databases;
		for (databases = pacman_manager_get_sync_databases (pacman); databases != NULL; databases = pacman_list_next (databases))
			backend_search_values (backend, (PacmanDatabase *) pacman_list_get (databases), values, search_type);
	}

	pk_backend_finished (backend);
	return TRUE;
}

/**
 * backend_search_details:
 */
static void
backend_search_details (PkBackend *backend, PkBitfield filters, gchar **values)
{
	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);
	pk_backend_set_uint (backend, "search-type", PK_ALPM_SEARCH_TYPE_DETAILS);

	pk_backend_thread_create (backend, backend_search_thread);
}

/**
 * backend_search_groups:
 */
static void
backend_search_groups (PkBackend *backend, PkBitfield filters, gchar **values)
{
	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);
	pk_backend_set_uint (backend, "search-type", PK_ALPM_SEARCH_TYPE_GROUP);

	pk_backend_thread_create (backend, backend_search_thread);
}

/**
 * backend_search_names:
 */
static void
backend_search_names (PkBackend *backend, PkBitfield filters, gchar **values)
{
	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);
	pk_backend_set_uint (backend, "search-type", PK_ALPM_SEARCH_TYPE_NAME);

	pk_backend_thread_create (backend, backend_search_thread);
}

/**
 * backend_update_packages:
 */
static void
backend_update_packages (PkBackend *backend, gboolean only_trusted, gchar **package_ids)
{
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);

	pk_backend_thread_create (backend, backend_install_packages_thread);
}

/**
 * backend_update_system_thread:
 */
static gboolean
backend_update_system_thread (PkBackend *backend)
{
	PacmanTransaction *transaction;
	gboolean result;
	GError *error = NULL;

	/* FIXME: support only_trusted */

	/* create a new transaction */
	transaction = pacman_manager_sync (pacman, PACMAN_TRANSACTION_FLAGS_NONE, &error);
	if (transaction == NULL) {
		backend_error (backend, error);
		pk_backend_finished (backend);
		return FALSE;
	}

	/* set action, prepare and commit transaction */
	result = backend_transaction_run (backend, transaction, NULL, &error);

	g_object_unref (transaction);

	pk_backend_finished (backend);
	return result;
}

/**
 * backend_update_system:
 */
static void
backend_update_system (PkBackend *backend, gboolean only_trusted)
{
	pk_backend_thread_create (backend, backend_update_system_thread);
}

/**
 * backend_what_provides:
 */
static void
backend_what_provides (PkBackend *backend, PkBitfield filters, PkProvidesEnum provides, gchar **values)
{
	pk_backend_set_status (backend, PK_STATUS_ENUM_QUERY);
	pk_backend_set_percentage (backend, PK_BACKEND_PERCENTAGE_INVALID);
	pk_backend_set_uint (backend, "search-type", PK_ALPM_SEARCH_TYPE_PROVIDES);

	pk_backend_thread_create (backend, backend_search_thread);
}

PK_BACKEND_OPTIONS (
	"alpm",						/* description */
	"Valeriy Lyasotskiy <onestep@ukr.net>",		/* author */
	backend_initialize,				/* initialize */
	backend_destroy,				/* destroy */
	backend_get_groups,				/* get_groups */
	backend_get_filters,				/* get_filters */
	NULL,						/* get_roles */
	backend_get_mime_types,				/* get_mime_types */
	backend_cancel,					/* cancel */
	backend_download_packages,			/* download_packages */
	NULL,						/* get_categories */
	backend_get_depends,				/* get_depends */
	backend_get_details,				/* get_details */
	NULL,						/* get_distro_upgrades */
	backend_get_files,				/* get_files */
	backend_get_packages,				/* get_packages */
	backend_get_repo_list,				/* get_repo_list */
	NULL,						/* get_requires */
	backend_get_update_detail,			/* get_update_detail */
	backend_get_updates,				/* get_updates */
	backend_install_files,				/* install_files */
	backend_install_packages,			/* install_packages */
	NULL,						/* install_signature */
	backend_refresh_cache,				/* refresh_cache */
	backend_remove_packages,			/* remove_packages */
	NULL,						/* repo_enable */
	NULL,						/* repo_set_data */
	backend_resolve,				/* resolve */
	NULL,						/* rollback */
	backend_search_details,				/* search_details */
	NULL,						/* search_files */
	backend_search_groups,				/* search_groups */
	backend_search_names,				/* search_names */
	backend_update_packages,			/* update_packages */
	backend_update_system,				/* update_system */
	backend_what_provides,				/* what_provides */
	NULL,						/* simulate_install_files */
	NULL,						/* simulate_install_packages */
	NULL,						/* simulate_remove_packages */
	NULL						/* simulate_update_packages */
);
