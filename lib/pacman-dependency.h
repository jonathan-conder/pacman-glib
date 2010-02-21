/* pacman-dependency.h
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
#error "Only <gpacman/pacman.h> can be included directly."
#endif

#ifndef __PACMAN_DEPENDENCY_H__
#define __PACMAN_DEPENDENCY_H__

#include <glib.h>
#include <glib-object.h>
#include "pacman-types.h"

G_BEGIN_DECLS

#define PACMAN_TYPE_DEPENDENCY_COMPARE (pacman_dependency_compare_get_type ())

/**
 * PacmanDependencyCompare:
 * @PACMAN_DEPENDENCY_COMPARE_NONE: Should not be used.
 * @PACMAN_DEPENDENCY_COMPARE_ANY: Satisfied if any version is provided.
 * @PACMAN_DEPENDENCY_COMPARE_EQUAL: Satisfied if a specific version is provided.
 * @PACMAN_DEPENDENCY_COMPARE_NEWER_OR_EQUAL: Satisfied if the package version is newer than or equal to that required.
 * @PACMAN_DEPENDENCY_COMPARE_OLDER_OR_EQUAL: Satisfied if the package version is older than or equal to that required.
 * @PACMAN_DEPENDENCY_COMPARE_NEWER: Satisfied if the package version is newer than that required.
 * @PACMAN_DEPENDENCY_COMPARE_OLDER: Satisfied if the package version is older than that required.
 *
 * Operations used to determine if a dependency is satisfied by a given package version.
 */
typedef enum {
	PACMAN_DEPENDENCY_COMPARE_NONE = 0, /*< skip >*/
	PACMAN_DEPENDENCY_COMPARE_ANY,
	PACMAN_DEPENDENCY_COMPARE_EQUAL,
	PACMAN_DEPENDENCY_COMPARE_NEWER_OR_EQUAL,
	PACMAN_DEPENDENCY_COMPARE_OLDER_OR_EQUAL,
	PACMAN_DEPENDENCY_COMPARE_NEWER,
	PACMAN_DEPENDENCY_COMPARE_OLDER
} PacmanDependencyCompare;

GType pacman_dependency_compare_get_type (void);

const gchar *pacman_dependency_get_name (PacmanDependency *dependency);
const gchar *pacman_dependency_get_version (PacmanDependency *dependency);
PacmanDependencyCompare pacman_dependency_get_compare_operation (PacmanDependency *dependency);

gboolean pacman_dependency_satisfied_by (PacmanDependency *dependency, PacmanPackage *package);
gchar *pacman_dependency_to_string (PacmanDependency *dependency);

G_END_DECLS

#endif
