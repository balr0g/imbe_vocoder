dnl 
dnl  Copyright 2004,2005 Free Software Foundation, Inc.
dnl  
dnl  This file is part of GNU Radio
dnl  
dnl  GNU Radio is free software; you can redistribute it and/or modify
dnl  it under the terms of the GNU General Public License as published by
dnl  the Free Software Foundation; either version 2, or (at your option)
dnl  any later version.
dnl  
dnl  GNU Radio is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl  GNU General Public License for more details.
dnl  
dnl  You should have received a copy of the GNU General Public License
dnl  along with GNU Radio; see the file COPYING.  If not, write to
dnl  the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
dnl  Boston, MA 02111-1307, USA.
dnl 

AC_INIT
AC_PREREQ(2.57)
AM_CONFIG_HEADER(config.h)
AC_CANONICAL_TARGET([])
AM_INIT_AUTOMAKE(imbe_vocoder,0.1)

dnl LF_CONFIGURE_CC
LF_CONFIGURE_CXX
LF_SET_WARNINGS
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL

AC_ENABLE_SHARED	dnl do build shared libraries
LT_INIT	dnl use libtool for shared libraries

if test "x$CXX_FOR_BUILD" = x
then
  CXX_FOR_BUILD=${CXX}
fi
AC_SUBST(CXX_FOR_BUILD)

dnl Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS(fcntl.h limits.h strings.h sys/ioctl.h sys/time.h unistd.h)
AC_CHECK_HEADERS(sys/mman.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_HEADER_TIME

dnl Checks for library functions.
AC_CHECK_FUNCS([])

AC_CONFIG_FILES([\
	  Makefile \
	  src/Makefile \
	  src/lib/Makefile \
	])

AC_OUTPUT
