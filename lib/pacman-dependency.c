/* pacman-dependency.c
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
#include "pacman-dependency.h"

/**
 * SECTION:pacman-dependency
 * @title: PacmanDependency
 * @short_description: Versioned dependencies
 *
 * A #PacmanDependency represents a versioned dependency that a package may have.
 */

/**
 * PacmanDependency:
 *
 * Represents a versioned dependency.
 */

void pacman_dependency_free (PacmanDependency *dependency) {
	/* this is a hack, but it's better than a memory leak */
	free ((gchar *) pacman_dependency_get_name (dependency));
	free ((gchar *) pacman_dependency_get_version (dependency));
	free (dependency);
}

/**
 * pacman_dependency_get_name:
 * @dependency: A #PacmanDependency.
 *
 * Gets the name of the (possibly virtual) package represented by @dependency.
 *
 * Returns: A package name. Do not free.
 */
const gchar *pacman_dependency_get_name (PacmanDependency *dependency) {
	g_return_val_if_fail (dependency != NULL, NULL);
	
	return alpm_dep_get_name (dependency);
}

/**
 * pacman_dependency_get_version:
 * @dependency: A #PacmanDependency.
 *
 * Gets the version of the package required by @dependency.
 *
 * Returns: A package version, or %NULL if no particular version is required. Do not free.
 */
const gchar *pacman_dependency_get_version (PacmanDependency *dependency) {
	g_return_val_if_fail (dependency != NULL, NULL);
	
	return alpm_dep_get_version (dependency);
}

/**
 * pacman_dependency_get_compare_operation:
 * @dependency: A #PacmanDependency.
 *
 * Gets the operation used to determine whether a package version satisfies @dependency.
 *
 * Returns: A #PacmanDependencyCompare.
 */
PacmanDependencyCompare pacman_dependency_get_compare_operation (PacmanDependency *dependency) {
	g_return_val_if_fail (dependency != NULL, PACMAN_DEPENDENCY_COMPARE_NONE);
	
	/* PacmanDependencyCompare is set up so that this works */
	return (PacmanDependencyCompare) alpm_dep_get_mod (dependency);
}

/**
 * pacman_dependency_satisfied_by:
 * @dependency: A #PacmanDependency.
 * @package: A #PacmanPackage.
 *
 * Checks if @package satisfies @dependency.
 *
 * Returns: %TRUE if @package satifies @dependency, %FALSE otherwise.
 */
gboolean pacman_dependency_satisfied_by (PacmanDependency *dependency, PacmanPackage *package) {
	g_return_val_if_fail (package != NULL, FALSE);
	g_return_val_if_fail (dependency != NULL, TRUE);
	
	return alpm_depcmp (package, dependency) != 0;
}

/**
 * pacman_dependency_to_string:
 * @dependency: A #PacmanDependency.
 *
 * Generates a string representation of @dependency.
 *
 * Returns: A string of the form 'package' or 'package*version', where * represents a #PacmanDependencyCompare operation (i.e. one of '=', '>=', '<=', '>' or '<'). Free with g_free().
 */
gchar *pacman_dependency_to_string (PacmanDependency *dependency) {
	gchar *result, *temp;
	
	g_return_val_if_fail (dependency != NULL, NULL);
	
	result = alpm_dep_compute_string (dependency);
	
	if (!g_mem_is_system_malloc ()) {
		temp = result;
		result = g_strdup (result);
		free (temp);
	}
	
	return result;
}
