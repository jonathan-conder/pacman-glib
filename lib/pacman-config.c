/* pacman-config.c
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

#include <sys/utsname.h>
#include <string.h>
#include <glob.h>
#include <glib/gi18n-lib.h>
#include <gio/gio.h>
#include "pacman-error.h"
#include "pacman-list.h"
#include "pacman-database.h"
#include "pacman-manager.h"

typedef struct {
	gboolean i_love_candy;
	gboolean show_size;
	gboolean total_download;
	gboolean use_delta;
	gboolean use_syslog;
	
	gchar *architecture;
	gchar *clean_method;
	gchar *database_path;
	gchar *log_file;
	gchar *root_path;
	gchar *transfer_command;
	
	PacmanList *cache_paths;
	PacmanList *hold_packages;
	PacmanList *ignore_groups;
	PacmanList *ignore_packages;
	PacmanList *no_extracts;
	PacmanList *no_upgrades;
	PacmanList *sync_firsts;
	
	PacmanList *databases;
	GHashTable *servers;
} PacmanConfig;

static PacmanConfig *pacman_config_new (void) {
	PacmanConfig *result = (PacmanConfig *) g_new0 (PacmanConfig, 1);
	
	result->servers = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
	return result;
}

static gboolean pacman_config_servers_free (gpointer database, gpointer list, gpointer user_data) {
	pacman_list_free_full ((PacmanList *) list, (GDestroyNotify) g_free);
	return TRUE;
}

static void pacman_config_free (PacmanConfig *config) {
	GHashTableIter iter;
	gpointer key, value;
	
	g_return_if_fail (config != NULL);
	
	g_free (config->architecture);
	g_free (config->clean_method);
	g_free (config->database_path);
	g_free (config->log_file);
	g_free (config->root_path);
	g_free (config->transfer_command);
	
	pacman_list_free_full (config->cache_paths, (GDestroyNotify) g_free);
	pacman_list_free_full (config->hold_packages, (GDestroyNotify) g_free);
	pacman_list_free_full (config->ignore_groups, (GDestroyNotify) g_free);
	pacman_list_free_full (config->ignore_packages, (GDestroyNotify) g_free);
	pacman_list_free_full (config->no_extracts, (GDestroyNotify) g_free);
	pacman_list_free_full (config->no_upgrades, (GDestroyNotify) g_free);
	pacman_list_free_full (config->sync_firsts, (GDestroyNotify) g_free);
	
	pacman_list_free_full (config->databases, (GDestroyNotify) g_free);
	g_hash_table_foreach_remove (config->servers, pacman_config_servers_free, NULL);
	g_hash_table_unref (config->servers);
}

static void pacman_config_set_i_love_candy (PacmanConfig *config, gboolean value) {
	g_return_if_fail (config != NULL);
	
	config->i_love_candy = value;
}

static void pacman_config_set_show_size (PacmanConfig *config, gboolean value) {
	g_return_if_fail (config != NULL);
	
	config->show_size = value;
}

static void pacman_config_set_total_download (PacmanConfig *config, gboolean value) {
	g_return_if_fail (config != NULL);
	
	config->total_download = value;
}

static void pacman_config_set_use_delta (PacmanConfig *config, gboolean value) {
	g_return_if_fail (config != NULL);
	
	config->use_delta = value;
}

static void pacman_config_set_use_syslog (PacmanConfig *config, gboolean value) {
	g_return_if_fail (config != NULL);
	
	config->use_syslog = value;
}

typedef struct {
	const gchar *name;
	void (*func) (PacmanConfig *config, gboolean value);
} PacmanConfigBoolean;

/* keep this in alphabetical order */
static const PacmanConfigBoolean pacman_config_boolean_options[] = {
	{ "ILoveCandy", pacman_config_set_i_love_candy },
	{ "ShowSize", pacman_config_set_show_size },
	{ "TotalDownload", pacman_config_set_total_download },
	{ "UseDelta", pacman_config_set_use_delta },
	{ "UseSyslog", pacman_config_set_use_syslog },
	{ NULL, NULL }
};

