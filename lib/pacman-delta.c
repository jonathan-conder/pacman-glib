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
