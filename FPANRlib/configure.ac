#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#LT_INIT

AC_PREREQ([2.69])
AC_INIT([fpanrlib], [0.2.0], [christophe.pont@univ-perp.fr])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/libfpanr.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AM_PROG_AR

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [sqrt])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.


# Checks for library functions.
AC_CHECK_FUNCS([sqrt])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
                 
                 LT_INIT
AC_SUBST([LIBTOOL_DEPS])

AC_OUTPUT
