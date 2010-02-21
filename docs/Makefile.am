AUTOMAKE_OPTIONS = 1.6

DOC_MODULE = $(PACKAGE_TARNAME)
DOC_MODULE_VERSION = $(PACKAGE_VERSION)
DOC_MAIN_SGML_FILE = $(DOC_MODULE)-docs.sgml
DOC_SOURCE_DIR = $(top_srcdir)/lib

SCANGOBJ_OPTIONS = 
SCAN_OPTIONS = --rebuild-types
MKDB_OPTIONS = --sgml-mode --output-format=xml --name-space=pacman
MKTMPL_OPTIONS = 
MKHTML_OPTIONS = 
FIXXREF_OPTIONS = --extra-dir=$(prefix)/share/gtk-doc/html/glib --extra-dir=$(prefix)/share/gtk-doc/html/gobject

HFILE_GLOB = $(top_srcdir)/lib/*.h
CFILE_GLOB = $(top_srcdir)/lib/*.c
EXTRA_HFILES = 
IGNORE_HFILES = 

HTML_IMAGES = 
content_files = 
expand_content_files = 

GTKDOC_CFLAGS = $(GLIB_CFLAGS)
GTKDOC_LIBS = $(GLIB_LIBS) $(top_builddir)/lib/lib$(API_NAME).la

include $(top_srcdir)/gtk-doc.make

# TODO: remove overrides.txt when gtk-doc 1.14 comes out
DISTCLEANFILES = $(DOC_MODULE).types $(DOC_MODULE)-docs.sgml Makefile.in -rf tmpl
