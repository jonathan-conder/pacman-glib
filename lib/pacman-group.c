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
