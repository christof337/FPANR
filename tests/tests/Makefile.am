## Process this file with automake to produce Makefile.in

TESTS = check_fpanr
check_PROGRAMS = check_fpanr
check_fpanr_SOURCES = check_fpanr.c $(top_builddir)/src/FPANRlib.h
check_fpanr_CFLAGS = @CHECK_CFLAGS@
check_fpanr_LDADD = $(top_builddir)/src/libfpanr.la @CHECK_LIBS@
