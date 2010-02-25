/* pacman-database.h
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
#error "Only <pacman.h> can be included directly."
#endif

#ifndef __PACMAN_DATABASE_H__
#define __PACMAN_DATABASE_H__

#include <glib.h>
#include "pacman-types.h"

G_BEGIN_DECLS

const gchar *pacman_database_get_name (PacmanDatabase *database);
const gchar *pacman_database_get_server (PacmanDatabase *database);
void pacman_database_add_server (PacmanDatabase *database, const gchar *url);

const PacmanList *pacman_database_get_packages (PacmanDatabase *database);
const PacmanList *pacman_database_get_groups (PacmanDatabase *database);

PacmanPackage *pacman_database_find_package (PacmanDatabase *database, const gchar *name);
PacmanGroup *pacman_database_find_group (PacmanDatabase *database, const gchar *name);
PacmanList *pacman_database_search (PacmanDatabase *database, const PacmanList *needles);

G_END_DECLS

#endif
