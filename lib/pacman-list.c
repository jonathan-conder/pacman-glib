#include <alpm_list.h>
#include "pacman-list.h"

/**
 * SECTION:pacman-list
 * @title: PacmanList
 * @short_description: Linked lists
 *
 * A #PacmanList contains a list of items and is very similar in usage to #GList.
 */

/**
 * PacmanList:
 *
 * Represents a list, or an entry in a list.
 */

/**
 * pacman_list_new:
 *
 * Creates a new list. Note that this is a convenience function only and simply returns %NULL.
 *
 * Returns: A new #PacmanList. Free with pacman_list_free().
 */
PacmanList *pacman_list_new (void) {
	return NULL;
}

/**
 * pacman_list_free:
 * @list: A #PacmanList.
 *
 * Frees @list.
 */
void pacman_list_free (PacmanList *list) {
	alpm_list_free (list);
}

/**
 * pacman_list_free_contents:
 * @list: A #PacmanList.
 * @func: A #GDestroyNotify function.
 *
 * Frees every item in @list using @func.
 */
void pacman_list_free_contents (PacmanList *list, GDestroyNotify func) {
	alpm_list_free_inner (list, (alpm_list_fn_free) func);
}

/**
 * pacman_list_free_full:
 * @list: A #PacmanList to free.
 * @func: A #GDestroyNotify function.
 *
 * Frees every item in @list using @func, then frees @list itself.
 */
void pacman_list_free_full (PacmanList *list, GDestroyNotify func) {
	pacman_list_free_contents (list, func);
	pacman_list_free (list);
}

/**
 * pacman_list_length:
 * @list: A #PacmanList.
 *
 * Gets the number of items in @list.
 *
 * Returns: The length of @list.
 */
guint pacman_list_length (const PacmanList *list) {
	return alpm_list_count (list);
}

/**
 * pacman_list_get:
 * @entry: An entry in a #PacmanList.
 *
 * Gets the item stored at @entry.
 *
 * Returns: A list item.
 */
gpointer pacman_list_get (const PacmanList *entry) {
	g_return_val_if_fail (entry != NULL, NULL);
	
	return entry->data;
}

/**
 * pacman_list_set:
 * @entry: An entry in a #PacmanList.
 * @item: A list item.
 *
 * Stores @item at @entry.
 */
void pacman_list_set (PacmanList *entry, gpointer item) {
	g_return_if_fail (entry != NULL);
	
	entry->data = item;
}

/**
 * pacman_list_next:
 * @entry: An entry in a #PacmanList.
 *
 * Finds the list entry that follows @entry.
 *
 * Returns: An entry in a #PacmanList, or %NULL if @entry was the last one.
 */
PacmanList *pacman_list_next (const PacmanList *entry) {
	return alpm_list_next (entry);
}

/**
 * pacman_list_nth:
 * @list: A #PacmanList.
 * @n: An integer.
 *
 * Finds the entry in @list at position @n (starting at 0).
 *
 * Returns: An entry in a #PacmanList, or %NULL if @list is shorter than @n items long.
 */
PacmanList *pacman_list_nth (const PacmanList *list, guint n) {
	while (list != NULL && n-- > 0)
		list = list->next;
	return (PacmanList *) list;
}

/**
 * pacman_list_add:
 * @list: A #PacmanList.
 * @item: A list item.
 *
 * Adds @item to the end of @list.
 *
 * Returns: A new reference to @list. Do not use or free @list afterwards.
 */
PacmanList *pacman_list_add (PacmanList *list, gpointer item) {
	return alpm_list_add (list, item);
}

/**
 * pacman_list_add_sorted:
 * @list: A #PacmanList.
 * @item: A list item.
 * @func: A #GCompareFunc function.
 *
 * Adds @item to @list, in the correct position as determined by @func.
 *
 * Returns: A new reference to @list. Do not use or free @list afterwards.
 */
PacmanList *pacman_list_add_sorted (PacmanList *list, gpointer item, GCompareFunc func) {
	return alpm_list_add_sorted (list, item, (alpm_list_fn_cmp) func);
}

/**
 * pacman_list_concat:
 * @first: A #PacmanList.
 * @second: A #PacmanList.
 *
 * Creates a new list by appending @second to @first.
 *
 * Returns: A #PacmanList composed of @first and @second. Do not use or free @first or @second afterwards.
 */
PacmanList *pacman_list_concat (PacmanList *first, PacmanList *second) {
	return alpm_list_join (first, second);
}

/**
 * pacman_list_remove:
 * @haystack: A #PacmanList.
 * @needle: An item to remove.
 * @func: A #GCompareFunc function.
 * @removed: A location to hold a list item, or %NULL if you do not need to use or free it.
 *
 * Removes an item equivalent to @needle (as determined by @func) from @haystack, and places it in @removed.
 *
 * Returns: A new reference to @haystack. Do not use or free @haystack afterwards.
 */
PacmanList *pacman_list_remove (PacmanList *haystack, gconstpointer needle, GCompareFunc func, gpointer *removed) {
	return alpm_list_remove (haystack, needle, (alpm_list_fn_cmp) func, removed);
}

