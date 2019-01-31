ACLOCAL_AMFLAGS=-I m4
# subdirectories to build
SUBDIRS=src/
#dist_bin_SCRIPTS=fpanr

#edit_script = $(SED) -e 's,%LIBDIR%,$(libdir),'g $(NULL)

#fpanr: fpanr.in Makefile
#	$(AM_V_GEN)rm -f $@ $@.tmp && \
#	$(edit_script) $< >$@.tmp && \
#	chmod a-w $@.tmp && \
#	mv $@.tmp $@

#CLEANFILES = fpanr

check:
	@echo "Tests should be run after install with make installcheck"

installcheck-local:
	$(MAKE) -C tests/ check

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool
