/* pacman-database.c
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

#include <alpm.h>
#include "pacman-list.h"
#include "pacman-database.h"

/**
 * SECTION:pacman-database
 * @title: PacmanDatabase
 * @short_description: Package databases
 *
 * A #PacmanDatabase (commonly known as a repository) contains a list of packages and groups. These can be searched for specific packages, and should be updated periodically.
 */

/**
 * PacmanDatabase:
 *
 * Represents a package database.
 */

/**
 * pacman_database_get_name:
 * @database: A #PacmanDatabase.
 *
 * Gets the name of @database.
 *
 * Returns: A database name. Do not free.
 */
const gchar *pacman_database_get_name (PacmanDatabase *database) {
	g_return_val_if_fail (database != NULL, NULL);
	
	return alpm_db_get_name (database);
}

/**
 * pacman_database_get_server:
 * @database: A #PacmanDatabase.
 *
 * Gets the primary mirror that will be used to download files from @database.
 *
 * Returns: A server URL. Do not free.
 */
const gchar *pacman_database_get_server (PacmanDatabase *database) {
	g_return_val_if_fail (database != NULL, NULL);
	
	return alpm_db_get_url (database);
}

/**
 * pacman_database_add_server:
 * @database: A sync #PacmanDatabase.
 * @url: The url of a server.
 *
 * Adds @url to the list of mirrors that will be used to download files from @database.
 */
void pacman_database_add_server (PacmanDatabase *database, const gchar *url) {
	g_return_if_fail (database != NULL);
	g_return_if_fail (database != alpm_option_get_localdb ());
	g_return_if_fail (url != NULL);
	
	alpm_db_setserver (database, url);
}

/**
 * pacman_database_get_packages:
 * @database: A #PacmanDatabase.
 *
 * Gets a list of packages contained in @database.
 *
 * Returns: A list of #PacmanPackage. Do not free.
 */
const PacmanList *pacman_database_get_packages (PacmanDatabase *database) {
	g_return_val_if_fail (database != NULL, NULL);
	
	return alpm_db_get_pkgcache (database);
}

/**
 * pacman_database_get_groups:
 * @database: A #PacmanDatabase.
 *
 * Gets a list of groups contained in @database.
 *
 * Returns: A list of #PacmanGroup. Do not free.
 */
const PacmanList *pacman_database_get_groups (PacmanDatabase *database) {
	g_return_val_if_fail (database != NULL, NULL);
	
	return alpm_db_get_grpcache (database);
}

/**
 * pacman_database_find_package:
 * @database: A #PacmanDatabase.
 * @name: The name of a package.
 *
 * Finds a package named @name in @database.
 *
 * Returns: A #PacmanPackage, or %NULL if none were found. Do not free.
 */
PacmanPackage *pacman_database_find_package (PacmanDatabase *database, const gchar *name) {
	g_return_val_if_fail (database != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	
	return alpm_db_get_pkg (database, name);
}

/**
 * pacman_database_find_group:
 * @database: A #PacmanDatabase.
 * @name: The name of a group.
 *
 * Finds a group named @name in @database.
 *
 * Returns: A #PacmanGroup, or %NULL if none were found. Do not free.
 */
PacmanGroup *pacman_database_find_group (PacmanDatabase *database, const gchar *name) {
	g_return_val_if_fail (database != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	
	return alpm_db_readgrp (database, name);
}

/**
 * pacman_database_search:
 * @database: A #PacmanDatabase.
 * @needles: A list of strings and/or regular expressions.
 *
 * Finds packages in @database with a name or description containing something in @needles. If @needles is empty, every package in @database is returned instead.
 *
 * Returns: A list of #PacmanPackage. Free with pacman_list_free().
 */
PacmanList *pacman_database_search (PacmanDatabase *database, const PacmanList *needles) {
	g_return_val_if_fail (database != NULL, NULL);
	
	/* TODO: can probably do this faster ourselves */
	if (needles != NULL) {
		return alpm_db_search (database, needles);
	} else {
		return pacman_list_copy (pacman_database_get_packages (database));
	}
}
