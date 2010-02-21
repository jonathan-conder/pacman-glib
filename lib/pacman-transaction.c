/* pacman-transaction.c
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

#include <glib/gi18n-lib.h>
#include <alpm.h>
#include "pacman-error.h"
#include "pacman-list.h"
#include "pacman-conflict.h"
#include "pacman-missing-dependency.h"
#include "pacman-package.h"
#include "pacman-database.h"
#include "pacman-manager.h"
#include "pacman-private.h"
#include "pacman-transaction.h"

/**
 * SECTION:pacman-transaction
 * @title: PacmanTransaction
 * @short_description: Manipulate installed packages
 *
 * #PacmanTransaction is an abstract base class for package management operations. Transactions can be obtained from a #PacmanManager and prepared in a transaction-specific way using pacman_transaction_prepare(). At this point the transaction can be carried out using pacman_transaction_commit(), and then cancelled with pacman_transaction_cancel(). Transactions emit a number of signals to report on their progress and/or interact with the user.
 */

/**
 * PacmanTransaction:
 *
 * Represents a package management operation.
 */

#define PACMAN_TRANSACTION_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), PACMAN_TYPE_TRANSACTION, PacmanTransactionPrivate))

G_DEFINE_ABSTRACT_TYPE (PacmanTransaction, pacman_transaction, G_TYPE_OBJECT);

typedef struct _PacmanTransactionPrivate {
	PacmanList *marked_packages;
	PacmanList *missing_dependencies;
	PacmanList *conflicts;
	PacmanList *file_conflicts;
	PacmanList *invalid_files;
} PacmanTransactionPrivate;

static void pacman_transaction_init (PacmanTransaction *transaction) {
	g_return_if_fail (transaction != NULL);
}

