/* pacman-delta.c
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
#include "pacman-delta.h"

/**
 * SECTION:pacman-delta
 * @title: PacmanDelta
 * @short_description: Package deltas
 *
 * A #PacmanDelta represents a delta patch that can be used to upgrade packages without downloading the whole compressed package.
 */

/**
 * PacmanDelta:
 *
 * Represents a delta patch against a binary file.
 */

/**
 * pacman_delta_get_patch_filename:
 * @delta: A #PacmanDelta.
 *
 * Gets the location of the delta patch provided by @delta.
 *
 * Returns: A file name. Do not free.
 */
const gchar *pacman_delta_get_patch_filename (PacmanDelta *delta) {
	g_return_val_if_fail (delta != NULL, NULL);
	
	return alpm_delta_get_filename (delta);
}

/**
 * pacman_delta_get_patch_size:
 * @delta: A #PacmanDelta.
 *
 * Gets the size of the delta patch provided by @delta.
 *
 * Returns: A file size, in bytes.
 */
goffset pacman_delta_get_patch_size (PacmanDelta *delta) {
	g_return_val_if_fail (delta != NULL, 0);
	
	return (goffset) alpm_delta_get_size (delta);
}

/**
 * pacman_delta_get_patch_md5sum:
 * @delta: A #PacmanDelta.
 *
 * Gets the MD5 sum that the delta patch provided by @delta should satisfy.
 *
 * Returns: An MD5 sum. Do not free.
 */
const gchar *pacman_delta_get_patch_md5sum (PacmanDelta *delta) {
	g_return_val_if_fail (delta != NULL, NULL);
	
	return alpm_delta_get_md5sum (delta);
}

/**
 * pacman_delta_get_from_filename:
 * @delta: A #PacmanDelta.
 *
 * Gets the location of the file that @delta will patch.
 *
 * Returns: A file name. Do not free.
 */
const gchar *pacman_delta_get_from_filename (PacmanDelta *delta) {
	g_return_val_if_fail (delta != NULL, NULL);
	
	return alpm_delta_get_from (delta);
}

/**
 * pacman_delta_get_to_filename:
 * @delta: A #PacmanDelta.
 *
 * Gets the location of the file that @delta will create.
 *
 * Returns: A file name. Do not free.
 */
const gchar *pacman_delta_get_to_filename (PacmanDelta *delta) {
	g_return_val_if_fail (delta != NULL, NULL);
	
	return alpm_delta_get_to (delta);
}
