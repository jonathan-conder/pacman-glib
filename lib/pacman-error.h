/* pacman-error.h
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

#ifndef __PACMAN_ERROR_H__
#define __PACMAN_ERROR_H__

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define PACMAN_TYPE_ERROR (pacman_error_get_type ())
#define PACMAN_ERROR (pacman_error_quark ())

/**
 * PacmanError:
 * @PACMAN_ERROR_NONE: No error occurred.
 * @PACMAN_ERROR_MEMORY: Not enough memory.
 * @PACMAN_ERROR_SYSTEM: Unknown system error.
 * @PACMAN_ERROR_NOT_PERMITTED: Operation not permitted with current privileges.
 * @PACMAN_ERROR_FILE_NOT_FOUND: Could not find or read from the file.
 * @PACMAN_ERROR_DIRECTORY_NOT_FOUND: Could not find or read from the directory.
 * @PACMAN_ERROR_INVALID_ARGS: Invalid function arguments.
 * @PACMAN_ERROR_NOT_INITIALIZED: The library has not been initialized.
 * @PACMAN_ERROR_ALREADY_INITIALIZED: The library has already been initialized.
 * @PACMAN_ERROR_ALREADY_RUNNING: Another package manager is already running.
 * @PACMAN_ERROR_DATABASE_OPEN_FAILED: Could not open the database.
 * @PACMAN_ERROR_DATABASE_CREATE_FAILED: Could not create the database.
 * @PACMAN_ERROR_DATABASE_NOT_INITIALIZED: The database has not been initialized.
 * @PACMAN_ERROR_DATABASE_ALREADY_INITIALIZED: The database has already been initialized.
 * @PACMAN_ERROR_DATABASE_NOT_FOUND: Could not find the database.
 * @PACMAN_ERROR_DATABASE_UPDATE_FAILED: Could not update the database.
 * @PACMAN_ERROR_DATABASE_REMOVE_FAILED: Could not remove the database.
 * @PACMAN_ERROR_SERVER_INVALID_URL: Could not understand the URL.
 * @PACMAN_ERROR_SERVER_NONE_AVAILABLE: Could not find a mirror for the database.
 * @PACMAN_ERROR_TRANSACTION_ALREADY_INITIALIZED: The transaction has already been initialized.
 * @PACMAN_ERROR_TRANSACTION_NOT_INITIALIZED: The transaction has not been initialized.
 * @PACMAN_ERROR_TRANSACTION_DUPLICATE_TARGET: A target was specified more than once for the transaction.
 * @PACMAN_ERROR_TRANSACTION_NOT_READY: The transaction is not in the appropriate state.
 * @PACMAN_ERROR_TRANSACTION_NOT_PREPARED: The transaction has not been prepared.
 * @PACMAN_ERROR_TRANSACTION_ABORTED: The transaction was aborted for unspecified reasons.
 * @PACMAN_ERROR_TRANSACTION_INVALID_OPERATION: The transaction type does not support the requested operation.
 * @PACMAN_ERROR_TRANSACTION_NOT_LOCKED: The transaction cannot be committed without a database lock.
 * @PACMAN_ERROR_PACKAGE_NOT_FOUND: Could not find the package.
 * @PACMAN_ERROR_PACKAGE_IGNORED: The operation failed because a package was marked as IgnorePkg or IgnoreGroup.
 * @PACMAN_ERROR_PACKAGE_INVALID: The package file was invalid or corrupted.
 * @PACMAN_ERROR_PACKAGE_OPEN_FAILED: Could not open the package file.
 * @PACMAN_ERROR_PACKAGE_REMOVE_FAILED: Could not remove the package from the system.
 * @PACMAN_ERROR_PACKAGE_UNKNOWN_FILENAME: Could not find the filename of the package.
 * @PACMAN_ERROR_PACKAGE_DATABASE_NOT_FOUND: Could not find the specified database.
 * @PACMAN_ERROR_DELTA_INVALID: The delta patch was invalid or corrupted.
 * @PACMAN_ERROR_DELTA_PATCH_FAILED: Could not patch using a delta.
 * @PACMAN_ERROR_DEPENDENCY_UNSATISFIED: A dependency was not satisfied.
 * @PACMAN_ERROR_CONFLICT: Two or more packages conflicted with each other.
 * @PACMAN_ERROR_FILE_CONFLICT: A file provided by a package also exists in another package or on the filesystem.
 * @PACMAN_ERROR_DOWNLOAD_FAILED: Could not download a file.
 * @PACMAN_ERROR_REGEX_INVALID: Could not understand a regular expression.
 * @PACMAN_ERROR_LIBARCHIVE: Internal libarchive error.
 * @PACMAN_ERROR_LIBFETCH: Internal libfetch error.
 * @PACMAN_ERROR_DOWNLOAD_HANDLER: Could not download a file using an external download handler or transfer command.
 * @PACMAN_ERROR_CONFIG_INVALID: Could not understand the config file.
 * @PACMAN_ERROR_PACKAGE_HELD: The operation failed because a package was marked as HoldPkg.
 *
 * Error codes that can result from package management operations.
 */
