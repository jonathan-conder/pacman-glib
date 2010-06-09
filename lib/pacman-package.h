/* pacman-package.h
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

#ifndef __PACMAN_PACKAGE_H__
#define __PACMAN_PACKAGE_H__

#include <glib.h>
#include "pacman-types.h"

G_BEGIN_DECLS

PacmanPackage *pacman_package_new_from_file (const gchar *filename, gboolean full, GError **error);
void pacman_package_free (PacmanPackage *package);

const gchar *pacman_package_get_name (PacmanPackage *package);
PacmanDatabase *pacman_package_get_database (PacmanPackage *package);
const gchar *pacman_package_get_filename (PacmanPackage *package);

const gchar *pacman_package_get_version (PacmanPackage *package);
gint pacman_package_compare_version (const gchar *a, const gchar *b);
gboolean pacman_package_will_upgrade (PacmanPackage *package, PacmanPackage *update);
PacmanPackage *pacman_package_find_new_version (PacmanPackage *package, const PacmanList *databases);
PacmanPackage *pacman_package_find_upgrade (PacmanPackage *package, const PacmanList *databases);

const gchar *pacman_package_get_arch (PacmanPackage *package);
const gchar *pacman_package_get_description (PacmanPackage *package);
const PacmanList *pacman_package_get_groups (PacmanPackage *package);
const PacmanList *pacman_package_get_licenses (PacmanPackage *package);
const gchar *pacman_package_get_url (PacmanPackage *package);

const PacmanList *pacman_package_get_dependencies (PacmanPackage *package);
const PacmanList *pacman_package_get_optional_dependencies (PacmanPackage *package);
PacmanList *pacman_package_find_required_by (PacmanPackage *package);

const PacmanList *pacman_package_get_conflicts (PacmanPackage *package);
const PacmanList *pacman_package_get_provides (PacmanPackage *package);
const PacmanList *pacman_package_get_replaces (PacmanPackage *package);

const PacmanList *pacman_package_get_backup (PacmanPackage *package);
const PacmanList *pacman_package_get_deltas (PacmanPackage *package);
PacmanList *pacman_package_find_unused_deltas (PacmanPackage *package);
const PacmanList *pacman_package_get_files (PacmanPackage *package);

goffset pacman_package_get_size (PacmanPackage *package);
goffset pacman_package_get_download_size (PacmanPackage *package);
goffset pacman_package_get_installed_size (PacmanPackage *package);

const gchar *pacman_package_get_md5sum (PacmanPackage *package);
gchar *pacman_package_generate_md5sum (const gchar *filename, GError **error);
gboolean pacman_package_check_md5sum (PacmanPackage *package, GError **error);

gboolean pacman_package_has_filename (PacmanPackage *package, const gchar *filename);
gboolean pacman_package_has_force (PacmanPackage *package);
gboolean pacman_package_has_install_scriptlet (PacmanPackage *package);
gboolean pacman_package_was_explicitly_installed (PacmanPackage *package);

const gchar *pacman_package_get_packager (PacmanPackage *package);
time_t pacman_package_get_build_date (PacmanPackage *package);
time_t pacman_package_get_install_date (PacmanPackage *package);
gchar *pacman_package_read_changelog (PacmanPackage *package);
gchar *pacman_package_make_list (const PacmanList *packages);

G_END_DECLS

#endif
