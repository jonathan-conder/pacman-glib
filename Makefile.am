ACLOCAL_AMFLAGS = -I m4

SUBDIRS = lib po docs

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(PACKAGE_TARNAME).pc

DISTCLEANFILES = $(PACKAGE_TARNAME).pc Makefile.in intltool-extract intltool-merge intltool-update po/.intltool-merge-cache
MAINTAINERCLEANFILES = aclocal.m4 compile config.guess config.h.in config.sub configure depcomp gtk-doc.make install-sh intltool-extract.in intltool-merge.in intltool-update.in ltmain.sh missing mkinstalldirs -rf m4
