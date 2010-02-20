/* pacman-group.h
 *
 * Copyright (C) 2010 Jonathan Conder <jonno@skurvy.org>
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

#ifndef __PACMAN_GROUP_H__
#define __PACMAN_GROUP_H__

#include <glib.h>
#include "pacman-types.h"

G_BEGIN_DECLS

const gchar *pacman_group_get_name (PacmanGroup *group);
const PacmanList *pacman_group_get_packages (PacmanGroup *group);

G_END_DECLS

#endif
