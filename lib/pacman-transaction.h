/* pacman-transaction.h
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

#ifndef __PACMAN_TRANSACTION_H__
#define __PACMAN_TRANSACTION_H__

#include <glib.h>
#include <glib-object.h>
#include "pacman-types.h"

G_BEGIN_DECLS

#define PACMAN_TYPE_TRANSACTION (pacman_transaction_get_type ())
#define PACMAN_TRANSACTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PACMAN_TYPE_TRANSACTION, PacmanTransaction))
#define PACMAN_TRANSACTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PACMAN_TYPE_TRANSACTION, PacmanTransactionClass))
#define PACMAN_IS_TRANSACTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PACMAN_TYPE_TRANSACTION))
#define PACMAN_IS_TRANSACTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PACMAN_TYPE_TRANSACTION))
#define PACMAN_TRANSACTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PACMAN_TYPE_TRANSACTION, PacmanTransactionClass))

#define PACMAN_TYPE_TRANSACTION_FLAGS (pacman_transaction_flags_get_type ())
#define PACMAN_TYPE_TRANSACTION_STATUS (pacman_transaction_status_get_type ())
#define PACMAN_TYPE_TRANSACTION_QUESTION (pacman_transaction_question_get_type ())
#define PACMAN_TYPE_TRANSACTION_PROGRESS (pacman_transaction_progress_get_type ())

struct _PacmanTransaction {
	GObject parent_instance;
};

typedef struct _PacmanTransactionClass {
	GObjectClass parent_class;
	
	gboolean (*prepare) (PacmanTransaction *transaction, const PacmanList *targets, GError **error);
	gboolean (*commit) (PacmanTransaction *transaction, GError **error);
} PacmanTransactionClass;

/**
 * PacmanTransactionFlags:
 * @PACMAN_TRANSACTION_FLAGS_NONE: Use the default transaction options.
 * @PACMAN_TRANSACTION_FLAGS_IGNORE_DEPENDENCIES: Skip dependency checks (equivalent to pacman -d).
 * @PACMAN_TRANSACTION_FLAGS_IGNORE_FILE_CONFLICTS: Overwrite files that already exist on the system (equivalent to pacman -f).
 * @PACMAN_TRANSACTION_FLAGS_REMOVE_BACKUPS: Completely remove configuration files (equivalent to pacman -Rn).
 * @PACMAN_TRANSACTION_FLAGS_REMOVE_CASCADE: Remove packages that depend on those being removed (equivalent to pacman -Rc).
 * @PACMAN_TRANSACTION_FLAGS_REMOVE_RECURSIVE: Remove packages that are no longer required by other packages, unless they were explicity installed (equivalent to pacman -Rs).
 * @PACMAN_TRANSACTION_FLAGS_REMOVE_KEEP_FILES: Remove packages from the database but leave the files on the system (equivalent to pacman -Rk).
 * @PACMAN_TRANSACTION_FLAGS_UPDATE_ALLOW_DOWNGRADE: "Update" databases that are newer than the remote database (equivalent to pacman -Syy).
 * @PACMAN_TRANSACTION_FLAGS_INSTALL_IMPLICIT: Install packages as if they were only a dependency of another package (equivalent to pacman --asdeps).
 * @PACMAN_TRANSACTION_FLAGS_SYNC_DOWNLOAD_ONLY: Download package files but do not install them (equivalent to pacman -Sw).
 * @PACMAN_TRANSACTION_FLAGS_INSTALL_IGNORE_SCRIPTLET: Do not execute the install scriptlet of the packages (equivalent to pacman --noscriptlet).
 * @PACMAN_TRANSACTION_FLAGS_IGNORE_DEPENDENCY_CONFLICTS: Skip checks for dependency conflicts. This could save time when not necessary (e.g. for pacman -Sw).
 * @PACMAN_TRANSACTION_FLAGS_SYNC_ALLOW_DOWNGRADE: "Upgrade" packages that are newer than the database version (equivalent to pacman -Suu).
 * @PACMAN_TRANSACTION_FLAGS_SYNC_OUTDATED_ONLY: Only install packages that are out-of-date (equivalent to pacman -S --needed).
 * @PACMAN_TRANSACTION_FLAGS_INSTALL_EXPLICIT: Install all packages as if they were installed explicitly by the user (equivalent to pacman --asexplicit).
 * @PACMAN_TRANSACTION_FLAGS_REMOVE_UNNEEDED_ONLY: Only remove those packages that are not required by other packages (equivalent to pacman -Ru).
 * @PACMAN_TRANSACTION_FLAGS_REMOVE_RECURSIVE_EXPLICIT: Remove packages that are no longer required by other packages, even if they were explicitly installed (equivalent to pacman -Rss).
 * @PACMAN_TRANSACTION_FLAGS_IGNORE_DATABASE_LOCK: Do not lock the pacman database. This could be useful if you do not intend to commit the transaction.
 *
 * Flags that specify the behaviour of a #PacmanTransaction.
 */
