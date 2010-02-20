#include <alpm.h>
#include "pacman-error.h"

/**
 * SECTION:pacman-error
 * @title: PacmanError
 * @short_description: Error reporting
 *
 * Errors are reported using #GError with error domain %PACMAN_ERROR and codes from #PacmanError.
 */

/**
 * PACMAN_ERROR:
 *
 * Error domain for pacman operations. Errors in this domain will be from the #PacmanError enumeration.
 */
GQuark pacman_error_quark (void) {
	return g_quark_from_static_string ("pacman-error-quark");
}