static void pacman_config_add_cache_path (PacmanConfig *config, const gchar *path) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (path != NULL);
	
	config->cache_paths = pacman_list_add (config->cache_paths, g_strdup (path));
}

static void pacman_config_set_architecture (PacmanConfig *config, const gchar *architecture) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (architecture != NULL);
	
	g_free (config->architecture);
	if (g_strcmp0 (architecture, "auto") == 0) {
		struct utsname un;
		uname (&un);
		config->architecture = g_strdup (un.machine);
	} else {
		config->architecture = g_strdup (architecture);
	}
}

static void pacman_config_set_clean_method (PacmanConfig *config, const gchar *method) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (method != NULL);
	
	g_free (config->clean_method);
	config->clean_method = g_strdup (method);
}

static void pacman_config_set_database_path (PacmanConfig *config, const gchar *path) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (path != NULL);
	
	g_free (config->database_path);
	config->database_path = g_strdup (path);
}

static void pacman_config_set_log_file (PacmanConfig *config, const gchar *filename) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (filename != NULL);
	
	g_free (config->log_file);
	config->log_file = g_strdup (filename);
}

static void pacman_config_set_root_path (PacmanConfig *config, const gchar *path) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (path != NULL);
	
	g_free (config->root_path);
	config->root_path = g_strdup (path);
}

static void pacman_config_set_transfer_command (PacmanConfig *config, const gchar *command) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (command != NULL);
	
	g_free (config->transfer_command);
	config->transfer_command = g_strdup (command);
}

typedef struct {
	const gchar *name;
	void (*func) (PacmanConfig *config, const gchar *value);
} PacmanConfigString;

/* keep this in alphabetical order */
static const PacmanConfigString pacman_config_string_options[] = {
	{ "Architecture", pacman_config_set_architecture },
	{ "CacheDir", pacman_config_add_cache_path },
	{ "CleanMethod", pacman_config_set_clean_method },
	{ "DBPath", pacman_config_set_database_path },
	{ "LogFile", pacman_config_set_log_file },
	{ "RootDir", pacman_config_set_root_path },
	{ "XferCommand", pacman_config_set_transfer_command },
	{ NULL, NULL }
};

static void pacman_config_add_hold_package (PacmanConfig *config, const gchar *package) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (package != NULL);
	
	config->hold_packages = pacman_list_add (config->hold_packages, g_strdup (package));
}

static void pacman_config_add_ignore_group (PacmanConfig *config, const gchar *group) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (group != NULL);
	
	config->ignore_groups = pacman_list_add (config->ignore_groups, g_strdup (group));
}

static void pacman_config_add_ignore_package (PacmanConfig *config, const gchar *package) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (package != NULL);
	
	config->ignore_packages = pacman_list_add (config->ignore_packages, g_strdup (package));
}

static void pacman_config_add_no_extract (PacmanConfig *config, const gchar *filename) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (filename != NULL);
	
	config->no_extracts = pacman_list_add (config->no_extracts, g_strdup (filename));
}

static void pacman_config_add_no_upgrade (PacmanConfig *config, const gchar *filename) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (filename != NULL);
	
	config->no_upgrades = pacman_list_add (config->no_upgrades, g_strdup (filename));
}

static void pacman_config_add_sync_first (PacmanConfig *config, const gchar *package) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (package != NULL);
	
	config->sync_firsts = pacman_list_add (config->sync_firsts, g_strdup (package));
}

typedef struct {
	const gchar *name;
	void (*func) (PacmanConfig *config, const gchar *value);
} PacmanConfigList;

/* keep this in alphabetical order */
static const PacmanConfigList pacman_config_list_options[] = {
	{ "HoldPkg", pacman_config_add_hold_package },
	{ "IgnoreGroup", pacman_config_add_ignore_group },
	{ "IgnorePkg", pacman_config_add_ignore_package },
	{ "NoExtract", pacman_config_add_no_extract },
	{ "NoUpgrade", pacman_config_add_no_upgrade },
	{ "SyncFirst", pacman_config_add_sync_first },
	{ NULL, NULL }
};

static void pacman_config_add_database (PacmanConfig *config, const gchar *name) {
	g_return_if_fail (config != NULL);
	g_return_if_fail (name != NULL);
	
	if (pacman_list_find_string (config->databases, name) == NULL) {
		config->databases = pacman_list_add (config->databases, g_strdup (name));
	}
}