typedef enum {
	PACMAN_TRANSACTION_FLAGS_NONE = 0,
	PACMAN_TRANSACTION_FLAGS_IGNORE_DEPENDENCIES = (1 << 0),
	PACMAN_TRANSACTION_FLAGS_IGNORE_FILE_CONFLICTS = (1 << 1),
	PACMAN_TRANSACTION_FLAGS_REMOVE_BACKUPS = (1 << 2),
	PACMAN_TRANSACTION_FLAGS_REMOVE_CASCADE = (1 << 4),
	PACMAN_TRANSACTION_FLAGS_REMOVE_RECURSIVE = (1 << 5),
	PACMAN_TRANSACTION_FLAGS_REMOVE_KEEP_FILES = (1 << 6),
	PACMAN_TRANSACTION_FLAGS_UPDATE_ALLOW_DOWNGRADE = (1 << 7),
	PACMAN_TRANSACTION_FLAGS_INSTALL_IMPLICIT = (1 << 8),
	PACMAN_TRANSACTION_FLAGS_SYNC_DOWNLOAD_ONLY = (1 << 9),
	PACMAN_TRANSACTION_FLAGS_INSTALL_IGNORE_SCRIPTLET = (1 << 10),
	PACMAN_TRANSACTION_FLAGS_IGNORE_DEPENDENCY_CONFLICTS = (1 << 11),
	PACMAN_TRANSACTION_FLAGS_SYNC_ALLOW_DOWNGRADE = (1 << 12),
	PACMAN_TRANSACTION_FLAGS_SYNC_OUTDATED_ONLY = (1 << 13),
	PACMAN_TRANSACTION_FLAGS_INSTALL_EXPLICIT = (1 << 14),
	PACMAN_TRANSACTION_FLAGS_REMOVE_UNNEEDED_ONLY = (1 << 15),
	PACMAN_TRANSACTION_FLAGS_REMOVE_RECURSIVE_EXPLICIT = (1 << 16),
	PACMAN_TRANSACTION_FLAGS_IGNORE_DATABASE_LOCK = (1 << 17)
} PacmanTransactionFlags;

/**
 * PacmanTransactionStatus:
 * @PACMAN_TRANSACTION_STATUS_DEPENDENCY_CHECK_START: Checking dependencies.
 * @PACMAN_TRANSACTION_STATUS_DEPENDENCY_CHECK_END: Finished checking dependencies.
 * @PACMAN_TRANSACTION_STATUS_FILE_CONFLICT_CHECK_START: Checking for file conflicts.
 * @PACMAN_TRANSACTION_STATUS_FILE_CONFLICT_CHECK_END: Finished checking for file conflicts.
 * @PACMAN_TRANSACTION_STATUS_DEPENDENCY_RESOLVE_START: Resolving dependencies.
 * @PACMAN_TRANSACTION_STATUS_DEPENDENCY_RESOLVE_END: Finished resolving dependencies.
 * @PACMAN_TRANSACTION_STATUS_CONFLICT_CHECK_START: Checking for conflicts.
 * @PACMAN_TRANSACTION_STATUS_CONFLICT_CHECK_END: Finished checking for conflicts.
 * @PACMAN_TRANSACTION_STATUS_INSTALL_START: Installing 'package', where package is the marked package for the transaction.
 * @PACMAN_TRANSACTION_STATUS_INSTALL_END: Finished installing 'package', where package is the marked package for the transaction.
 * @PACMAN_TRANSACTION_STATUS_REMOVE_START: Removing 'package', where package is the marked package for the transaction.
 * @PACMAN_TRANSACTION_STATUS_REMOVE_END: Finished removing 'package', where package is the marked package for the transaction.
 * @PACMAN_TRANSACTION_STATUS_UPGRADE_START: Upgrading 'package', where the new package, followed by the old package, are the marked packages for the transaction.
 * @PACMAN_TRANSACTION_STATUS_UPGRADE_END: Finished upgrading 'package', where the new package, followed by the old package, are the marked packages for the transaction.
 * @PACMAN_TRANSACTION_STATUS_PACKAGE_INTEGRITY_CHECK_START: Checking package integrity.
 * @PACMAN_TRANSACTION_STATUS_PACKAGE_INTEGRITY_CHECK_END: Finished checking package integrity.
 * @PACMAN_TRANSACTION_STATUS_DELTA_INTEGRITY_CHECK_START: Checking delta integrity.
 * @PACMAN_TRANSACTION_STATUS_DELTA_INTEGRITY_CHECK_END: Finished checking delta integrity.
 * @PACMAN_TRANSACTION_STATUS_DELTA_PATCHING_START: Applying delta patches.
 * @PACMAN_TRANSACTION_STATUS_DELTA_PATCHING_END: Finished applying delta patches.
 * @PACMAN_TRANSACTION_STATUS_DELTA_PATCH_START: Creating 'file' from the delta patch 'delta'.
 * @PACMAN_TRANSACTION_STATUS_DELTA_PATCH_END: Finished applying delta patch.
 * @PACMAN_TRANSACTION_STATUS_DOWNLOAD_START: Downloading packages.
 * @PACMAN_TRANSACTION_STATUS_DOWNLOAD_FROM: Downloading packages from ['database'].
 * @PACMAN_TRANSACTION_STATUS_DOWNLOAD_END: Finished downloading packages.
 * @PACMAN_TRANSACTION_STATUS_LAST: Should not be used.
 *
 * Status messages that will be emitted by the "status" signal of a #PacmanTransaction. The descriptions given are the same as or similar to those reported by the "status" signal of a transaction. If desired, a custom description could be derived from the status message and the marked packages of the transaction.
 */
