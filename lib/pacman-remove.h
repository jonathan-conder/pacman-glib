/* pacman-remove.h
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

#ifndef __PACMAN_REMOVE_H__
#define __PACMAN_REMOVE_H__

#include <glib.h>
#include <glib-object.h>
#include "pacman-types.h"
#include "pacman-transaction.h"

G_BEGIN_DECLS

#define PACMAN_TYPE_REMOVE (pacman_remove_get_type ())
#define PACMAN_REMOVE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PACMAN_TYPE_REMOVE, PacmanRemove))
#define PACMAN_REMOVE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PACMAN_TYPE_REMOVE, PacmanRemoveClass))
#define PACMAN_IS_REMOVE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PACMAN_TYPE_REMOVE))
#define PACMAN_IS_REMOVE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PACMAN_TYPE_REMOVE))
#define PACMAN_REMOVE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PACMAN_TYPE_REMOVE, PacmanRemoveClass))

struct _PacmanRemove {
	PacmanTransaction parent_instance;
};

typedef struct _PacmanRemoveClass {
	PacmanTransactionClass parent_class;
} PacmanRemoveClass;

GType pacman_remove_get_type (void);

G_END_DECLS

#endif
