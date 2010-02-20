<?xml version="1.0"?>
<api version="1.0">
	<namespace name="Pacman">
		<function name="error_quark" symbol="pacman_error_quark">
			<return-type type="GQuark"/>
		</function>
		<callback name="PacmanTransferFunc">
			<return-type type="gboolean"/>
			<parameters>
				<parameter name="manager" type="PacmanManager*"/>
				<parameter name="url" type="gchar*"/>
				<parameter name="filename" type="gchar*"/>
				<parameter name="mtime" type="time_t*"/>
				<parameter name="user_data" type="gpointer"/>
			</parameters>
		</callback>
		<struct name="PacmanConflict">
			<method name="check_packages" symbol="pacman_conflict_check_packages">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="packages" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="free" symbol="pacman_conflict_free">
				<return-type type="void"/>
				<parameters>
					<parameter name="conflict" type="PacmanConflict*"/>
				</parameters>
			</method>
			<method name="get_first_package" symbol="pacman_conflict_get_first_package">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="conflict" type="PacmanConflict*"/>
				</parameters>
			</method>
			<method name="get_second_package" symbol="pacman_conflict_get_second_package">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="conflict" type="PacmanConflict*"/>
				</parameters>
			</method>
		</struct>
		<struct name="PacmanDatabase">
			<method name="add_server" symbol="pacman_database_add_server">
				<return-type type="void"/>
				<parameters>
					<parameter name="database" type="PacmanDatabase*"/>
					<parameter name="url" type="gchar*"/>
				</parameters>
			</method>
			<method name="find_group" symbol="pacman_database_find_group">
				<return-type type="PacmanGroup*"/>
				<parameters>
					<parameter name="database" type="PacmanDatabase*"/>
					<parameter name="name" type="gchar*"/>
				</parameters>
			</method>
			<method name="find_package" symbol="pacman_database_find_package">
				<return-type type="PacmanPackage*"/>
				<parameters>
					<parameter name="database" type="PacmanDatabase*"/>
					<parameter name="name" type="gchar*"/>
				</parameters>
			</method>
			<method name="get_groups" symbol="pacman_database_get_groups">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="database" type="PacmanDatabase*"/>
				</parameters>
			</method>
			<method name="get_name" symbol="pacman_database_get_name">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="database" type="PacmanDatabase*"/>
				</parameters>
			</method>
			<method name="get_packages" symbol="pacman_database_get_packages">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="database" type="PacmanDatabase*"/>
				</parameters>
			</method>
			<method name="get_server" symbol="pacman_database_get_server">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="database" type="PacmanDatabase*"/>
				</parameters>
			</method>
			<method name="search" symbol="pacman_database_search">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="database" type="PacmanDatabase*"/>
					<parameter name="needles" type="PacmanList*"/>
				</parameters>
			</method>
		</struct>
		<struct name="PacmanDelta">
			<method name="get_from_filename" symbol="pacman_delta_get_from_filename">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="delta" type="PacmanDelta*"/>
				</parameters>
			</method>
			<method name="get_patch_filename" symbol="pacman_delta_get_patch_filename">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="delta" type="PacmanDelta*"/>
				</parameters>
			</method>
			<method name="get_patch_md5sum" symbol="pacman_delta_get_patch_md5sum">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="delta" type="PacmanDelta*"/>
				</parameters>
			</method>
			<method name="get_patch_size" symbol="pacman_delta_get_patch_size">
				<return-type type="goffset"/>
				<parameters>
					<parameter name="delta" type="PacmanDelta*"/>
				</parameters>
			</method>
			<method name="get_to_filename" symbol="pacman_delta_get_to_filename">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="delta" type="PacmanDelta*"/>
				</parameters>
			</method>
		</struct>
		<struct name="PacmanDependency">
			<method name="get_compare_operation" symbol="pacman_dependency_get_compare_operation">
				<return-type type="PacmanDependencyCompare"/>
				<parameters>
					<parameter name="dependency" type="PacmanDependency*"/>
				</parameters>
			</method>
			<method name="get_name" symbol="pacman_dependency_get_name">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="dependency" type="PacmanDependency*"/>
				</parameters>
			</method>
			<method name="get_version" symbol="pacman_dependency_get_version">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="dependency" type="PacmanDependency*"/>
				</parameters>
			</method>
			<method name="satisfied_by" symbol="pacman_dependency_satisfied_by">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="dependency" type="PacmanDependency*"/>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="to_string" symbol="pacman_dependency_to_string">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="dependency" type="PacmanDependency*"/>
				</parameters>
			</method>
		</struct>
		<struct name="PacmanFileConflict">
			<method name="get_file" symbol="pacman_file_conflict_get_file">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="conflict" type="PacmanFileConflict*"/>
				</parameters>
			</method>
			<method name="get_package" symbol="pacman_file_conflict_get_package">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="conflict" type="PacmanFileConflict*"/>
				</parameters>
			</method>
			<method name="get_second_package" symbol="pacman_file_conflict_get_second_package">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="conflict" type="PacmanFileConflict*"/>
				</parameters>
			</method>
		</struct>
		<struct name="PacmanGroup">
			<method name="get_name" symbol="pacman_group_get_name">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="group" type="PacmanGroup*"/>
				</parameters>
			</method>
			<method name="get_packages" symbol="pacman_group_get_packages">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="group" type="PacmanGroup*"/>
				</parameters>
			</method>
		</struct>
		<struct name="PacmanList">
			<method name="add" symbol="pacman_list_add">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
					<parameter name="item" type="gpointer"/>
				</parameters>
			</method>
			<method name="add_sorted" symbol="pacman_list_add_sorted">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
					<parameter name="item" type="gpointer"/>
					<parameter name="func" type="GCompareFunc"/>
				</parameters>
			</method>
			<method name="concat" symbol="pacman_list_concat">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="first" type="PacmanList*"/>
					<parameter name="second" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="copy" symbol="pacman_list_copy">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="diff" symbol="pacman_list_diff">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="lhs" type="PacmanList*"/>
					<parameter name="rhs" type="PacmanList*"/>
					<parameter name="func" type="GCompareFunc"/>
				</parameters>
			</method>
			<method name="find" symbol="pacman_list_find">
				<return-type type="gpointer"/>
				<parameters>
					<parameter name="haystack" type="PacmanList*"/>
					<parameter name="needle" type="gconstpointer"/>
					<parameter name="func" type="GCompareFunc"/>
				</parameters>
			</method>
			<method name="find_direct" symbol="pacman_list_find_direct">
				<return-type type="gpointer"/>
				<parameters>
					<parameter name="haystack" type="PacmanList*"/>
					<parameter name="needle" type="gconstpointer"/>
				</parameters>
			</method>
			<method name="find_string" symbol="pacman_list_find_string">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="haystack" type="PacmanList*"/>
					<parameter name="needle" type="gchar*"/>
				</parameters>
			</method>
			<method name="free" symbol="pacman_list_free">
				<return-type type="void"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="free_contents" symbol="pacman_list_free_contents">
				<return-type type="void"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
					<parameter name="func" type="GDestroyNotify"/>
				</parameters>
			</method>
			<method name="free_full" symbol="pacman_list_free_full">
				<return-type type="void"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
					<parameter name="func" type="GDestroyNotify"/>
				</parameters>
			</method>
			<method name="get" symbol="pacman_list_get">
				<return-type type="gpointer"/>
				<parameters>
					<parameter name="entry" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="length" symbol="pacman_list_length">
				<return-type type="guint"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="next" symbol="pacman_list_next">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="entry" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="nth" symbol="pacman_list_nth">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
					<parameter name="n" type="guint"/>
				</parameters>
			</method>
			<method name="remove" symbol="pacman_list_remove">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="haystack" type="PacmanList*"/>
					<parameter name="needle" type="gconstpointer"/>
					<parameter name="func" type="GCompareFunc"/>
					<parameter name="removed" type="gpointer*"/>
				</parameters>
			</method>
			<method name="remove_direct" symbol="pacman_list_remove_direct">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="haystack" type="PacmanList*"/>
					<parameter name="needle" type="gconstpointer"/>
					<parameter name="removed" type="gpointer*"/>
				</parameters>
			</method>
			<method name="remove_duplicates" symbol="pacman_list_remove_duplicates">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="remove_string" symbol="pacman_list_remove_string">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="haystack" type="PacmanList*"/>
					<parameter name="needle" type="gchar*"/>
					<parameter name="removed" type="gchar**"/>
				</parameters>
			</method>
			<method name="reverse" symbol="pacman_list_reverse">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="set" symbol="pacman_list_set">
				<return-type type="void"/>
				<parameters>
					<parameter name="entry" type="PacmanList*"/>
					<parameter name="item" type="gpointer"/>
				</parameters>
			</method>
			<method name="sort" symbol="pacman_list_sort">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
					<parameter name="func" type="GCompareFunc"/>
				</parameters>
			</method>
			<method name="strdup" symbol="pacman_list_strdup">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="list" type="PacmanList*"/>
				</parameters>
			</method>
		</struct>
		<struct name="PacmanMissingDependency">
			<method name="free" symbol="pacman_missing_dependency_free">
				<return-type type="void"/>
				<parameters>
					<parameter name="dependency" type="PacmanMissingDependency*"/>
				</parameters>
			</method>
			<method name="get_causing_package" symbol="pacman_missing_dependency_get_causing_package">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="dependency" type="PacmanMissingDependency*"/>
				</parameters>
			</method>
			<method name="get_dependency" symbol="pacman_missing_dependency_get_dependency">
				<return-type type="PacmanDependency*"/>
				<parameters>
					<parameter name="dependency" type="PacmanMissingDependency*"/>
				</parameters>
			</method>
			<method name="get_package" symbol="pacman_missing_dependency_get_package">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="dependency" type="PacmanMissingDependency*"/>
				</parameters>
			</method>
		</struct>
		<struct name="PacmanPackage">
			<method name="check_md5sum" symbol="pacman_package_check_md5sum">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="compare_version" symbol="pacman_package_compare_version">
				<return-type type="gint"/>
				<parameters>
					<parameter name="a" type="gchar*"/>
					<parameter name="b" type="gchar*"/>
				</parameters>
			</method>
			<method name="find_new_version" symbol="pacman_package_find_new_version">
				<return-type type="PacmanPackage*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
					<parameter name="databases" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="find_required_by" symbol="pacman_package_find_required_by">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="free" symbol="pacman_package_free">
				<return-type type="void"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="generate_md5sum" symbol="pacman_package_generate_md5sum">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="filename" type="gchar*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="get_arch" symbol="pacman_package_get_arch">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_backup" symbol="pacman_package_get_backup">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_build_date" symbol="pacman_package_get_build_date">
				<return-type type="time_t"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_conflicts" symbol="pacman_package_get_conflicts">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_database" symbol="pacman_package_get_database">
				<return-type type="PacmanDatabase*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_deltas" symbol="pacman_package_get_deltas">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_dependencies" symbol="pacman_package_get_dependencies">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_description" symbol="pacman_package_get_description">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_download_size" symbol="pacman_package_get_download_size">
				<return-type type="goffset"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_filename" symbol="pacman_package_get_filename">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_files" symbol="pacman_package_get_files">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_groups" symbol="pacman_package_get_groups">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_install_date" symbol="pacman_package_get_install_date">
				<return-type type="time_t"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_installed_size" symbol="pacman_package_get_installed_size">
				<return-type type="goffset"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_licenses" symbol="pacman_package_get_licenses">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_md5sum" symbol="pacman_package_get_md5sum">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_name" symbol="pacman_package_get_name">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_optional_dependencies" symbol="pacman_package_get_optional_dependencies">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_packager" symbol="pacman_package_get_packager">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_provides" symbol="pacman_package_get_provides">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_removes" symbol="pacman_package_get_removes">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_replaces" symbol="pacman_package_get_replaces">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_size" symbol="pacman_package_get_size">
				<return-type type="goffset"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_url" symbol="pacman_package_get_url">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="get_version" symbol="pacman_package_get_version">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="has_force" symbol="pacman_package_has_force">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="has_install_scriptlet" symbol="pacman_package_has_install_scriptlet">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="make_list" symbol="pacman_package_make_list">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="packages" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="new_from_file" symbol="pacman_package_new_from_file">
				<return-type type="PacmanPackage*"/>
				<parameters>
					<parameter name="filename" type="gchar*"/>
					<parameter name="full" type="gboolean"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="read_changelog" symbol="pacman_package_read_changelog">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
			<method name="was_explicitly_installed" symbol="pacman_package_was_explicitly_installed">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="package" type="PacmanPackage*"/>
				</parameters>
			</method>
		</struct>
		<enum name="PacmanDependencyCompare" type-name="PacmanDependencyCompare" get-type="pacman_dependency_compare_get_type">
			<member name="PACMAN_DEPENDENCY_COMPARE_ANY" value="1"/>
			<member name="PACMAN_DEPENDENCY_COMPARE_EQUAL" value="2"/>
			<member name="PACMAN_DEPENDENCY_COMPARE_NEWER_OR_EQUAL" value="3"/>
			<member name="PACMAN_DEPENDENCY_COMPARE_OLDER_OR_EQUAL" value="4"/>
			<member name="PACMAN_DEPENDENCY_COMPARE_NEWER" value="5"/>
			<member name="PACMAN_DEPENDENCY_COMPARE_OLDER" value="6"/>
		</enum>
		<enum name="PacmanError" type-name="PacmanError" get-type="pacman_error_get_type">
			<member name="PACMAN_ERROR_MEMORY" value="1"/>
			<member name="PACMAN_ERROR_SYSTEM" value="2"/>
			<member name="PACMAN_ERROR_NOT_PERMITTED" value="3"/>
			<member name="PACMAN_ERROR_FILE_NOT_FOUND" value="4"/>
			<member name="PACMAN_ERROR_DIRECTORY_NOT_FOUND" value="5"/>
			<member name="PACMAN_ERROR_INVALID_ARGS" value="6"/>
			<member name="PACMAN_ERROR_NOT_INITIALIZED" value="7"/>
			<member name="PACMAN_ERROR_ALREADY_INITIALIZED" value="8"/>
			<member name="PACMAN_ERROR_ALREADY_RUNNING" value="9"/>
			<member name="PACMAN_ERROR_DATABASE_OPEN_FAILED" value="10"/>
			<member name="PACMAN_ERROR_DATABASE_CREATE_FAILED" value="11"/>
			<member name="PACMAN_ERROR_DATABASE_NOT_INITIALIZED" value="12"/>
			<member name="PACMAN_ERROR_DATABASE_ALREADY_INITIALIZED" value="13"/>
			<member name="PACMAN_ERROR_DATABASE_NOT_FOUND" value="14"/>
			<member name="PACMAN_ERROR_DATABASE_UPDATE_FAILED" value="15"/>
			<member name="PACMAN_ERROR_DATABASE_REMOVE_FAILED" value="16"/>
			<member name="PACMAN_ERROR_SERVER_INVALID_URL" value="17"/>
			<member name="PACMAN_ERROR_SERVER_NONE_AVAILABLE" value="18"/>
			<member name="PACMAN_ERROR_TRANSACTION_ALREADY_INITIALIZED" value="19"/>
			<member name="PACMAN_ERROR_TRANSACTION_NOT_INITIALIZED" value="20"/>
			<member name="PACMAN_ERROR_TRANSACTION_DUPLICATE_TARGET" value="21"/>
			<member name="PACMAN_ERROR_TRANSACTION_NOT_READY" value="22"/>
			<member name="PACMAN_ERROR_TRANSACTION_NOT_PREPARED" value="23"/>
			<member name="PACMAN_ERROR_TRANSACTION_ABORTED" value="24"/>
			<member name="PACMAN_ERROR_TRANSACTION_INVALID_OPERATION" value="25"/>
			<member name="PACMAN_ERROR_TRANSACTION_NOT_LOCKED" value="26"/>
			<member name="PACMAN_ERROR_PACKAGE_NOT_FOUND" value="27"/>
			<member name="PACMAN_ERROR_PACKAGE_IGNORED" value="28"/>
			<member name="PACMAN_ERROR_PACKAGE_INVALID" value="29"/>
			<member name="PACMAN_ERROR_PACKAGE_OPEN_FAILED" value="30"/>
			<member name="PACMAN_ERROR_PACKAGE_REMOVE_FAILED" value="31"/>
			<member name="PACMAN_ERROR_PACKAGE_UNKNOWN_FILENAME" value="32"/>
			<member name="PACMAN_ERROR_PACKAGE_DATABASE_NOT_FOUND" value="33"/>
			<member name="PACMAN_ERROR_DELTA_INVALID" value="34"/>
			<member name="PACMAN_ERROR_DELTA_PATCH_FAILED" value="35"/>
			<member name="PACMAN_ERROR_DEPENDENCY_UNSATISFIED" value="36"/>
			<member name="PACMAN_ERROR_CONFLICT" value="37"/>
			<member name="PACMAN_ERROR_FILE_CONFLICT" value="38"/>
			<member name="PACMAN_ERROR_DOWNLOAD_FAILED" value="39"/>
			<member name="PACMAN_ERROR_REGEX_INVALID" value="40"/>
			<member name="PACMAN_ERROR_LIBARCHIVE" value="41"/>
			<member name="PACMAN_ERROR_LIBFETCH" value="42"/>
			<member name="PACMAN_ERROR_DOWNLOAD_HANDLER" value="43"/>
			<member name="PACMAN_ERROR_CONFIG_INVALID" value="44"/>
			<member name="PACMAN_ERROR_PACKAGE_HELD" value="45"/>
		</enum>
		<enum name="PacmanTransactionProgress" type-name="PacmanTransactionProgress" get-type="pacman_transaction_progress_get_type">
			<member name="PACMAN_TRANSACTION_PROGRESS_INSTALL" value="0"/>
			<member name="PACMAN_TRANSACTION_PROGRESS_UPGRADE" value="1"/>
			<member name="PACMAN_TRANSACTION_PROGRESS_REMOVE" value="2"/>
			<member name="PACMAN_TRANSACTION_PROGRESS_FILE_CONFLICT_CHECK" value="3"/>
		</enum>
		<enum name="PacmanTransactionQuestion" type-name="PacmanTransactionQuestion" get-type="pacman_transaction_question_get_type">
			<member name="PACMAN_TRANSACTION_QUESTION_INSTALL_IGNORE_PACKAGE" value="0"/>
			<member name="PACMAN_TRANSACTION_QUESTION_REPLACE_PACKAGE" value="1"/>
			<member name="PACMAN_TRANSACTION_QUESTION_REMOVE_CONFLICTING_PACKAGE" value="2"/>
			<member name="PACMAN_TRANSACTION_QUESTION_SKIP_UNRESOLVABLE_PACKAGES" value="3"/>
			<member name="PACMAN_TRANSACTION_QUESTION_INSTALL_OLDER_PACKAGE" value="4"/>
			<member name="PACMAN_TRANSACTION_QUESTION_DELETE_CORRUPTED_PACKAGE" value="5"/>
			<member name="PACMAN_TRANSACTION_QUESTION_REMOVE_HOLD_PACKAGES" value="6"/>
			<member name="PACMAN_TRANSACTION_QUESTION_SYNC_FIRST" value="7"/>
		</enum>
		<enum name="PacmanTransactionStatus" type-name="PacmanTransactionStatus" get-type="pacman_transaction_status_get_type">
			<member name="PACMAN_TRANSACTION_STATUS_DEPENDENCY_CHECK_START" value="0"/>
			<member name="PACMAN_TRANSACTION_STATUS_DEPENDENCY_CHECK_END" value="1"/>
			<member name="PACMAN_TRANSACTION_STATUS_FILE_CONFLICT_CHECK_START" value="2"/>
			<member name="PACMAN_TRANSACTION_STATUS_FILE_CONFLICT_CHECK_END" value="3"/>
			<member name="PACMAN_TRANSACTION_STATUS_DEPENDENCY_RESOLVE_START" value="4"/>
			<member name="PACMAN_TRANSACTION_STATUS_DEPENDENCY_RESOLVE_END" value="5"/>
			<member name="PACMAN_TRANSACTION_STATUS_CONFLICT_CHECK_START" value="6"/>
			<member name="PACMAN_TRANSACTION_STATUS_CONFLICT_CHECK_END" value="7"/>
			<member name="PACMAN_TRANSACTION_STATUS_INSTALL_START" value="8"/>
			<member name="PACMAN_TRANSACTION_STATUS_INSTALL_END" value="9"/>
			<member name="PACMAN_TRANSACTION_STATUS_REMOVE_START" value="10"/>
			<member name="PACMAN_TRANSACTION_STATUS_REMOVE_END" value="11"/>
			<member name="PACMAN_TRANSACTION_STATUS_UPGRADE_START" value="12"/>
			<member name="PACMAN_TRANSACTION_STATUS_UPGRADE_END" value="13"/>
			<member name="PACMAN_TRANSACTION_STATUS_PACKAGE_INTEGRITY_CHECK_START" value="14"/>
			<member name="PACMAN_TRANSACTION_STATUS_PACKAGE_INTEGRITY_CHECK_END" value="15"/>
			<member name="PACMAN_TRANSACTION_STATUS_DELTA_INTEGRITY_CHECK_START" value="16"/>
			<member name="PACMAN_TRANSACTION_STATUS_DELTA_INTEGRITY_CHECK_END" value="17"/>
			<member name="PACMAN_TRANSACTION_STATUS_DELTA_PATCHING_START" value="18"/>
			<member name="PACMAN_TRANSACTION_STATUS_DELTA_PATCHING_END" value="19"/>
			<member name="PACMAN_TRANSACTION_STATUS_DELTA_PATCH_START" value="20"/>
			<member name="PACMAN_TRANSACTION_STATUS_DELTA_PATCH_END" value="21"/>
			<member name="PACMAN_TRANSACTION_STATUS_DOWNLOAD_START" value="22"/>
			<member name="PACMAN_TRANSACTION_STATUS_DOWNLOAD_FROM" value="23"/>
			<member name="PACMAN_TRANSACTION_STATUS_DOWNLOAD_END" value="24"/>
		</enum>
		<flags name="PacmanTransactionFlags" type-name="PacmanTransactionFlags" get-type="pacman_transaction_flags_get_type">
			<member name="PACMAN_TRANSACTION_FLAGS_NONE" value="0"/>
			<member name="PACMAN_TRANSACTION_FLAGS_IGNORE_DEPENDENCIES" value="1"/>
			<member name="PACMAN_TRANSACTION_FLAGS_IGNORE_FILE_CONFLICTS" value="2"/>
			<member name="PACMAN_TRANSACTION_FLAGS_REMOVE_BACKUPS" value="4"/>
			<member name="PACMAN_TRANSACTION_FLAGS_REMOVE_CASCADE" value="16"/>
			<member name="PACMAN_TRANSACTION_FLAGS_REMOVE_RECURSIVE" value="32"/>
			<member name="PACMAN_TRANSACTION_FLAGS_REMOVE_KEEP_FILES" value="64"/>
			<member name="PACMAN_TRANSACTION_FLAGS_INSTALL_IMPLICIT" value="256"/>
			<member name="PACMAN_TRANSACTION_FLAGS_SYNC_DOWNLOAD_ONLY" value="512"/>
			<member name="PACMAN_TRANSACTION_FLAGS_INSTALL_IGNORE_SCRIPTLET" value="1024"/>
			<member name="PACMAN_TRANSACTION_FLAGS_IGNORE_DEPENDENCY_CONFLICTS" value="2048"/>
			<member name="PACMAN_TRANSACTION_FLAGS_SYNC_ALLOW_DOWNGRADE" value="4096"/>
			<member name="PACMAN_TRANSACTION_FLAGS_SYNC_OUTDATED_ONLY" value="8192"/>
			<member name="PACMAN_TRANSACTION_FLAGS_INSTALL_EXPLICIT" value="16384"/>
			<member name="PACMAN_TRANSACTION_FLAGS_REMOVE_UNNEEDED_ONLY" value="32768"/>
			<member name="PACMAN_TRANSACTION_FLAGS_REMOVE_RECURSIVE_EXPLICIT" value="65536"/>
			<member name="PACMAN_TRANSACTION_FLAGS_IGNORE_DATABASE_LOCK" value="131072"/>
		</flags>
		<object name="PacmanInstall" parent="PacmanTransaction" type-name="PacmanInstall" get-type="pacman_install_get_type">
		</object>
		<object name="PacmanManager" parent="GObject" type-name="PacmanManager" get-type="pacman_manager_get_type">
			<method name="add_cache_path" symbol="pacman_manager_add_cache_path">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="path" type="gchar*"/>
				</parameters>
			</method>
			<method name="add_hold_package" symbol="pacman_manager_add_hold_package">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="package" type="gchar*"/>
				</parameters>
			</method>
			<method name="add_ignore_group" symbol="pacman_manager_add_ignore_group">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="group" type="gchar*"/>
				</parameters>
			</method>
			<method name="add_ignore_package" symbol="pacman_manager_add_ignore_package">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="package" type="gchar*"/>
				</parameters>
			</method>
			<method name="add_no_extract" symbol="pacman_manager_add_no_extract">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="filename" type="gchar*"/>
				</parameters>
			</method>
			<method name="add_no_upgrade" symbol="pacman_manager_add_no_upgrade">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="filename" type="gchar*"/>
				</parameters>
			</method>
			<method name="add_sync_first" symbol="pacman_manager_add_sync_first">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="package" type="gchar*"/>
				</parameters>
			</method>
			<method name="configure" symbol="pacman_manager_configure">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="filename" type="gchar*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="find_missing_dependencies" symbol="pacman_manager_find_missing_dependencies">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="remove" type="PacmanList*"/>
					<parameter name="install" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="find_sync_database" symbol="pacman_manager_find_sync_database">
				<return-type type="PacmanDatabase*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="name" type="gchar*"/>
				</parameters>
			</method>
			<method name="get" symbol="pacman_manager_get">
				<return-type type="PacmanManager*"/>
				<parameters>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="get_cache_paths" symbol="pacman_manager_get_cache_paths">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_clean_method" symbol="pacman_manager_get_clean_method">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_database_path" symbol="pacman_manager_get_database_path">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_hold_packages" symbol="pacman_manager_get_hold_packages">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_i_love_candy" symbol="pacman_manager_get_i_love_candy">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_ignore_groups" symbol="pacman_manager_get_ignore_groups">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_ignore_packages" symbol="pacman_manager_get_ignore_packages">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_local_database" symbol="pacman_manager_get_local_database">
				<return-type type="PacmanDatabase*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_log_file" symbol="pacman_manager_get_log_file">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_no_extracts" symbol="pacman_manager_get_no_extracts">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_no_passive_ftp" symbol="pacman_manager_get_no_passive_ftp">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_no_upgrades" symbol="pacman_manager_get_no_upgrades">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_root_path" symbol="pacman_manager_get_root_path">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_show_size" symbol="pacman_manager_get_show_size">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_sync_databases" symbol="pacman_manager_get_sync_databases">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_sync_firsts" symbol="pacman_manager_get_sync_firsts">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_total_download" symbol="pacman_manager_get_total_download">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_transaction" symbol="pacman_manager_get_transaction">
				<return-type type="PacmanTransaction*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_use_delta" symbol="pacman_manager_get_use_delta">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_use_syslog" symbol="pacman_manager_get_use_syslog">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="get_version" symbol="pacman_manager_get_version">
				<return-type type="gchar*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
				</parameters>
			</method>
			<method name="install" symbol="pacman_manager_install">
				<return-type type="PacmanTransaction*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="flags" type="guint32"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="register_local_database" symbol="pacman_manager_register_local_database">
				<return-type type="PacmanDatabase*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="register_sync_database" symbol="pacman_manager_register_sync_database">
				<return-type type="PacmanDatabase*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="name" type="gchar*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="remove" symbol="pacman_manager_remove">
				<return-type type="PacmanTransaction*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="flags" type="guint32"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="remove_cache_path" symbol="pacman_manager_remove_cache_path">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="path" type="gchar*"/>
				</parameters>
			</method>
			<method name="remove_hold_package" symbol="pacman_manager_remove_hold_package">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="package" type="gchar*"/>
				</parameters>
			</method>
			<method name="remove_ignore_group" symbol="pacman_manager_remove_ignore_group">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="group" type="gchar*"/>
				</parameters>
			</method>
			<method name="remove_ignore_package" symbol="pacman_manager_remove_ignore_package">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="package" type="gchar*"/>
				</parameters>
			</method>
			<method name="remove_no_extract" symbol="pacman_manager_remove_no_extract">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="filename" type="gchar*"/>
				</parameters>
			</method>
			<method name="remove_no_upgrade" symbol="pacman_manager_remove_no_upgrade">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="filename" type="gchar*"/>
				</parameters>
			</method>
			<method name="remove_sync_first" symbol="pacman_manager_remove_sync_first">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="package" type="gchar*"/>
				</parameters>
			</method>
			<method name="set_cache_paths" symbol="pacman_manager_set_cache_paths">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="paths" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="set_clean_method" symbol="pacman_manager_set_clean_method">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="method" type="gchar*"/>
				</parameters>
			</method>
			<method name="set_database_path" symbol="pacman_manager_set_database_path">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="path" type="gchar*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="set_hold_packages" symbol="pacman_manager_set_hold_packages">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="packages" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="set_i_love_candy" symbol="pacman_manager_set_i_love_candy">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="value" type="gboolean"/>
				</parameters>
			</method>
			<method name="set_ignore_groups" symbol="pacman_manager_set_ignore_groups">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="groups" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="set_ignore_packages" symbol="pacman_manager_set_ignore_packages">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="packages" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="set_log_file" symbol="pacman_manager_set_log_file">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="filename" type="gchar*"/>
				</parameters>
			</method>
			<method name="set_no_extracts" symbol="pacman_manager_set_no_extracts">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="filenames" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="set_no_passive_ftp" symbol="pacman_manager_set_no_passive_ftp">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="value" type="gboolean"/>
				</parameters>
			</method>
			<method name="set_no_upgrades" symbol="pacman_manager_set_no_upgrades">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="filenames" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="set_root_path" symbol="pacman_manager_set_root_path">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="path" type="gchar*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="set_show_size" symbol="pacman_manager_set_show_size">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="value" type="gboolean"/>
				</parameters>
			</method>
			<method name="set_sync_firsts" symbol="pacman_manager_set_sync_firsts">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="packages" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="set_total_download" symbol="pacman_manager_set_total_download">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="value" type="gboolean"/>
				</parameters>
			</method>
			<method name="set_transfer_closure" symbol="pacman_manager_set_transfer_closure">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="closure" type="GClosure*"/>
				</parameters>
			</method>
			<method name="set_transfer_command" symbol="pacman_manager_set_transfer_command">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="command" type="gchar*"/>
				</parameters>
			</method>
			<method name="set_transfer_handler" symbol="pacman_manager_set_transfer_handler">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="func" type="PacmanTransferFunc"/>
					<parameter name="user_data" type="gpointer"/>
					<parameter name="destroy_data" type="GClosureNotify"/>
				</parameters>
			</method>
			<method name="set_use_delta" symbol="pacman_manager_set_use_delta">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="value" type="gboolean"/>
				</parameters>
			</method>
			<method name="set_use_syslog" symbol="pacman_manager_set_use_syslog">
				<return-type type="void"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="value" type="gboolean"/>
				</parameters>
			</method>
			<method name="sync" symbol="pacman_manager_sync">
				<return-type type="PacmanTransaction*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="flags" type="guint32"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="test_dependencies" symbol="pacman_manager_test_dependencies">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="dependencies" type="PacmanList*"/>
				</parameters>
			</method>
			<method name="unregister_all_databases" symbol="pacman_manager_unregister_all_databases">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="unregister_database" symbol="pacman_manager_unregister_database">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="database" type="PacmanDatabase*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="update" symbol="pacman_manager_update">
				<return-type type="PacmanTransaction*"/>
				<parameters>
					<parameter name="manager" type="PacmanManager*"/>
					<parameter name="flags" type="guint32"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<property name="transaction" type="PacmanTransaction*" readable="1" writable="0" construct="0" construct-only="0"/>
			<property name="version" type="char*" readable="1" writable="0" construct="0" construct-only="0"/>
		</object>
		<object name="PacmanRemove" parent="PacmanTransaction" type-name="PacmanRemove" get-type="pacman_remove_get_type">
		</object>
		<object name="PacmanSync" parent="PacmanTransaction" type-name="PacmanSync" get-type="pacman_sync_get_type">
		</object>
		<object name="PacmanTransaction" parent="GObject" type-name="PacmanTransaction" get-type="pacman_transaction_get_type">
			<method name="cancel" symbol="pacman_transaction_cancel">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="commit" symbol="pacman_transaction_commit">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<method name="get_conflicts" symbol="pacman_transaction_get_conflicts">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
				</parameters>
			</method>
			<method name="get_file_conflicts" symbol="pacman_transaction_get_file_conflicts">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
				</parameters>
			</method>
			<method name="get_flags" symbol="pacman_transaction_get_flags">
				<return-type type="guint32"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
				</parameters>
			</method>
			<method name="get_invalid_files" symbol="pacman_transaction_get_invalid_files">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
				</parameters>
			</method>
			<method name="get_marked_packages" symbol="pacman_transaction_get_marked_packages">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
				</parameters>
			</method>
			<method name="get_missing_dependencies" symbol="pacman_transaction_get_missing_dependencies">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
				</parameters>
			</method>
			<method name="get_packages" symbol="pacman_transaction_get_packages">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
				</parameters>
			</method>
			<method name="prepare" symbol="pacman_transaction_prepare">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
					<parameter name="targets" type="PacmanList*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</method>
			<signal name="download" when="LAST">
				<return-type type="void"/>
				<parameters>
					<parameter name="object" type="PacmanTransaction*"/>
					<parameter name="p0" type="char*"/>
					<parameter name="p1" type="guint"/>
					<parameter name="p2" type="guint"/>
				</parameters>
			</signal>
			<signal name="progress" when="LAST">
				<return-type type="void"/>
				<parameters>
					<parameter name="object" type="PacmanTransaction*"/>
					<parameter name="p0" type="PacmanTransactionProgress"/>
					<parameter name="p1" type="char*"/>
					<parameter name="p2" type="guint"/>
					<parameter name="p3" type="guint"/>
					<parameter name="p4" type="guint"/>
				</parameters>
			</signal>
			<signal name="question" when="LAST">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="object" type="PacmanTransaction*"/>
					<parameter name="p0" type="PacmanTransactionQuestion"/>
					<parameter name="p1" type="char*"/>
				</parameters>
			</signal>
			<signal name="status" when="LAST">
				<return-type type="void"/>
				<parameters>
					<parameter name="object" type="PacmanTransaction*"/>
					<parameter name="p0" type="PacmanTransactionStatus"/>
					<parameter name="p1" type="char*"/>
				</parameters>
			</signal>
			<vfunc name="commit">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</vfunc>
			<vfunc name="prepare">
				<return-type type="gboolean"/>
				<parameters>
					<parameter name="transaction" type="PacmanTransaction*"/>
					<parameter name="targets" type="PacmanList*"/>
					<parameter name="error" type="GError**"/>
				</parameters>
			</vfunc>
		</object>
		<object name="PacmanUpdate" parent="PacmanTransaction" type-name="PacmanUpdate" get-type="pacman_update_get_type">
			<method name="get_databases" symbol="pacman_update_get_databases">
				<return-type type="PacmanList*"/>
				<parameters>
					<parameter name="update" type="PacmanUpdate*"/>
				</parameters>
			</method>
		</object>
	</namespace>
</api>
