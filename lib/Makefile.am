DEFS = -DPACMAN_COMPILATION -DG_LOG_DOMAIN=\"Pacman\" -DPACMAN_ROOT_PATH=\"$(PACMAN_ROOT_PATH)\" -DPACMAN_DATABASE_PATH=\"$(PACMAN_DATABASE_PATH)\" -DPACMAN_CACHE_PATH=\"$(PACMAN_CACHE_PATH)\" -DPACMAN_CONFIG_FILE=\"$(PACMAN_CONFIG_FILE)\" -DPACMAN_LOG_FILE=\"$(PACMAN_LOG_FILE)\"

libheaderincludedir = $(includedir)/$(API_NAME)
libheaderinclude_HEADERS = pacman.h

libgpacmanincludedir = $(libheaderincludedir)/$(PACKAGE_TARNAME)
libgpacmaninclude_HEADERS = pacman-conflict.h pacman-database.h pacman-delta.h pacman-dependency.h pacman-error.h pacman-file-conflict.h pacman-group.h pacman-install.h pacman-list.h pacman-manager.h pacman-missing-dependency.h pacman-package.h pacman-remove.h pacman-sync.h pacman-transaction.h pacman-types.h pacman-update.h

lib_LTLIBRARIES = libgpacman-@API_VERSION@.la
libgpacman_@API_VERSION@_la_SOURCES = pacman-config.c pacman-conflict.c pacman-database.c pacman-delta.c pacman-dependency.c pacman-enum.c pacman-error.c pacman-file-conflict.c pacman-group.c pacman-install.c pacman-list.c pacman-manager.c pacman-marshal.c pacman-missing-dependency.c pacman-package.c pacman-remove.c pacman-sync.c pacman-transaction.c pacman-update.c
libgpacman_@API_VERSION@_la_CFLAGS = $(GLIB_CFLAGS) $(PACMAN_CFLAGS) -include $(CONFIG_HEADER)
libgpacman_@API_VERSION@_la_LIBADD = $(GLIB_LIBS) $(PACMAN_LIBS)

pacman-enum.c: pacman-enum.c.template pacman-dependency.h pacman-error.h pacman-transaction.h
	$(GLIB_MKENUMS) --template $^ > $@.tmp && \
	( cmp -s $@.tmp $@ && rm -f $@.tmp || mv -f $@.tmp $@ )

pacman-marshal.c: pacman-marshal.list
	$(GLIB_GENMARSHAL) --body $< > $@.tmp && \
	( cmp -s $@.tmp $@ && rm -f $@.tmp || mv -f $@.tmp $@ )

BUILT_SOURCES = pacman-enum.c pacman-marshal.c

CLEANFILES = $(BUILT_SOURCES)
DISTCLEANFILES = Makefile.in
