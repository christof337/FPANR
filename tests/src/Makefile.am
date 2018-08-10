## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libfpanr.la
libfpanr_la_SOURCES = FPANRlib.c FPANRlib.h fp2bin.c fp2bin.h

bin_PROGRAMS = main
main_SOURCES = FPANR.c
main_LDADD = libfpanr.la