static void pacman_transaction_finalize (GObject *object) {
	PacmanTransactionPrivate *priv;
	
	g_return_if_fail (object != NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (PACMAN_TRANSACTION (object));
	pacman_list_free (priv->marked_packages);
	pacman_list_free_full (priv->missing_dependencies, (GDestroyNotify) pacman_missing_dependency_free);
	pacman_list_free_full (priv->conflicts, (GDestroyNotify) pacman_conflict_free);
	pacman_list_free_full (priv->file_conflicts, (GDestroyNotify) pacman_file_conflict_free);
	pacman_list_free (priv->invalid_files);
	
	pacman_transaction_end (NULL);
	pacman_manager_new_transaction (pacman_manager, G_TYPE_NONE);
	
	G_OBJECT_CLASS (pacman_transaction_parent_class)->finalize (object);
}

enum {
	SIGNAL_STATUS,
	SIGNAL_QUESTION,
	SIGNAL_PROGRESS,
	SIGNAL_DOWNLOAD,
	SIGNAL_LAST
};

static guint transaction_signals[SIGNAL_LAST] = { 0 };

static GQuark transaction_signal_statuses[PACMAN_TRANSACTION_STATUS_LAST] = { 0 };

const gchar *pacman_transaction_status_get_nick (PacmanTransactionStatus status);

static void transaction_signal_statuses_make_details (void) {
	gint i;
	for (i = 0; i < PACMAN_TRANSACTION_STATUS_LAST; ++i) {
		const gchar *name = pacman_transaction_status_get_nick (i);
		if (name != NULL) {
			transaction_signal_statuses[i] = g_quark_from_static_string (name);
		}
	}
}

static GQuark transaction_signal_questions[PACMAN_TRANSACTION_QUESTION_LAST] = { 0 };

const gchar *pacman_transaction_question_get_nick (PacmanTransactionQuestion question);

static void transaction_signal_questions_make_details (void) {
	gint i;
	for (i = 0; i < PACMAN_TRANSACTION_QUESTION_LAST; ++i) {
		const gchar *name = pacman_transaction_question_get_nick (i);
		if (name != NULL) {
			transaction_signal_questions[i] = g_quark_from_static_string (name);
		}
	}
}

static GQuark transaction_signal_progresses[PACMAN_TRANSACTION_PROGRESS_LAST] = { 0 };

const gchar *pacman_transaction_progress_get_nick (PacmanTransactionProgress progress);

static void transaction_signal_progresses_make_details (void) {
	gint i;
	for (i = 0; i < PACMAN_TRANSACTION_PROGRESS_LAST; ++i) {
		const gchar *name = pacman_transaction_progress_get_nick (i);
		if (name != NULL) {
			transaction_signal_progresses[i] = g_quark_from_static_string (name);
		}
	}
}

/**
 * pacman_transaction_get_flags:
 * @transaction: A #PacmanTransaction.
 *
 * Gets the flags that were used to configure @transaction.
 *
 * Returns: A set of #PacmanTransactionFlags.
 */
guint32 pacman_transaction_get_flags (PacmanTransaction *transaction) {
	g_return_val_if_fail (transaction != NULL, PACMAN_TRANSACTION_FLAGS_NONE);
	
	/* PacmanTransactionFlags is set up so that this works */
	return (guint32) alpm_trans_get_flags ();
}

/**
 * pacman_transaction_get_packages:
 * @transaction: A #PacmanTransaction.
 *
 * Gets a list of the packages that will be affected when @transaction is committed.
 *
 * Returns: A list of #PacmanPackage. Do not free.
 */
const PacmanList *pacman_transaction_get_packages (PacmanTransaction *transaction) {
	g_return_val_if_fail (transaction != NULL, NULL);
	
	return alpm_trans_get_pkgs ();
}

/**
 * pacman_transaction_get_marked_packages:
 * @transaction: A #PacmanTransaction.
 *
 * Gets a list of packages that have been marked as special in some way by @transaction.
 *
 * Returns: A list of #PacmanPackage. Do not free.
 */
const PacmanList *pacman_transaction_get_marked_packages (PacmanTransaction *transaction) {
	PacmanTransactionPrivate *priv;
	
	g_return_val_if_fail (transaction != NULL, NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	return priv->marked_packages;
}

void pacman_transaction_mark_package (PacmanTransaction *transaction, PacmanPackage *package) {
	PacmanTransactionPrivate *priv;
	
	g_return_if_fail (transaction != NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	priv->marked_packages = pacman_list_add (priv->marked_packages, package);
}

void pacman_transaction_set_marked_packages (PacmanTransaction *transaction, PacmanList *packages) {
	PacmanTransactionPrivate *priv;
	
	g_return_if_fail (transaction != NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	pacman_list_free (priv->marked_packages);
	priv->marked_packages = packages;
}

/**
 * pacman_transaction_get_missing_dependencies:
 * @transaction: A #PacmanTransaction.
 *
 * Gets a list of missing dependencies that need to be satisfied before @transaction can be committed.
 *
 * Returns: A list of #PacmanMissingDependency. Do not free.
 */
const PacmanList *pacman_transaction_get_missing_dependencies (PacmanTransaction *transaction) {
	PacmanTransactionPrivate *priv;
	
	g_return_val_if_fail (transaction != NULL, NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	return priv->missing_dependencies;
}

void pacman_transaction_set_missing_dependencies (PacmanTransaction *transaction, PacmanList *dependencies) {
	PacmanTransactionPrivate *priv;
	
	g_return_if_fail (transaction != NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	pacman_list_free_full (priv->missing_dependencies, (GDestroyNotify) pacman_missing_dependency_free);
	priv->missing_dependencies = dependencies;
}

/**
 * pacman_transaction_get_conflicts:
 * @transaction: A #PacmanTransaction.
 *
 * Gets a list of conflicts that need to be resolved before @transaction can be committed.
 *
 * Returns: A list of #PacmanConflict. Do not free.
 */
const PacmanList *pacman_transaction_get_conflicts (PacmanTransaction *transaction) {
	PacmanTransactionPrivate *priv;
	
	g_return_val_if_fail (transaction != NULL, NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	return priv->conflicts;
}

void pacman_transaction_set_conflicts (PacmanTransaction *transaction, PacmanList *conflicts) {
	PacmanTransactionPrivate *priv;
	
	g_return_if_fail (transaction != NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	pacman_list_free_full (priv->conflicts, (GDestroyNotify) pacman_conflict_free);
	priv->conflicts = conflicts;
}

/**
 * pacman_transaction_get_file_conflicts:
 * @transaction: A #PacmanTransaction.
 *
 * Gets a list of file conflicts that need to be resolved before @transaction can be committed.
 *
 * Returns: A list of #PacmanFileConflict. Do not free.
 */
const PacmanList *pacman_transaction_get_file_conflicts (PacmanTransaction *transaction) {
	PacmanTransactionPrivate *priv;
	
	g_return_val_if_fail (transaction != NULL, NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	return priv->file_conflicts;
}

void pacman_transaction_set_file_conflicts (PacmanTransaction *transaction, PacmanList *conflicts) {
	PacmanTransactionPrivate *priv;
	
	g_return_if_fail (transaction != NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	pacman_list_free_full (priv->file_conflicts, (GDestroyNotify) pacman_file_conflict_free);
	priv->file_conflicts = conflicts;
}

/**
 * pacman_transaction_get_invalid_files:
 * @transaction: A #PacmanTransaction.
 *
 * Gets a list of corrupt files that must be downloaded again before @transaction can be committed.
 *
 * Returns: A list of file names. Do not free.
 */
const PacmanList *pacman_transaction_get_invalid_files (PacmanTransaction *transaction) {
	PacmanTransactionPrivate *priv;
	
	g_return_val_if_fail (transaction != NULL, NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	return priv->invalid_files;
}

void pacman_transaction_set_invalid_files (PacmanTransaction *transaction, PacmanList *filenames) {
	PacmanTransactionPrivate *priv;
	
	g_return_if_fail (transaction != NULL);
	
	priv = PACMAN_TRANSACTION_GET_PRIVATE (transaction);
	pacman_list_free (priv->invalid_files);
	priv->invalid_files = filenames;
}

/**
 * pacman_transaction_prepare:
 * @transaction: A #PacmanTransaction.
 * @targets: A list of strings.
 * @error: A #GError, or %NULL.
 *
 * Prepares @transaction to use @targets in some way. Safe to be called multiple times, but each call will discard the results of the previous one.
 *
 * Returns: %TRUE if the operation succeeded, or %FALSE if @error is set.
 */
gboolean pacman_transaction_prepare (PacmanTransaction *transaction, const PacmanList *targets, GError **error) {
	g_return_val_if_fail (transaction != NULL, FALSE);
	
	return PACMAN_TRANSACTION_GET_CLASS (transaction)->prepare (transaction, targets, error);
}

/**
 * pacman_transaction_commit:
 * @transaction: A #PacmanTransaction.
 * @error: A #GError, or %NULL.
 *
 * Carries out the operation represented by @transaction.
 *
 * Returns: %TRUE if the operation succeeded, or %FALSE if @error is set.
 */
gboolean pacman_transaction_commit (PacmanTransaction *transaction, GError **error) {
	g_return_val_if_fail (transaction != NULL, FALSE);
	
	return PACMAN_TRANSACTION_GET_CLASS (transaction)->commit (transaction, error);
}

static gboolean pacman_transaction_real_commit (PacmanTransaction *transaction, GError **error) {
	g_return_val_if_fail (transaction != NULL, FALSE);
	
	if (alpm_trans_commit (NULL) < 0) {
		g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not commit transaction: %s"), alpm_strerrorlast ());
		return FALSE;
	}
	
	return TRUE;
}

/**
 * pacman_transaction_cancel:
 * @transaction: A #PacmanTransaction.
 * @error: A #GError, or %NULL.
 *
 * Cancels the commit operation of @transaction.
 *
 * Returns: %TRUE if @transaction could be cancelled, or %FALSE if @error is set.
 */
gboolean pacman_transaction_cancel (PacmanTransaction *transaction, GError **error) {
	g_return_val_if_fail (transaction != NULL, FALSE);
	
	if (alpm_trans_interrupt () < 0) {
		g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not cancel transaction: %s"), alpm_strerrorlast ());
		return FALSE;
	}
	
	return TRUE;
}

static void pacman_transaction_tell (PacmanTransaction *transaction, PacmanTransactionStatus status, const gchar *format, ...) {
	va_list args;
	gchar *message;
	
	g_return_if_fail (transaction != NULL);
	g_return_if_fail (status < PACMAN_TRANSACTION_STATUS_LAST);
	
	va_start (args, format);
	message = g_strdup_vprintf (format, args);
	va_end (args);
	
	g_return_if_fail (message != NULL);
	
	g_signal_emit (transaction, transaction_signals[SIGNAL_STATUS], transaction_signal_statuses[status], status, message);
	
	g_free (message);
}

static void pacman_transaction_event_cb (pmtransevt_t event, gpointer data1, gpointer data2) {
	PacmanTransaction *transaction;
	
	g_return_if_fail (pacman_manager != NULL);
	transaction = pacman_manager_get_transaction (pacman_manager);
	g_return_if_fail (transaction != NULL);
	
	switch (event) {
		case PM_TRANS_EVT_CHECKDEPS_START: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DEPENDENCY_CHECK_START, _("Checking dependencies"));
			break;
		} case PM_TRANS_EVT_CHECKDEPS_DONE: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DEPENDENCY_CHECK_END, _("Finished checking dependencies"));
			break;
		} case PM_TRANS_EVT_FILECONFLICTS_START: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_FILE_CONFLICT_CHECK_START, _("Checking for file conflicts"));
			break;
		} case PM_TRANS_EVT_FILECONFLICTS_DONE: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_FILE_CONFLICT_CHECK_END, _("Finished checking for file conflicts"));
			break;
		} case PM_TRANS_EVT_RESOLVEDEPS_START: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DEPENDENCY_RESOLVE_START, _("Resolving dependencies"));
			break;
		} case PM_TRANS_EVT_RESOLVEDEPS_DONE: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DEPENDENCY_RESOLVE_END, _("Finished resolving dependencies"));
			break;
		} case PM_TRANS_EVT_INTERCONFLICTS_START: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_CONFLICT_CHECK_START, _("Checking for conflicts"));
			break;
		} case PM_TRANS_EVT_INTERCONFLICTS_DONE: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_CONFLICT_CHECK_END, _("Finished checking for conflicts"));
			break;
		} case PM_TRANS_EVT_ADD_START: {
			pacman_transaction_set_marked_packages (transaction, pacman_list_add (NULL, data1));
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_INSTALL_START, _("Installing %s"), pacman_package_get_name ((PacmanPackage *) data1));
			pacman_transaction_set_marked_packages (transaction, NULL);
			break;
		} case PM_TRANS_EVT_ADD_DONE: {
			PacmanPackage *package = (PacmanPackage *) data1;
			const PacmanList *optional_dependencies, *i;
			alpm_logaction ("installed %s (%s)\n", pacman_package_get_name (package), pacman_package_get_version (package));
			
			pacman_transaction_set_marked_packages (transaction, pacman_list_add (NULL, data1));
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_INSTALL_END, _("Finished installing %s"), pacman_package_get_name (package));
			pacman_transaction_set_marked_packages (transaction, NULL);
			
			optional_dependencies = pacman_package_get_optional_dependencies (package);
			if (optional_dependencies != NULL) {
				GString *depends = g_string_new ("");
				gchar *message;
				
				g_string_append_printf (depends, _("Optional dependencies for %s:\n"), pacman_package_get_name (package));
				for (i = optional_dependencies; i != NULL; i = pacman_list_next (i)) {
					const gchar *line = (const gchar *) pacman_list_get (i);
					g_string_append_printf (depends, "%s\n", line);
				}
				
				message = g_string_free (depends, FALSE);
				g_message ("%s", message);
				g_free (message);
			}
			break;
		} case PM_TRANS_EVT_REMOVE_START: {
			pacman_transaction_set_marked_packages (transaction, pacman_list_add (NULL, data1));
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_REMOVE_START, _("Removing %s"), pacman_package_get_name ((PacmanPackage *) data1));
			pacman_transaction_set_marked_packages (transaction, NULL);
			break;
		} case PM_TRANS_EVT_REMOVE_DONE: {
			PacmanPackage *package = (PacmanPackage *) data1;
			alpm_logaction ("removed %s (%s)\n", pacman_package_get_name (package), pacman_package_get_version (package));
			
			pacman_transaction_set_marked_packages (transaction, pacman_list_add (NULL, data1));
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_REMOVE_END, _("Finished removing %s"), pacman_package_get_name (package));
			pacman_transaction_set_marked_packages (transaction, NULL);
			break;
		} case PM_TRANS_EVT_UPGRADE_START: {
			PacmanList *new_then_old = NULL;
			new_then_old = pacman_list_add (new_then_old, data1);
			new_then_old = pacman_list_add (new_then_old, data2);
			
			pacman_transaction_set_marked_packages (transaction, new_then_old);
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_UPGRADE_START, _("Upgrading %s"), pacman_package_get_name ((PacmanPackage *) data1));
			pacman_transaction_set_marked_packages (transaction, NULL);
			break;
		} case PM_TRANS_EVT_UPGRADE_DONE: {
			PacmanPackage *package = (PacmanPackage *) data1, *old_package = (PacmanPackage *) data2;
			PacmanList *optional_dependencies, *i, *new_then_old = NULL;
			alpm_logaction ("upgraded %s (%s -> %s)\n", pacman_package_get_name (package), pacman_package_get_version (old_package), pacman_package_get_version (package));
			
			new_then_old = pacman_list_add (new_then_old, data1);
			new_then_old = pacman_list_add (new_then_old, data2);
			
			pacman_transaction_set_marked_packages (transaction, new_then_old);
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_UPGRADE_END, _("Finished upgrading %s"), pacman_package_get_name (package));
			pacman_transaction_set_marked_packages (transaction, NULL);
			
			optional_dependencies = pacman_list_diff (pacman_package_get_optional_dependencies (package), pacman_package_get_optional_dependencies (old_package), (GCompareFunc) g_strcmp0);
			if (optional_dependencies != NULL) {
				GString *depends = g_string_new ("");
				gchar *message;
				
				g_string_append_printf (depends, _("New optional dependencies for %s\n"), pacman_package_get_name (package));
				for (i = optional_dependencies; i != NULL; i = pacman_list_next (i)) {
					const gchar *line = (const gchar *) pacman_list_get (i);
					g_string_append_printf (depends, "%s\n", line);
				}
				
				message = g_string_free (depends, FALSE);
				g_message ("%s", message);
				g_free (message);
				pacman_list_free (optional_dependencies);
			}
			break;
		} case PM_TRANS_EVT_INTEGRITY_START: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_PACKAGE_INTEGRITY_CHECK_START, _("Checking package integrity"));
			break;
		} case PM_TRANS_EVT_INTEGRITY_DONE: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_PACKAGE_INTEGRITY_CHECK_END, _("Finished checking package integrity"));
			break;
		} case PM_TRANS_EVT_DELTA_INTEGRITY_START: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DELTA_INTEGRITY_CHECK_START, _("Checking delta integrity"));
			break;
		} case PM_TRANS_EVT_DELTA_INTEGRITY_DONE: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DELTA_INTEGRITY_CHECK_END, _("Finished checking delta integrity"));
			break;
		} case PM_TRANS_EVT_DELTA_PATCHES_START: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DELTA_PATCHING_START, _("Applying delta patches"));
			break;
		} case PM_TRANS_EVT_DELTA_PATCHES_DONE: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DELTA_PATCHING_END, _("Finished applying delta patches"));
			break;
		} case PM_TRANS_EVT_DELTA_PATCH_START: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DELTA_PATCH_START, _("Creating %s from the delta patch %s"), (const gchar *) data1, (const gchar *) data2);
			break;
		} case PM_TRANS_EVT_DELTA_PATCH_DONE: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DELTA_PATCH_END, _("Finished applying delta patch"));
			break;
		} case PM_TRANS_EVT_DELTA_PATCH_FAILED: {
			/* already reported as an error */
			break;
		} case PM_TRANS_EVT_SCRIPTLET_INFO: {
			g_message ("%s\n", (const gchar *) data1);
			break;
		} case PM_TRANS_EVT_RETRIEVE_START: {
			pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DOWNLOAD_FROM, _("Downloading packages from [%s]"), (const gchar *) data1);
			break;
		} default: {
			g_debug ("Unrecognised event: %d\n", event);
			break;
		}
	}
}