typedef enum {
	PACMAN_TRANSACTION_STATUS_DEPENDENCY_CHECK_START,
	PACMAN_TRANSACTION_STATUS_DEPENDENCY_CHECK_END,
	PACMAN_TRANSACTION_STATUS_FILE_CONFLICT_CHECK_START,
	PACMAN_TRANSACTION_STATUS_FILE_CONFLICT_CHECK_END,
	PACMAN_TRANSACTION_STATUS_DEPENDENCY_RESOLVE_START,
	PACMAN_TRANSACTION_STATUS_DEPENDENCY_RESOLVE_END,
	PACMAN_TRANSACTION_STATUS_CONFLICT_CHECK_START,
	PACMAN_TRANSACTION_STATUS_CONFLICT_CHECK_END,
	PACMAN_TRANSACTION_STATUS_INSTALL_START,
	PACMAN_TRANSACTION_STATUS_INSTALL_END,
	PACMAN_TRANSACTION_STATUS_REMOVE_START,
	PACMAN_TRANSACTION_STATUS_REMOVE_END,
	PACMAN_TRANSACTION_STATUS_UPGRADE_START,
	PACMAN_TRANSACTION_STATUS_UPGRADE_END,
	PACMAN_TRANSACTION_STATUS_PACKAGE_INTEGRITY_CHECK_START,
	PACMAN_TRANSACTION_STATUS_PACKAGE_INTEGRITY_CHECK_END,
	PACMAN_TRANSACTION_STATUS_DELTA_INTEGRITY_CHECK_START,
	PACMAN_TRANSACTION_STATUS_DELTA_INTEGRITY_CHECK_END,
	PACMAN_TRANSACTION_STATUS_DELTA_PATCHING_START,
	PACMAN_TRANSACTION_STATUS_DELTA_PATCHING_END,
	PACMAN_TRANSACTION_STATUS_DELTA_PATCH_START,
	PACMAN_TRANSACTION_STATUS_DELTA_PATCH_END,
	PACMAN_TRANSACTION_STATUS_DOWNLOAD_START,
	PACMAN_TRANSACTION_STATUS_DOWNLOAD_FROM,
	PACMAN_TRANSACTION_STATUS_DOWNLOAD_END,
	PACMAN_TRANSACTION_STATUS_LAST /*< skip >*/
} PacmanTransactionStatus;

