# Process this file with autoconf to produce a configure script.

# Prelude.
AC_PREREQ([2.59])
#AC_INIT([Money], [0.3], [check-devel AT lists.sourceforge.net])
AC_INIT([FPANRtests],[0.2])
AM_PROG_AR

# unique source file --- primitive safety check 
# AC_CONFIG_SRCDIR([src/FPANRlib.c])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_MACRO_DIRS([m4])

# fairly severe build strictness
# change foreign to gnu or gnits to comply with gnu standards
AM_INIT_AUTOMAKE
#AM_INIT_AUTOMAKE([-Wall -Werror gnu 1.11.2])

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_CXX
#AC_PROG_RANLIB

LT_INIT

# Checks for libraries.

PKG_CHECK_MODULES([CHECK], [check >= 0.9.6])
AC_SEARCH_LIBS([sqrt], [m])
AM_PROG_CC_C_O

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS#([stdlib.h])
AC_CHECK_FUNCS([floor])
AC_CHECK_FUNCS([modf])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

# Output files
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])

AC_OUTPUT