gboolean pacman_transaction_ask (PacmanTransaction *transaction, PacmanTransactionQuestion question, const gchar *format, ...) {
	va_list args;
	gchar *message;
	gboolean result;
	
	g_return_val_if_fail (transaction != NULL, FALSE);
	g_return_val_if_fail (question < PACMAN_TRANSACTION_QUESTION_LAST, FALSE);
	
	va_start (args, format);
	message = g_strdup_vprintf (format, args);
	va_end (args);
	
	g_return_val_if_fail (message != NULL, FALSE);
	
	g_signal_emit (transaction, transaction_signals[SIGNAL_QUESTION], transaction_signal_questions[question], question, message, &result);
	
	g_free (message);
	return result;
}

/* pretty fucked up kludge, keep this in sync with libalpm/conflict.h */
struct __pmconflict_t {
	gchar *first;
	gchar *second;
};

static PacmanConflict *pacman_conflict_new (const gchar *first, const gchar *second) {
	PacmanConflict *result;
	
	g_return_val_if_fail (first != NULL, NULL);
	g_return_val_if_fail (second != NULL, NULL);
	
	result = malloc (sizeof (PacmanConflict));
	g_return_val_if_fail (result != NULL, NULL);
	
	result->first = strdup (first);
	result->second = strdup (second);
	
	g_warn_if_fail (first != pacman_conflict_get_first_package (result));
	g_warn_if_fail (second != pacman_conflict_get_second_package (result));
	
	return result;
}

