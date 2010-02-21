/* pacman-list.h
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

#ifndef __PACMAN_LIST_H__
#define __PACMAN_LIST_H__

#include <glib.h>
#include "pacman-types.h"

G_BEGIN_DECLS

PacmanList *pacman_list_new (void);
void pacman_list_free (PacmanList *list);
void pacman_list_free_contents (PacmanList *list, GDestroyNotify func);
void pacman_list_free_full (PacmanList *list, GDestroyNotify func);

guint pacman_list_length (const PacmanList *list);
gpointer pacman_list_get (const PacmanList *entry);
void pacman_list_set (PacmanList *entry, gpointer item);

PacmanList *pacman_list_prev (const PacmanList *entry);
PacmanList *pacman_list_next (const PacmanList *entry);
PacmanList *pacman_list_nth (const PacmanList *list, guint n);

PacmanList *pacman_list_first (const PacmanList *list);
PacmanList *pacman_list_last (const PacmanList *list);

PacmanList *pacman_list_add (PacmanList *list, gpointer item);
PacmanList *pacman_list_add_sorted (PacmanList *list, gpointer item, GCompareFunc func);
PacmanList *pacman_list_concat (PacmanList *first, PacmanList *second);
PacmanList *pacman_list_concat_sorted (PacmanList *first, PacmanList *second, GCompareFunc func);

PacmanList *pacman_list_remove (PacmanList *haystack, gconstpointer needle, GCompareFunc func, gpointer *removed);
PacmanList *pacman_list_remove_direct (PacmanList *haystack, gconstpointer needle, gpointer *removed);
PacmanList *pacman_list_remove_string (PacmanList *haystack, const gchar *needle, gchar **removed);
PacmanList *pacman_list_remove_duplicates (const PacmanList *list);

gpointer pacman_list_find (const PacmanList *haystack, gconstpointer needle, GCompareFunc func);
gpointer pacman_list_find_direct (const PacmanList *haystack, gconstpointer needle);
gchar *pacman_list_find_string (const PacmanList *haystack, const gchar *needle);

PacmanList *pacman_list_sort (PacmanList *list, GCompareFunc func);
PacmanList *pacman_list_reverse (PacmanList *list);
PacmanList *pacman_list_diff (const PacmanList *lhs, const PacmanList *rhs, GCompareFunc func);
PacmanList *pacman_list_copy (const PacmanList *list);
PacmanList *pacman_list_strdup (const PacmanList *list);

G_END_DECLS

#endif
