# libtool dynamic shared library
lib_LTLIBRARIES = libfpanrio.la
libfpanrio_la_SOURCES = libfpanrio.c 
# EXTRA_DIST = libfpanrio.h
libfpanrio_la_LDFLAGS = -lm
#libfpanrio_la_LIBADD = ../common/libtinymt64.la
library_includedir =$(includedir)/
library_include_HEADERS = libfpanrio.h   

# fp2bin library
noinst_LIBRARIES = libfp2bin.a
libfp2bin_a_SOURCES = fp2bin.c fp2bin.h
#libfp2bin_a_LDFLAGS = -lm

ACLOCAL_AMFLAGS = -I m4