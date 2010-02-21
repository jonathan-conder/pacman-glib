/* pacman-error.c
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
