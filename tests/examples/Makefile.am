## Process this file with automake to produce Makefile.in

#bin_PROGRAMS = example_newton
#example_newton_SOURCES = newton.c newtonFPANR.c $(top_builddir)/src/FPANRlib.h
#example_newton_CFLAGS = @CHECK_CFLAGS@
#example_newton_LDADD = $(top_builddir)/src/libfpanr.la @CHECK_LIBS@

# libexamples_la_SOURCES = newton.c newtonFPANR.c $(top_builddir)/src/FPANRlib.h $(top_builddir)/src/FPANRlib.c

#bin_PROGRAMS = main
#main_SOURCES = newtonFPANR.c
# main_LDADD = libexamples.la

bin_PROGRAMS = example_newton_FPANR 
# example_newton 
#example_newton_SOURCES = newton.c $(top_builddir)/src/FPANRlib.h
#example_newton_LDADD = $(top_builddir)/src/libfpanr.la
example_newton_FPANR_SOURCES = newtonFPANR.c $(top_builddir)/src/FPANRlib.h
example_newton_FPANR_LDADD = $(top_builddir)/src/libfpanr.la