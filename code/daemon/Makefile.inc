#===============================================================================
#
#         File: Makefile
#
#        Usage: make		(generate executable(s)				)
#		make help	(print this help message			)
#               make clean	(remove objects, executables, prerequisits	)
#		make doxy	(generate doxygen documentation			)
#		make dist	(generate a distribution			)
#		make distcheck	(check the distribution				)
#		make distclean	(remove all generated file(s)			)
#
#
#       Author: M. Ozgan, <mozgan@mozgan.org>
#      Created: 13.11.2011 14:15
#      Company:	TU Wien
#
# $Id: Makefile,v 1.0 13.11.2011 14.15 mozgan Exp $
#
#===============================================================================


# === package ==================================================================
PACKAGE	=	udp
VERSION	=	1.0

# === tarball ==================================================================
TARNAME	=	$(PACKAGE)
DISTDIR	=	$(TARNAME)-$(VERSION)


# === source directory =========================================================
SRCDIR	=	./src

# === doxygen ==================================================================
DOX	=	doxygen
DOXFILE	=	doxy.file

# === make the executable (the default goal) ===================================
all clean check depend install uninstall:
	cd $(SRCDIR) && $(MAKE) $@

# === make doxygen documentation ===============================================
doxy:
	$(DOX) $(DOXFILE)

# === make a distrubition ======================================================
dist:	$(DISTDIR).tar.gz

$(DISTDIR).tar.gz: $(DISTDIR)
	tar chof - $(DISTDIR) | gzip -9 -c > $@
	-rm -rf $(DISTDIR)

$(DISTDIR): FORCE
	mkdir -p $(DISTDIR)
	cp BSDmakefile GNUmakefile $(DISTDIR)
	cp Makefile.inc $(DISTDIR)
	cp LICENSE $(DISTDIR)
	cp $(DOXFILE) $(DISTDIR)
	cp -ir $(SRCDIR) $(DISTDIR)

FORCE:
	-rm -f $(DISTDIR).tar.gz > /dev/null 2>&1
	-rm -rf $(DISTDIR) > /dev/null 2>&1
	cd $(SRCDIR) && $(MAKE) clean

# === check the distribution ===================================================
distcheck: $(DISTDIR).tar.gz
	gzip -cd $(DISTDIR).tar.gz | tar xvf -
	cd $(DISTDIR) && $(MAKE) all
	cd $(DISTDIR) && $(MAKE) check
	cd $(DISTDIR) && $(MAKE) DESTDIR=$${PWD}/_inst install
	cd $(DISTDIR) && $(MAKE) DESTDIR=$${PWD}/_inst uninstall
	@remaining="`find $${PWD}/$(DISTDIR)/_inst -type f | wc -l`"; \
	if test "$${remaining}" -ne 0; then \
		@echo "*** $${remaining} file(s) remaining in stage directory!";\
		exit 1;\
	fi
	cd $(DISTDIR) && $(MAKE) clean
	-rm -rf $(DISTDIR)
	@echo "*** Package $(DISTDIR).tar.gz is ready for distribution ***"

# === help =====================================================================
help:
	@echo	"Usage:	make [option]"
	@echo	" "
	@echo	"Options:"
	@echo	"	help	    print this help message			"
	@echo	"	make	    generate the executable			"
	@echo	"	clean	    remove executable, object(s), and doc	"
	@echo	"	doxy	    generate doxygen documentation		"
	@echo	"	install	    install the executable			"
	@echo	"	uninstall   uninstall the executable from PREFIX	"
	@echo	"	dist	    generate a distribution			"
	@echo	"	distcheck   check the distribution			"
	@echo	"	distclean   remove the dist, doc, exec, and object(s)	"
	@echo	" "
	@echo	"Defaults:   PREFIX=/usr/local	    "
	@echo	"	    BIN=/usr/local/bin	    "
	@echo	" "
	@echo	"To install in other directory:	    "
	@echo	"   make prefix=/path/to/install install	"

# === clean distribution, also all executable(s), object file(s) and tarball ==
distclean: FORCE

# === PHONY ====================================================================
.PHONY: FORCE all clean check dist distcheck doxy install uninstall distclean depend



