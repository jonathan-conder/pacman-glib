#include <stdlib.h>
#include <alpm.h>
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
