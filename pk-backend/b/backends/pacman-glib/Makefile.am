plugindir = $(PK_PLUGIN_DIR)
plugin_LTLIBRARIES = libpk_backend_pacman_glib.la
libpk_backend_pacman_glib_la_SOURCES = pk-backend-pacman-glib.c
libpk_backend_pacman_glib_la_LIBADD = $(PK_PLUGIN_LIBS) $(PACMAN_LIBS)
libpk_backend_pacman_glib_la_LDFLAGS = -module -avoid-version
libpk_backend_pacman_glib_la_CFLAGS = $(PK_PLUGIN_CFLAGS) $(PACMAN_CFLAGS) $(WARNINGFLAGS_C)