/**
 * PacmanTransactionQuestion:
 * @PACMAN_TRANSACTION_QUESTION_INSTALL_IGNORE_PACKAGE: Whether to install a newer version of a package marked as IgnorePkg or IgnoreGroup. The relevant package will be the marked package for the transaction.
 * @PACMAN_TRANSACTION_QUESTION_REPLACE_PACKAGE: Whether to replace an installed package with a different one marked as a replacement. The relevant packages will be in the conflict for the transaction.
 * @PACMAN_TRANSACTION_QUESTION_REMOVE_CONFLICTING_PACKAGE: Whether to replace an installed package with a different one that conflicts with it. The relevant packages will be in the conflict for the transaction.
 * @PACMAN_TRANSACTION_QUESTION_SKIP_UNRESOLVABLE_PACKAGES: Whether to continue the transaction even though some of the packages will not be able to be installed. The relevant packages will be the marked packages for the transaction.
 * @PACMAN_TRANSACTION_QUESTION_INSTALL_OLDER_PACKAGE: Whether to install an older version of a package than the one already installed. The older package will be the marked package for the transaction.
 * @PACMAN_TRANSACTION_QUESTION_DELETE_CORRUPTED_PACKAGE: Whether to delete a package file that is corrupt (the transaction will fail either way). The relevant file will be the invalid file for the transaction.
 * @PACMAN_TRANSACTION_QUESTION_REMOVE_HOLD_PACKAGES: Whether to remove packages that are marked as HoldPkg. The relevant packages will be the marked packages for the transaction.
 * @PACMAN_TRANSACTION_QUESTION_SYNC_FIRST: Whether to cancel the transaction and install packages marked as SyncFirst instead. The relevant packages will be the marked packages for the transaction.
 * @PACMAN_TRANSACTION_QUESTION_LAST: Should not be used.
 *
 * Questions that will be emitted by the "question" signal of a #PacmanTransaction. If desired, a custom question description could be derived from the question and the marked packages/conflicts/invalid files of the transaction.
 */
typedef enum {
	PACMAN_TRANSACTION_QUESTION_INSTALL_IGNORE_PACKAGE,
	PACMAN_TRANSACTION_QUESTION_REPLACE_PACKAGE,
	PACMAN_TRANSACTION_QUESTION_REMOVE_CONFLICTING_PACKAGE,
	PACMAN_TRANSACTION_QUESTION_SKIP_UNRESOLVABLE_PACKAGES,
	PACMAN_TRANSACTION_QUESTION_INSTALL_OLDER_PACKAGE,
	PACMAN_TRANSACTION_QUESTION_DELETE_CORRUPTED_PACKAGE,
	PACMAN_TRANSACTION_QUESTION_REMOVE_HOLD_PACKAGES,
	PACMAN_TRANSACTION_QUESTION_SYNC_FIRST,
	PACMAN_TRANSACTION_QUESTION_LAST /*< skip >*/
} PacmanTransactionQuestion;

/**
 * PacmanTransactionProgress:
 * @PACMAN_TRANSACTION_PROGRESS_INSTALL: Installing a package.
 * @PACMAN_TRANSACTION_PROGRESS_UPGRADE: Upgrading a package.
 * @PACMAN_TRANSACTION_PROGRESS_REMOVE: Removing a package.
 * @PACMAN_TRANSACTION_PROGRESS_FILE_CONFLICT_CHECK: Checking for file conflicts.
 * @PACMAN_TRANSACTION_PROGRESS_LAST: Should not be used.
 *
 * Operations that will be reported on by the "progress" signal of a transaction. The start and finish of these operations are reported by the "status" signal.
 */
typedef enum {
	PACMAN_TRANSACTION_PROGRESS_INSTALL,
	PACMAN_TRANSACTION_PROGRESS_UPGRADE,
	PACMAN_TRANSACTION_PROGRESS_REMOVE,
	PACMAN_TRANSACTION_PROGRESS_FILE_CONFLICT_CHECK,
	PACMAN_TRANSACTION_PROGRESS_LAST /*< skip >*/
} PacmanTransactionProgress;

GType pacman_transaction_get_type (void);
GType pacman_transaction_flags_get_type (void);
GType pacman_transaction_status_get_type (void);
GType pacman_transaction_question_get_type (void);
GType pacman_transaction_progress_get_type (void);

guint32 pacman_transaction_get_flags (PacmanTransaction *transaction);
const PacmanList *pacman_transaction_get_installs (PacmanTransaction *transaction);
const PacmanList *pacman_transaction_get_removes (PacmanTransaction *transaction);

const PacmanList *pacman_transaction_get_marked_packages (PacmanTransaction *transaction);
const PacmanList *pacman_transaction_get_missing_dependencies (PacmanTransaction *transaction);
const PacmanList *pacman_transaction_get_conflicts (PacmanTransaction *transaction);
const PacmanList *pacman_transaction_get_file_conflicts (PacmanTransaction *transaction);
const PacmanList *pacman_transaction_get_invalid_files (PacmanTransaction *transaction);

gboolean pacman_transaction_prepare (PacmanTransaction *transaction, const PacmanList *targets, GError **error);
gboolean pacman_transaction_commit (PacmanTransaction *transaction, GError **error);
gboolean pacman_transaction_cancel (PacmanTransaction *transaction, GError **error);

G_END_DECLS

#endif
