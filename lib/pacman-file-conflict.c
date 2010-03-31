/* pacman-file-conflict.c
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
#include "pacman-list.h"
#include "pacman-file-conflict.h"

/**
 * SECTION:pacman-file-conflict
 * @title: PacmanFileConflict
 * @short_description: File conflicts
 *
 * A #PacmanFileConflict describes a situation where a package contains a file that cannot be installed. This could be because the file already exists on the system, or because another package also contains that file.
 */

/**
 * PacmanFileConflict:
 *
 * Represents a file conflict between a package and either the filesystem or another package.
 */

void pacman_file_conflict_free (PacmanFileConflict *conflict) {
	/* this is a hack, but it's better than a memory leak */
	gchar *package = (gchar *) pacman_file_conflict_get_second_package (conflict);
	if (package != NULL && *package != '\0') {
		free (package);
	}
	
	free ((gchar *) pacman_file_conflict_get_package (conflict));
	free ((gchar *) pacman_file_conflict_get_file (conflict));
	free (conflict);
}

/**
 * pacman_file_conflict_get_package:
 * @conflict: A #PacmanFileConflict.
 *
 * Gets the name of the package that contains the conflicting file for @conflict.
 *
 * Returns: A package name. Do not free.
 */
const gchar *pacman_file_conflict_get_package (PacmanFileConflict *conflict) {
	g_return_val_if_fail (conflict != NULL, NULL);
	
	return alpm_fileconflict_get_target (conflict);
}

/**
 * pacman_file_conflict_get_file:
 * @conflict: A #PacmanFileConflict.
 *
 * Gets the location of the conflicting file for @conflict.
 *
 * Returns: A file name. Do not free.
 */
const gchar *pacman_file_conflict_get_file (PacmanFileConflict *conflict) {
	g_return_val_if_fail (conflict != NULL, NULL);
	
	return alpm_fileconflict_get_file (conflict);
}

/**
 * pacman_file_conflict_get_second_package:
 * @conflict: A #PacmanFileConflict.
 *
 * Gets the name of the second package that contains the conflicting file for @conflict.
 *
 * Returns: A package name, or %NULL if @conflict does not involve a second package. Do not free.
 */
const gchar *pacman_file_conflict_get_second_package (PacmanFileConflict *conflict) {
	g_return_val_if_fail (conflict != NULL, NULL);
	
	if (alpm_fileconflict_get_type (conflict) == PM_FILECONFLICT_FILESYSTEM) {
		return NULL;
	} else {
		return alpm_fileconflict_get_ctarget (conflict);
	}
}

/**
 * pacman_file_conflict_make_list:
 * @conflicts: A list of #PacmanFileConflict.
 *
 * Creates a list of file conflict strings from @conflicts.
 *
 * Returns: A newline-separated string. Free with g_free().
 */
gchar *pacman_file_conflict_make_list (const PacmanList *conflicts) {
	GString *result;
	const PacmanList *i;
	
	result = g_string_new (_("Conflicting files:"));
	
	for (i = conflicts; i != NULL; i = pacman_list_next (i)) {
		PacmanFileConflict *conflict = (PacmanFileConflict *) pacman_list_get (i);
		const gchar *package = pacman_file_conflict_get_package (conflict);
		const gchar *file = pacman_file_conflict_get_file (conflict);
		
		g_string_append_printf (result, _("\n%s contains %s"), package, file);
		
		package = pacman_file_conflict_get_second_package (conflict);
		if (package != NULL) {
			g_string_append_printf (result, _(", which is also in %s"), package);
		} else {
			g_string_append (result, _(", which is on the filesystem"));
		}
	}
	
	return g_string_free (result, FALSE);
}
