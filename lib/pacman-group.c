/* pacman-group.c
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
#include "pacman-group.h"

/**
 * SECTION:pacman-group
 * @title: PacmanGroup
 * @short_description: Groups of packages
 *
 * A #PacmanGroup is a set of similar packages that can be installed together.
 */

/**
 * PacmanGroup:
 *
 * Represents a set of similar packages.
 */

/**
 * pacman_group_get_name:
 * @group: A #PacmanGroup.
 *
 * Gets the name of @group.
 *
 * Returns: A group name. Do not free.
 */
const gchar *pacman_group_get_name (PacmanGroup *group) {
	g_return_val_if_fail (group != NULL, NULL);
	
	return alpm_grp_get_name (group);
}

/**
 * pacman_group_get_packages:
 * @group: A #PacmanGroup.
 *
 * Gets a list of packages in @group.
 *
 * Returns: A list of #PacmanPackage. Do not free.
 */
const PacmanList *pacman_group_get_packages (PacmanGroup *group) {
	g_return_val_if_fail (group != NULL, NULL);
	
	return alpm_grp_get_pkgs (group);
}