static void pacman_transaction_question_cb (pmtransconv_t question, gpointer data1, gpointer data2, gpointer data3, gint *response) {
	PacmanTransaction *transaction;
	
	g_return_if_fail (pacman_manager != NULL);
	transaction = pacman_manager_get_transaction (pacman_manager);
	g_return_if_fail (transaction != NULL);
	
	switch (question) {
		case PM_TRANS_CONV_INSTALL_IGNOREPKG: {
			/* called in sync_addtarget only, data1 = ignored package */
			const gchar *name = pacman_package_get_name ((PacmanPackage *) data1), *version = pacman_package_get_version ((PacmanPackage *) data1);
			
			pacman_transaction_set_marked_packages (transaction, pacman_list_add (NULL, data1));
			*response = (gint) pacman_transaction_ask (transaction, PACMAN_TRANSACTION_QUESTION_INSTALL_IGNORE_PACKAGE, _("%s is marked as ignored. Do you want to install version %s anyway?"), name, version);
			pacman_transaction_set_marked_packages (transaction, NULL);
			break;
		} case PM_TRANS_CONV_REPLACE_PKG: {
			/* called in sync_sysupgrade, data1 = package to replace, data2 = replacement package, data3 = database name */
			const gchar *replace = pacman_package_get_name ((PacmanPackage *) data1), *replacement = pacman_package_get_name ((PacmanPackage *) data2);
			PacmanConflict *conflict = pacman_conflict_new (replacement, replace);
			
			pacman_transaction_set_conflicts (transaction, pacman_list_add (NULL, conflict));
			*response = (gint) pacman_transaction_ask (transaction, PACMAN_TRANSACTION_QUESTION_REPLACE_PACKAGE, _("Do you want to replace %s with %s from [%s]?"), replace, replacement, (const gchar *) data3);
			pacman_transaction_set_conflicts (transaction, NULL);
			break;
		} case PM_TRANS_CONV_CONFLICT_PKG: {
			/* called in sync_prepare, data1 = name of sync package, data2 = name of local package */
			const gchar *replacement = (const gchar *) data1, *replace = (const gchar *) data2;
			PacmanConflict *conflict = pacman_conflict_new (replacement, replace);
			
			pacman_transaction_set_conflicts (transaction, pacman_list_add (NULL, conflict));
			*response = (gint) pacman_transaction_ask (transaction, PACMAN_TRANSACTION_QUESTION_REMOVE_CONFLICTING_PACKAGE, _("%s conflicts with %s. Do you want to remove %s?"), replacement, replace, replace);
			pacman_transaction_set_conflicts (transaction, NULL);
			break;
		} case PM_TRANS_CONV_REMOVE_PKGS: {
			/* called in sync_prepare, data1 = list of unsyncable packages */
			gchar *packages = pacman_package_make_list ((PacmanList *) data1);
			
			pacman_transaction_set_marked_packages (transaction, (PacmanList *) data1);
			*response = (gint) pacman_transaction_ask (transaction, PACMAN_TRANSACTION_QUESTION_SKIP_UNRESOLVABLE_PACKAGES, _("The following packages have unresolved dependencies: %s. Do you want to continue without them?"), packages);
			pacman_transaction_set_marked_packages (transaction, NULL);
			
			g_free (packages);
			break;
		} case PM_TRANS_CONV_LOCAL_NEWER: {
			/* isn't called anywhere..., data1 = package that is older than local version */
			PacmanDatabase *database;
			PacmanPackage *package;
			const gchar *version, *name = (const gchar *) data1;
			
			database = pacman_manager_get_local_database (pacman_manager);
			g_return_if_fail (database != NULL);
			
			package = pacman_database_find_package (database, name);
			version = pacman_package_get_version (package);
			
			pacman_transaction_set_marked_packages (transaction, pacman_list_add (NULL, package));
			*response = (gint) pacman_transaction_ask (transaction, PACMAN_TRANSACTION_QUESTION_INSTALL_OLDER_PACKAGE, _("%s-%s is older than the installed version. Do you want to install it anyway?"), name, version);
			pacman_transaction_set_marked_packages (transaction, NULL);
			break;
		} case PM_TRANS_CONV_CORRUPTED_PKG: {
			/* called in sync_commit, data1 = location of corrupted package */
			
			pacman_transaction_set_invalid_files (transaction, pacman_list_add (NULL, data1));
			*response = (gint) pacman_transaction_ask (transaction, PACMAN_TRANSACTION_QUESTION_DELETE_CORRUPTED_PACKAGE, _("The package at %s is corrupted. Do you want to delete it?"), (const gchar *) data1);
			pacman_transaction_set_invalid_files (transaction, NULL);
			break;
		} default: {
			g_debug ("Unrecognised question: %d\n", question);
			break;
		}
	}
}

