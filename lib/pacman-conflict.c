#include <stdlib.h>
#include <alpm.h>
#include "pacman-conflict.h"

/**
 * SECTION:pacman-conflict
 * @title: PacmanConflict
 * @short_description: Dependency conflicts
 *
 * A #PacmanConflict represents a dependency conflict between two packages.
 */

/**
 * PacmanConflict:
 *
 * Represents a dependency conflict between two packages.
 */

/**
 * pacman_conflict_free:
 * @conflict: A #PacmanConflict.
 *
 * Frees @conflict.
 */
void pacman_conflict_free (PacmanConflict *conflict) {
	/* this is a hack, but it's better than a memory leak */
	free ((gchar *) pacman_conflict_get_first_package (conflict));
	free ((gchar *) pacman_conflict_get_second_package (conflict));
	free (conflict);
}

/**
 * pacman_conflict_get_first_package:
 * @conflict: A #PacmanConflict.
 *
 * Gets the name of the first package that conflicts for @conflict.
 *
 * Returns: The name of a package. Do not free.
 */
const gchar *pacman_conflict_get_first_package (PacmanConflict *conflict) {
	g_return_val_if_fail (conflict != NULL, NULL);
	
	return alpm_conflict_get_package1 (conflict);
}

/**
 * pacman_conflict_get_second_package:
 * @conflict: A #PacmanConflict.
 *
 * Gets the name of the second package that conflicts for @conflict.
 *
 * Returns: The name of a package. Do not free.
 */
const gchar *pacman_conflict_get_second_package (PacmanConflict *conflict) {
	g_return_val_if_fail (conflict != NULL, NULL);
	
	return alpm_conflict_get_package2 (conflict);
}

/**
 * pacman_conflict_check_packages:
 * @packages: A list of #PacmanPackage.
 *
 * Checks @packages for pairs that conflict with each other, and returns a list of these conflicts.
 *
 * Returns: A list of #PacmanConflict. Free the contents with pacman_conflict_free(), then free the list with pacman_list_free().
 */
PacmanList *pacman_conflict_check_packages (const PacmanList *packages) {
	g_return_val_if_fail (packages != NULL, NULL);
	
	return alpm_checkconflicts ((PacmanList *) packages);
}
