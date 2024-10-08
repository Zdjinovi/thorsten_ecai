## Process this file with automake to create Makefile.in.

## Makefile for Bison testsuite.
## Copyright (C) 2000, 2001, 2002 Free Software Foundation, Inc.

## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.

## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
## 02111-1307, USA.

EXTRA_DIST = $(TESTSUITE_AT) testsuite package.m4

DISTCLEANFILES       = atconfig $(check_SCRIPTS)
MAINTAINERCLEANFILES = Makefile.in $(TESTSUITE)

## ------------ ##
## package.m4.  ##
## ------------ ##

$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	{					\
	  echo '# Signature of the current package.'; \
	  echo 'm4_define([AT_PACKAGE_NAME],      [@PACKAGE_NAME@])'; \
	  echo 'm4_define([AT_PACKAGE_TARNAME],   [@PACKAGE_TARNAME@])'; \
	  echo 'm4_define([AT_PACKAGE_VERSION],   [@PACKAGE_VERSION@])'; \
	  echo 'm4_define([AT_PACKAGE_STRING],    [@PACKAGE_STRING@])'; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [@PACKAGE_BUGREPORT@])'; \
	} >$(srcdir)/package.m4

## ------------ ##
## Test suite.  ##
## ------------ ##

TESTSUITE_AT = \
	testsuite.at \
	input.at \
	output.at sets.at reduce.at \
	synclines.at headers.at actions.at conflicts.at \
	calc.at \
        torture.at existing.at regression.at \
	cxx-type.at glr-regr1.at

TESTSUITE = $(srcdir)/testsuite

AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): package.m4 $(TESTSUITE_AT)
	$(AUTOTEST) -I $(srcdir) testsuite.at -o $@.tmp
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && ./config.status tests/$@

clean-local:
	$(SHELL) $(TESTSUITE) --clean

check-local: atconfig atlocal $(TESTSUITE)
	$(SHELL) $(TESTSUITE)

check_SCRIPTS = bison

# Run the test suite on the *installed* tree.
installcheck-local:
	$(SHELL) $(TESTSUITE) AUTOTEST_PATH=$(exec_prefix)/bin

# Be real mean with it.
.PHONY: maintainer-check-g++
maintainer-check-g++: $(TESTSUITE)
	if test -n "$(VALGRIND)"; then		\
	   $(TESTSUITE) CC='$(GXX)';		\
	else					\
	  true;					\
	fi

.PHONY: maintainer-check-posix
maintainer-check-posix: $(TESTSUITE)
	$(TESTSUITE) POSIXLY_CORRECT=1

.PHONY: maintainer-check-valgrind
maintainer-check-valgrind: $(TESTSUITE)
	if test -n "$(VALGRIND)"; then					    \
	   $(TESTSUITE) PREBISON='$(VALGRIND) -q' PREPARSER='$(VALGRIND) -q'; \
	else								    \
	  true;								    \
	fi

.PHONY: maintainer-check
maintainer-check: maintainer-check-posix maintainer-check-valgrind maintainer-check-g++