static gboolean pacman_transaction_question_accumulator (GSignalInvocationHint *hint, GValue *result, const GValue *response, gpointer data) {
	g_return_val_if_fail (result != NULL, FALSE);
	g_return_val_if_fail (response != NULL, FALSE);
	
	/* we need at least one TRUE to give a TRUE result */
	if (g_value_get_boolean (response)) {
		g_value_set_boolean (result, TRUE);
	}
	
	return TRUE;
}

static void pacman_transaction_progress_cb (pmtransprog_t type, const gchar *target, gint percent, gint targets, gint current) {
	PacmanTransaction *transaction;
	static gint last_percent = 101;
	
	g_return_if_fail (target != NULL);
	g_return_if_fail (type < PACMAN_TRANSACTION_PROGRESS_LAST);
	g_return_if_fail (targets > 0);
	g_return_if_fail (current > 0);
	g_return_if_fail (current < targets);
	
	g_return_if_fail (pacman_manager != NULL);
	transaction = pacman_manager_get_transaction (pacman_manager);
	g_return_if_fail (transaction != NULL);
	
	if (percent < 0) {
		percent = 0;
	} else if (percent > 100) {
		percent = 100;
	}
	
	if (percent != last_percent) {
		last_percent = percent;
		
		/* PacmanTransactionProgress is set up so that this works */
		g_signal_emit (transaction, transaction_signals[SIGNAL_PROGRESS], transaction_signal_progresses[type], (PacmanTransactionProgress) type, target, (guint) percent, (guint) current, (guint) targets);
	}
}