typedef enum {
	PACMAN_ERROR_NONE = 0, /*< skip >*/
	PACMAN_ERROR_MEMORY,
	PACMAN_ERROR_SYSTEM,
	PACMAN_ERROR_NOT_PERMITTED,
	PACMAN_ERROR_FILE_NOT_FOUND,
	PACMAN_ERROR_DIRECTORY_NOT_FOUND,
	PACMAN_ERROR_INVALID_ARGS,
	
	PACMAN_ERROR_NOT_INITIALIZED,
	PACMAN_ERROR_ALREADY_INITIALIZED,
	PACMAN_ERROR_ALREADY_RUNNING,
	
	PACMAN_ERROR_DATABASE_OPEN_FAILED,
	PACMAN_ERROR_DATABASE_CREATE_FAILED,
	PACMAN_ERROR_DATABASE_NOT_INITIALIZED,
	PACMAN_ERROR_DATABASE_ALREADY_INITIALIZED,
	PACMAN_ERROR_DATABASE_NOT_FOUND,
	PACMAN_ERROR_DATABASE_UPDATE_FAILED,
	PACMAN_ERROR_DATABASE_REMOVE_FAILED,
	
	PACMAN_ERROR_SERVER_INVALID_URL,
	PACMAN_ERROR_SERVER_NONE_AVAILABLE,
	
	PACMAN_ERROR_TRANSACTION_ALREADY_INITIALIZED,
	PACMAN_ERROR_TRANSACTION_NOT_INITIALIZED,
	PACMAN_ERROR_TRANSACTION_DUPLICATE_TARGET,
	PACMAN_ERROR_TRANSACTION_NOT_READY,
	PACMAN_ERROR_TRANSACTION_NOT_PREPARED,
	PACMAN_ERROR_TRANSACTION_ABORTED,
	PACMAN_ERROR_TRANSACTION_INVALID_OPERATION,
	PACMAN_ERROR_TRANSACTION_NOT_LOCKED,
	
	PACMAN_ERROR_PACKAGE_NOT_FOUND,
	PACMAN_ERROR_PACKAGE_IGNORED,
	PACMAN_ERROR_PACKAGE_INVALID,
	PACMAN_ERROR_PACKAGE_OPEN_FAILED,
	PACMAN_ERROR_PACKAGE_REMOVE_FAILED,
	PACMAN_ERROR_PACKAGE_UNKNOWN_FILENAME,
	PACMAN_ERROR_PACKAGE_DATABASE_NOT_FOUND,
	
	PACMAN_ERROR_DELTA_INVALID,
	PACMAN_ERROR_DELTA_PATCH_FAILED,
	
	PACMAN_ERROR_DEPENDENCY_UNSATISFIED,
	PACMAN_ERROR_CONFLICT,
	PACMAN_ERROR_FILE_CONFLICT,
	
	PACMAN_ERROR_DOWNLOAD_FAILED,
	PACMAN_ERROR_REGEX_INVALID,
	PACMAN_ERROR_LIBARCHIVE,
	PACMAN_ERROR_LIBFETCH,
	PACMAN_ERROR_DOWNLOAD_HANDLER,
	
	/* custom errors */
	PACMAN_ERROR_CONFIG_INVALID,
	PACMAN_ERROR_PACKAGE_HELD
} PacmanError;

GType pacman_error_get_type (void);
GQuark pacman_error_quark (void);

G_END_DECLS

#endif
