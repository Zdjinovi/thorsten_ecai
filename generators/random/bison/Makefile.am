## Process this file with automake to produce Makefile.in -*-Makefile-*-
## Copyright (C) 2001, 2002 Free Software Foundation, Inc.

## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.

## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
## 02111-1307  USA

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = config po lib data src doc m4 tests

EXTRA_DIST = REFERENCES OChangeLog Makefile.maint GNUmakefile

.PHONY: maintainer-check
maintainer-check:
	cd tests && $(MAKE) $(AM_MAKEFLAGS) $@

## ---------------------------- ##
## Customizing Makefile.maint.  ##
## ---------------------------- ##

move_if_change = $(srcdir)/config/move-if-change
prev_version_file = $(srcdir)/config/prev-version.txt
release_archive_dir = releases

# Uploading betas.
url_dir_list = \
  ftp://alpha.gnu.org/gnu/bison

# Files to update automatically.
wget_files = $(srcdir)/config/config.guess $(srcdir)/config/config.sub \
	     $(srcdir)/config/texinfo.tex

cvs_files = $(srcdir)/config/missing