static void pacman_transaction_download_cb (const gchar *filename, off_t complete, off_t total) {
	PacmanTransaction *transaction;
	
	g_return_if_fail (filename != NULL);
	g_return_if_fail (pacman_manager != NULL);
	
	transaction = pacman_manager_get_transaction (pacman_manager);
	g_return_if_fail (transaction != NULL);
	
	g_signal_emit (transaction, transaction_signals[SIGNAL_DOWNLOAD], 0, filename, (guint) complete, (guint) total);
}

static void pacman_transaction_total_download_cb (off_t total) {
	PacmanTransaction *transaction;
	
	g_return_if_fail (pacman_manager != NULL);
	transaction = pacman_manager_get_transaction (pacman_manager);
	g_return_if_fail (transaction != NULL);
	
	if (total == 0) {
		g_signal_emit (transaction, transaction_signals[SIGNAL_DOWNLOAD], 0, NULL, (guint) 0, (guint) 0);
		pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DOWNLOAD_END, _("Finished downloading packages"));
	} else {
		g_signal_emit (transaction, transaction_signals[SIGNAL_DOWNLOAD], 0, NULL, (guint) 0, (guint) total);
		pacman_transaction_tell (transaction, PACMAN_TRANSACTION_STATUS_DOWNLOAD_START, _("Downloading packages"));
	}
}