static void pacman_config_database_add_server (PacmanConfig *config, const gchar *name, const gchar *url) {
	PacmanList *list;
	
	g_return_if_fail (config != NULL);
	g_return_if_fail (name != NULL);
	g_return_if_fail (pacman_list_find_string (config->databases, name) != NULL);
	g_return_if_fail (url != NULL);
	
	list = (PacmanList *) g_hash_table_lookup (config->servers, name);
	list = pacman_list_add (list, g_strdup (url));
	g_hash_table_insert (config->servers, g_strdup (name), list);
}

static gboolean pacman_config_read_line (GDataInputStream *data_stream, gchar **line, GError **error) {
	g_free (*line);
	*line = g_data_input_stream_read_line (data_stream, NULL, NULL, error);
	return *line != NULL;
}

static gboolean pacman_config_parse (PacmanConfig *config, const gchar *filename, gchar *section, GError **error) {
	GFile *file;
	GFileInputStream *file_stream;
	GDataInputStream *data_stream;
	
	GRegex *repo = NULL, *arch = NULL;
	GError *e = NULL;
	
	gchar *key, *str, *line = NULL;
	gint i, num = 0;
	
	g_return_if_fail (config != NULL);
	g_return_if_fail (filename != NULL);
	
	file = g_file_new_for_path (filename);
	file_stream = g_file_read (file, NULL, &e);
	
	if (file_stream == NULL) {
		g_propagate_error (error, e);
		g_object_unref (file);
		return FALSE;
	}
	
	data_stream = g_data_input_stream_new (G_INPUT_STREAM (file_stream));
	section = g_strdup (section);
	
	while (pacman_config_read_line (data_stream, &line, &e)) {
		++num;
		g_strstrip (line);
		
		if (*line == '\0' || *line == '#') {
			continue;
		}
		
		str = strchr (line, '#');
		if (str != NULL) {
			*str = '\0';
		} else {
			for (str = line; *str != '\0'; ++str);
		}
		
		if (*line == '[' && *(--str) == ']') {
			*str = '\0';
			str = line + 1;
			
			if (*str == '\0') {
				g_set_error (&e, PACMAN_ERROR, PACMAN_ERROR_CONFIG_INVALID, _("Empty section name in %s on line %d"), filename, num);
				break;
			}
			
			g_free (section);
			section = g_strdup (str);
			
			if (g_strcmp0 (section, "options") != 0) {
				pacman_config_add_database (config, section);
			}
		} else {
			if (section == NULL) {
				g_set_error (&e, PACMAN_ERROR, PACMAN_ERROR_CONFIG_INVALID, _("Directive must belong to a section in %s on line %d"), filename, num);
				break;
			}
			
			str = line;
			key = strsep (&str, "=");
			g_strchomp (key);
			
			if (str == NULL) {
				if (g_strcmp0 (section, "options") == 0) {
					for (i = 0; pacman_config_boolean_options[i].name != NULL; ++i) {
						if (g_strcmp0 (key, pacman_config_boolean_options[i].name) == 0) {
							pacman_config_boolean_options[i].func (config, TRUE);
							break;
						}
					}
					
					if (pacman_config_boolean_options[i].name == NULL) {
						g_set_error (&e, PACMAN_ERROR, PACMAN_ERROR_CONFIG_INVALID, _("Unrecognised directive %s in %s on line %d"), key, filename, num);
						break;
					}
				} else {
					g_set_error (&e, PACMAN_ERROR, PACMAN_ERROR_CONFIG_INVALID, _("Unrecognised directive %s in %s on line %d"), key, filename, num);
					break;
				}
			} else {
				g_strchug (str);
				
				if (g_strcmp0 (key, "Include") == 0) {
					glob_t match;
					gsize i;
					
					if (glob (str, GLOB_NOCHECK, NULL, &match) == 0) {
						for (i = 0; i < match.gl_pathc; ++i) {
							if (!pacman_config_parse (config, match.gl_pathv[i], section, &e)) {
								break;
							}
						}
					}
					
					globfree (&match);
					if (e != NULL) {
						break;
					}
				} else if (g_strcmp0 (section, "options") == 0) {
					for (i = 0; pacman_config_string_options[i].name != NULL; ++i) {
						if (g_strcmp0 (key, pacman_config_string_options[i].name) == 0) {
							pacman_config_string_options[i].func (config, str);
							break;
						}
					}
					
					if (pacman_config_string_options[i].name == NULL) {
						for (i = 0; pacman_config_list_options[i].name != NULL; ++i) {
							if (g_strcmp0 (key, pacman_config_list_options[i].name) == 0) {
								while ((key = strchr (str, ' ')) != NULL) {
									*key = '\0';
									pacman_config_list_options[i].func (config, str);
									str = key + 1;
								}
								pacman_config_list_options[i].func (config, str);
								break;
							}
						}
						
						if (pacman_config_list_options[i].name == NULL) {
							g_set_error (&e, PACMAN_ERROR, PACMAN_ERROR_CONFIG_INVALID, _("Unrecognised directive %s in %s on line %d"), key, filename, num);
							break;
						}
					}
				} else if (g_strcmp0 (key, "Server") == 0) {
					gchar *server, *temp;
					
					/* initialize here so we don't waste time in option files */
					if (repo == NULL) {
						repo = g_regex_new ("\\$repo", 0, 0, &e);
						if (repo == NULL) {
							break;
						}
					}
					if (arch == NULL) {
						arch = g_regex_new ("\\$arch", 0, 0, &e);
						if (arch == NULL) {
							break;
						}
					}
					
					temp = g_regex_replace_literal (repo, str, -1, 0, section, 0, &e);
					if (temp == NULL) {
						break;
					}
					
					if (config->architecture != NULL) {
						server = g_regex_replace_literal (arch, temp, -1, 0, config->architecture, 0, &e);
						g_free (temp);
						if (server == NULL) {
							break;
						}
					} else if (strstr (temp, "$arch") == NULL) {
						server = temp;
					} else {
						g_set_error (&e, PACMAN_ERROR, PACMAN_ERROR_CONFIG_INVALID, _("Server contained $arch but none is defined in %s on line %d"), filename, num);
						g_free (temp);
						break;
					}
					
					pacman_config_database_add_server (config, section, server);
					
					g_free (server);
				} else {
					g_set_error (&e, PACMAN_ERROR, PACMAN_ERROR_CONFIG_INVALID, _("Unrecognised directive %s in %s on line %d"), key, filename, num);
					break;
				}
			}
		}
	}
	
	g_free (line);
	g_free (section);
	
	if (repo != NULL) {
		g_regex_unref (repo);
	}
	if (arch != NULL) {
		g_regex_unref (arch);
	}
	
	g_object_unref (data_stream);
	g_object_unref (file_stream);
	g_object_unref (file);
	
	if (e != NULL) {
		g_propagate_error (error, e);
		return FALSE;
	} else {
		return TRUE;
	}
}

