AC_INIT([GPacman], [3.3.0])
AC_CONFIG_SRCDIR([lib/gpacman.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.11 dist-bzip2])
AM_MAINTAINER_MODE

AC_PROG_CC
AM_PROG_CC_C_O
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

AC_SUBST([CFLAGS])
AC_SUBST([CPPFLAGS])
AC_SUBST([LDFLAGS])

AH_TEMPLATE([GETTEXT_PACKAGE], [Package name for gettext])
GETTEXT_PACKAGE="$PACKAGE_TARNAME"
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], "$GETTEXT_PACKAGE")
AC_SUBST([GETTEXT_PACKAGE])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])

LIB_VERSION_INFO="0.0.0"
AC_SUBST([LIB_VERSION_INFO])

# Earlier versions probably work, but I'm not sure
GLIB_REQUIRED=[2.22.0]
ALPM_REQUIRED=[4.0.0]
GTKDOC_REQUIRED=[1.13]

AM_PATH_GLIB_2_0([$GLIB_REQUIRED], [], [AC_MSG_ERROR([Unable to find glib on your system, please make sure glib2 is installed and up-to-date.])], gobject gio)
AC_SUBST([GLIB_CFLAGS])
AC_SUBST([GLIB_LIBS])

AC_CHECK_HEADERS([alpm.h alpm_list.h], [ALPM_CFLAGS=[-I$includedir] ALPM_LIBS=[-lalpm]], [AC_MSG_ERROR([Unable to find alpm on your system, please make sure pacman is installed.])])
AC_SUBST([ALPM_CFLAGS])
AC_SUBST([ALPM_LIBS])

# TODO: add no-tmpl option when gtk-doc 1.14 is released
GTK_DOC_CHECK([$GTKDOC_REQUIRED])

AC_ARG_WITH(root-path, AS_HELP_STRING([--with-root-path=path], [set the default location of the operating root directory]), [PACMAN_ROOT_PATH=[$withval]], [PACMAN_ROOT_PATH=[/]])
AC_SUBST([PACMAN_ROOT_PATH])

AC_ARG_WITH(database-path, AS_HELP_STRING([--with-database-path=path], [set the default location of the database directory]), [PACMAN_DATABASE_PATH=[$withval]], [PACMAN_DATABASE_PATH=[$localstatedir/lib/pacman/]])
AC_SUBST([PACMAN_DATABASE_PATH])

AC_ARG_WITH(cache-path, AS_HELP_STRING([--with-cache-path=path], [set the default location of the cache directory]), [PACMAN_CACHE_PATH=[$withval]], [PACMAN_CACHE_PATH=[$localstatedir/cache/pacman/pkg/]])
AC_SUBST([PACMAN_CACHE_PATH])

AC_ARG_WITH(config-file, AS_HELP_STRING([--with-config-file=path], [set the default location of the pacman config file]), [PACMAN_CONFIG_FILE=[$withval]], [PACMAN_CONFIG_FILE=[$sysconfdir/pacman.conf]])
AC_SUBST([PACMAN_CONFIG_FILE])

AC_ARG_WITH(log-file, AS_HELP_STRING([--with-log-file=path], [set the default location of the log file]), [PACMAN_LOG_FILE=[$withval]], [PACMAN_LOG_FILE=[$localstatedir/log/pacman.log]])
AC_SUBST([PACMAN_LOG_FILE])

AC_CONFIG_FILES([Makefile $PACKAGE_TARNAME.pc docs/$PACKAGE_TARNAME-docs.sgml lib/Makefile po/Makefile.in docs/Makefile])
AC_OUTPUT