gboolean pacman_transaction_start (pmtranstype_t type, guint32 flags, GError **error) {
	if (alpm_trans_init (type, flags, pacman_transaction_event_cb, pacman_transaction_question_cb, pacman_transaction_progress_cb) < 0) {
		if (pm_errno == PACMAN_ERROR_ALREADY_RUNNING) {
			g_message (_("If you are certain no other package manager is running, you can remove %s\n"), alpm_option_get_lockfile ());
		}
		
		g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not initialize transaction: %s"), alpm_strerrorlast ());
		return FALSE;
	}
	
	alpm_option_set_dlcb (pacman_transaction_download_cb);
	alpm_option_set_totaldlcb (pacman_transaction_total_download_cb);
	return TRUE;
}

gboolean pacman_transaction_end (GError **error) {
	alpm_option_set_dlcb (NULL);
	alpm_option_set_totaldlcb (NULL);
	
	if (alpm_trans_release () < 0) {
		g_set_error (error, PACMAN_ERROR, pm_errno, _("Could not release transaction: %s"), alpm_strerrorlast ());
		return FALSE;
	}
	
	return TRUE;
}

gboolean pacman_transaction_restart (PacmanTransaction *transaction, GError **error) {
	pmtranstype_t type = alpm_trans_get_type ();
	guint32 flags = pacman_transaction_get_flags (transaction);
	
	pacman_transaction_set_marked_packages (transaction, NULL);
	pacman_transaction_set_missing_dependencies (transaction, NULL);
	pacman_transaction_set_conflicts (transaction, NULL);
	pacman_transaction_set_file_conflicts (transaction, NULL);
	pacman_transaction_set_invalid_files (transaction, NULL);
	
	if (!pacman_transaction_end (error) || !pacman_transaction_start (type, flags, error)) {
		return FALSE;
	}
	
	return TRUE;
}