static gboolean pacman_config_configure_paths (PacmanConfig *config, PacmanManager *manager, GError **error) {
	g_return_val_if_fail (config != NULL, FALSE);
	g_return_val_if_fail (manager != NULL, FALSE);
	
	if (config->root_path == NULL) {
		config->root_path = g_strdup (PACMAN_ROOT_PATH);
	}
	if (!pacman_manager_set_root_path (manager, config->root_path, error)) {
		return FALSE;
	}
	
	if (config->database_path == NULL) {
		config->database_path = g_strconcat (pacman_manager_get_root_path (manager), PACMAN_DATABASE_PATH + 1, NULL);
	}
	if (!pacman_manager_set_database_path (manager, config->database_path, error)) {
		return FALSE;
	}
	
	if (config->log_file == NULL) {
		config->log_file = g_strconcat (pacman_manager_get_root_path (manager), PACMAN_LOG_FILE + 1, NULL);
	}
	pacman_manager_set_log_file (manager, config->log_file);
	
	if (config->cache_paths == NULL) {
		gchar *path = g_strconcat (pacman_manager_get_root_path (manager), PACMAN_CACHE_PATH + 1, NULL);
		config->cache_paths = pacman_list_add (config->cache_paths, path);
	}
	pacman_manager_set_cache_paths (manager, config->cache_paths);
	
	return TRUE;
}

