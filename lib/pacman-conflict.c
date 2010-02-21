/* pacman-conflict.c
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