void g_cclosure_user_marshal_VOID__ENUM_STRING (GClosure *closure, GValue *result, guint param_count, const GValue *param_values, gpointer hint, gpointer marshal_data);
void g_cclosure_user_marshal_BOOLEAN__ENUM_STRING (GClosure *closure, GValue *result, guint param_count, const GValue *param_values, gpointer hint, gpointer marshal_data);
void g_cclosure_user_marshal_VOID__ENUM_STRING_UINT_UINT_UINT (GClosure *closure, GValue *result, guint param_count, const GValue *param_values, gpointer hint, gpointer marshal_data);
void g_cclosure_user_marshal_VOID__STRING_UINT_UINT (GClosure *closure, GValue *result, guint param_count, const GValue *param_values, gpointer hint, gpointer marshal_data);

static void pacman_transaction_class_init (PacmanTransactionClass *klass) {
	g_return_if_fail (klass != NULL);
	
	g_type_class_add_private (klass, sizeof (PacmanTransactionPrivate));
	
	G_OBJECT_CLASS (klass)->finalize = pacman_transaction_finalize;
	
	klass->prepare = NULL;
	klass->commit = pacman_transaction_real_commit;
	
	/**
	 * PacmanTransaction::status:
	 * @transaction: The current #PacmanTransaction.
	 * @status: A #PacmanTransactionStatus.
	 * @message: A status message.
	 *
	 * Emitted when an operation starts or finishes. Both @status and @message represent the type of operation starting or finishing.
	 */
	transaction_signals[SIGNAL_STATUS] = g_signal_new ("status", PACMAN_TYPE_TRANSACTION, G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED, 0, NULL, NULL, g_cclosure_user_marshal_VOID__ENUM_STRING, G_TYPE_NONE, 2, PACMAN_TYPE_TRANSACTION_STATUS, G_TYPE_STRING);
	transaction_signal_statuses_make_details ();
	
	/**
	 * PacmanTransaction::question:
	 * @transaction: The current #PacmanTransaction.
	 * @question: A #PacmanTransactionQuestion.
	 * @message: A question message.
	 *
	 * Emitted when the user needs to respond to a question. Both @question and @message represent the type of question being asked.
	 *
	 * Returns: TRUE if the user agreed to @message or FALSE otherwise.
	 */
	transaction_signals[SIGNAL_QUESTION] = g_signal_new ("question", PACMAN_TYPE_TRANSACTION, G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED, 0, pacman_transaction_question_accumulator, NULL, g_cclosure_user_marshal_BOOLEAN__ENUM_STRING, G_TYPE_BOOLEAN, 2, PACMAN_TYPE_TRANSACTION_QUESTION, G_TYPE_STRING);
	transaction_signal_questions_make_details ();
	
	/**
	 * PacmanTransaction::progress:
	 * @transaction: The current #PacmanTransaction.
	 * @type: A #PacmanTransactionProgress.
	 * @target: The name of a package.
	 * @percent: The percentage of the operation completed.
	 * @current: The number of the current operation.
	 * @targets: The number of operations to be carried out.
	 *
	 * Emitted when an operation makes some progress towards completion. The operation is of type @type and will affect @target in some way.
	 */
	transaction_signals[SIGNAL_PROGRESS] = g_signal_new ("progress", PACMAN_TYPE_TRANSACTION, G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED, 0, NULL, NULL, g_cclosure_user_marshal_VOID__ENUM_STRING_UINT_UINT_UINT, G_TYPE_NONE, 5, PACMAN_TYPE_TRANSACTION_PROGRESS, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT);
	transaction_signal_progresses_make_details ();
	
	/**
	 * PacmanTransaction::download:
	 * @transaction: The current #PacmanTransaction.
	 * @filename: The basename of a file being downloaded.
	 * @complete: The proportion of the download completed, in bytes.
	 * @total: The size of the file being downloaded, in bytes.
	 *
	 * Emitted when downloading @filename makes some progress towards completion.
	 */
	transaction_signals[SIGNAL_DOWNLOAD] = g_signal_new ("download", PACMAN_TYPE_TRANSACTION, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__STRING_UINT_UINT, G_TYPE_NONE, 3, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT);
}
