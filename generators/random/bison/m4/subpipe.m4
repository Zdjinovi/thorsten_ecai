# -*- Autoconf -*-
# Checks required to run `subpipe'.
#
# Copyright (C) 2002 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
# 02111-1307  USA

# Written by Paul Eggert <eggert@twinsun.com>.

AC_DEFUN([BISON_PREREQ_SUBPIPE],
[
 AC_TYPE_PID_T
 AC_CHECK_HEADERS([fcntl.h sys/wait.h])
 AC_HEADER_SYS_WAIT
 AC_CHECK_FUNCS(dup2 waitpid)
 AC_FUNC_FORK
])