static gint direct_compare (gconstpointer a, gconstpointer b) {
	if (a == b) {
		return 0;
	} else {
		return (a < b) ? -1 : 1;
	}
}

/**
 * pacman_list_remove_direct:
 * @haystack: A #PacmanList.
 * @needle: An item to remove.
 * @removed: A location to hold a list item, or %NULL if you do not need to use or free it.
 *
 * Removes an item that points to the same location as @needle from @haystack, and places it in @removed.
 *
 * Returns: A new reference to @haystack. Do not use or free @haystack afterwards.
 */
PacmanList *pacman_list_remove_direct (PacmanList *haystack, gconstpointer needle, gpointer *removed) {
	return alpm_list_remove (haystack, needle, direct_compare, removed);
}

/**
 * pacman_list_remove_string:
 * @haystack: A #PacmanList.
 * @needle: A string to remove.
 * @removed: A location to hold a string, or %NULL if you do not need to use or free it.
 *
 * Removes a string equal to @needle from @haystack, and places it in @removed.
 *
 * Returns: A new reference to @haystack. Do not use or free @haystack afterwards.
 */
PacmanList *pacman_list_remove_string (PacmanList *haystack, const gchar *needle, gchar **removed) {
	return alpm_list_remove_str (haystack, needle, removed);
}

/**
 * pacman_list_remove_duplicates:
 * @list: A #PacmanList.
 *
 * Creates a new list containing an entry for each unique item in @list.
 *
 * Returns: A #PacmanList. Free with pacman_list_free().
 */
PacmanList *pacman_list_remove_duplicates (const PacmanList *list) {
	return alpm_list_remove_dupes (list);
}

/**
 * pacman_list_find:
 * @haystack: A #PacmanList.
 * @needle: An item to find.
 * @func: A #GCompareFunc function.
 *
 * Searches @haystack for an item equivalent to @needle (as determined by @func).
 *
 * Returns: A list item from @haystack, or %NULL if none were found.
 */
gpointer pacman_list_find (const PacmanList *haystack, gconstpointer needle, GCompareFunc func) {
	return alpm_list_find (haystack, needle, (alpm_list_fn_cmp) func);
}

/**
 * pacman_list_find_direct:
 * @haystack: A #PacmanList.
 * @needle: An item to find.
 *
 * Searches @haystack for an item that points to the same location as @needle.
 *
 * Returns: A list item from @haystack, or %NULL if none were found.
 */
gpointer pacman_list_find_direct (const PacmanList *haystack, gconstpointer needle) {
	return alpm_list_find_ptr (haystack, needle);
}

/**
 * pacman_list_find_string:
 * @haystack: A #PacmanList.
 * @needle: A string to find.
 *
 * Searches @haystack for a string equal to @needle.
 *
 * Returns: A string from @haystack, or %NULL if none were found.
 */
gchar *pacman_list_find_string (const PacmanList *haystack, const gchar *needle) {
	return alpm_list_find_str (haystack, needle);
}

/**
 * pacman_list_sort:
 * @list: A #PacmanList.
 * @func: A #GCompareFunc function.
 *
 * Sorts @list into an order determined by @func.
 *
 * Returns: A sorted #PacmanList. Do not use or free @list afterwards.
 */
PacmanList *pacman_list_sort (PacmanList *list, GCompareFunc func) {
	return alpm_list_msort (list, pacman_list_length (list), (alpm_list_fn_cmp) func);
}

/**
 * pacman_list_reverse:
 * @list: A #PacmanList.
 *
 * Creates a new list with the same contents as @list but in reverse order.
 *
 * Returns: A #PacmanList. Free with pacman_list_free().
 */
PacmanList *pacman_list_reverse (PacmanList *list) {
	return alpm_list_reverse (list);
}

/**
 * pacman_list_diff:
 * @lhs: A #PacmanList.
 * @rhs: A #PacmanList.
 * @func: A #GCompareFunc function.
 *
 * Creates a new list from items in @lhs that have no equivalent in @rhs (as determined by @func).
 *
 * Returns: A #PacmanList. Free with pacman_list_free().
 */
PacmanList *pacman_list_diff (const PacmanList *lhs, const PacmanList *rhs, GCompareFunc func) {
	return alpm_list_diff (lhs, rhs, (alpm_list_fn_cmp) func);
}

/**
 * pacman_list_copy:
 * @list: A #PacmanList.
 *
 * Creates a new list with the same contents as @list.
 *
 * Returns: A #PacmanList. Free with pacman_list_free().
 */
PacmanList *pacman_list_copy (const PacmanList *list) {
	return alpm_list_copy (list);
}

/**
 * pacman_list_strdup:
 * @list: A #PacmanList.
 *
 * Creates a new list by duplicating every string in @list.
 *
 * Returns: A #PacmanList. Free the contents with g_free(), then free the list with pacman_list_free().
 */
PacmanList *pacman_list_strdup (const PacmanList *list) {
	const PacmanList *i;
	PacmanList *result = NULL;
	
	for (i = list; i != NULL; i = pacman_list_next (i)) {
		const gchar *string = (const gchar *) pacman_list_get (i);
		result = pacman_list_add (result, g_strdup (string));
	}
	
	return result;
}
