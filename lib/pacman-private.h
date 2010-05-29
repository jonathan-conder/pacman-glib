/* pacman-private.h
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

#ifndef __PACMAN_PRIVATE_H__
#define __PACMAN_PRIVATE_H__

#include <glib.h>
#include "pacman-types.h"
#include "pacman-transaction.h"

G_BEGIN_DECLS

void pacman_conflict_free (PacmanConflict *conflict);
void pacman_dependency_free (PacmanDependency *dependency);
void pacman_file_conflict_free (PacmanFileConflict *conflict);

extern PacmanManager *pacman_manager;

PacmanTransaction *pacman_manager_new_transaction (PacmanManager *manager, GType type);
gboolean pacman_transaction_ask (PacmanTransaction *transaction, PacmanTransactionQuestion question, const gchar *format, ...);
void pacman_transaction_tell (PacmanTransaction *transaction, PacmanTransactionStatus status, const gchar *format, ...);

gboolean pacman_transaction_start (guint32 flags, GError **error);
gboolean pacman_transaction_end (GError **error);
gboolean pacman_transaction_restart (PacmanTransaction *transaction, GError **error);

void pacman_transaction_mark_package (PacmanTransaction *transaction, PacmanPackage *package);
void pacman_transaction_set_marked_packages (PacmanTransaction *transaction, PacmanList *packages);

void pacman_transaction_set_missing_dependencies (PacmanTransaction *transaction, PacmanList *dependencies);
void pacman_transaction_set_conflicts (PacmanTransaction *transaction, PacmanList *conflicts);

void pacman_transaction_set_file_conflicts (PacmanTransaction *transaction, PacmanList *conflicts);
void pacman_transaction_set_invalid_files (PacmanTransaction *transaction, PacmanList *filenames);

G_END_DECLS

#endif
