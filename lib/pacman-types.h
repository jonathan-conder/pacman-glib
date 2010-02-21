/* pacman-types.h
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

#ifndef __PACMAN_TYPES_H__
#define __PACMAN_TYPES_H__

#include <glib.h>

G_BEGIN_DECLS

typedef struct __pmconflict_t PacmanConflict;
typedef struct __pmdb_t PacmanDatabase;
typedef struct __pmdelta_t PacmanDelta;
typedef struct __pmdepend_t PacmanDependency;
typedef struct __pmfileconflict_t PacmanFileConflict;
typedef struct __pmgrp_t PacmanGroup;
typedef struct _PacmanInstall PacmanInstall;
typedef struct __alpm_list_t PacmanList;
typedef struct _PacmanManager PacmanManager;
typedef struct __pmdepmissing_t PacmanMissingDependency;
typedef struct __pmpkg_t PacmanPackage;
typedef struct _PacmanRemove PacmanRemove;
typedef struct _PacmanSync PacmanSync;
typedef struct _PacmanTransaction PacmanTransaction;
typedef struct _PacmanUpdate PacmanUpdate;

G_END_DECLS

#endif