static gboolean pacman_config_configure_databases (PacmanConfig *config, PacmanManager *manager, GError **error) {
	const PacmanList *databases;
	
	g_return_val_if_fail (config != NULL, FALSE);
	g_return_val_if_fail (manager != NULL, FALSE);
	
	if (config->databases == NULL) {
		return TRUE;
	}
	
	if (!pacman_manager_unregister_all_databases (manager, error) || pacman_manager_register_local_database (manager, error) == NULL) {
		return FALSE;
	}
	
	for (databases = config->databases; databases != NULL; databases = pacman_list_next (databases)) {
		PacmanDatabase *database;
		PacmanList *i;
		const gchar *name = (const gchar *) pacman_list_get (databases);
		
		database = pacman_manager_register_sync_database (manager, name, error);
		if (database == NULL) {
			return FALSE;
		}
		
		for (i = (PacmanList *) g_hash_table_lookup (config->servers, name); i != NULL; i = pacman_list_next (i)) {
			const gchar *url = (const gchar *) pacman_list_get (i);
			g_return_val_if_fail (url != NULL, FALSE);
			
			pacman_database_add_server (database, url);
		}
	}
	
	return TRUE;
}

static gboolean pacman_config_configure_manager (PacmanConfig *config, PacmanManager *manager, GError **error) {
	g_return_val_if_fail (config != NULL, FALSE);
	g_return_val_if_fail (manager != NULL, FALSE);
	
	if (!pacman_config_configure_paths (config, manager, error)) {
		return FALSE;
	}
	
	pacman_manager_set_i_love_candy (manager, config->i_love_candy);
	pacman_manager_set_show_size (manager, config->show_size);
	pacman_manager_set_total_download (manager, config->total_download);
	pacman_manager_set_use_delta (manager, config->use_delta);
	pacman_manager_set_use_syslog (manager, config->use_syslog);
	
	if (config->architecture != NULL) {
		pacman_manager_set_architecture (manager, config->architecture);
	}
	if (config->clean_method != NULL) {
		pacman_manager_set_clean_method (manager, config->clean_method);
	}
	pacman_manager_set_transfer_command (manager, config->transfer_command);
	
	if (config->hold_packages != NULL) {
		pacman_manager_set_hold_packages (manager, config->hold_packages);
	}
	if (config->sync_firsts != NULL) {
		pacman_manager_set_sync_firsts (manager, config->sync_firsts);
	}
	if (config->ignore_groups != NULL) {
		pacman_manager_set_ignore_groups (manager, config->ignore_groups);
	}
	if (config->ignore_packages != NULL) {
		pacman_manager_set_ignore_packages (manager, config->ignore_packages);
	}
	if (config->no_extracts != NULL) {
		pacman_manager_set_no_extracts (manager, config->no_extracts);
	}
	if (config->no_upgrades != NULL) {
		pacman_manager_set_no_upgrades (manager, config->no_upgrades);
	}
	
	if (!pacman_config_configure_databases (config, manager, error)) {
		return FALSE;
	}
	
	return TRUE;
}

/**
 * pacman_manager_configure:
 * @manager: A #PacmanManager.
 * @filename: The location of a config file, or %NULL for the default.
 * @error: A #GError, or %NULL.
 *
 * Reads the options specified in @filename and configures @manager with them. These options will override any previously specified settings.
 *
 * Returns: %TRUE if @manager was configured successfully, or %FALSE if @error is set.
 */
gboolean pacman_manager_configure (PacmanManager *manager, const gchar *filename, GError **error) {
	PacmanConfig *config;
	
	g_return_val_if_fail (manager != NULL, FALSE);
	
	config = pacman_config_new ();
	if (filename == NULL) {
		filename = PACMAN_CONFIG_FILE;
	}
	
	if (!pacman_config_parse (config, filename, NULL, error) || !pacman_config_configure_manager (config, manager, error)) {
		pacman_config_free (config);
		return FALSE;
	}
	
	pacman_config_free (config);
	return TRUE;
}
