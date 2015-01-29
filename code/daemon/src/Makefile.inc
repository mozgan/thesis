#
# $Id: src/Makefile,v1.0 13.11.2011 14.15 mozgan Exp $
#

# === compiler and flags ======================================================
CC	=	gcc
CFLAGS	=	-ansi -pedantic -Wall -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -g #-D_POSIX_C_SOURCE
LDFLAGS	=	-lm
DEPFILE	=	.depend

# === prefix to install =======================================================
PREFIX		=	/usr/local
EXEC_PREFIX	=	$(PREFIX)
BINDIR		=	$(EXEC_PREFIX)/bin

# === source(s), object(s) and executable =====================================
SRCS	=	main.c udp.c error.c
OBJS	=	$(SRCS:.c=.o)
PRJNAME	=	daemon

# === make the executable (the default goal) ==================================
all: $(PRJNAME)

$(PRJNAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# === make object(s) ==========================================================
%o: %.c %.h
	$(CC) $(CFLAGS) -c $<

# === check the executable file to execute ====================================
check: all
	./$(PRJNAME) -h 127.0.0.1 -p 1200
	@echo "*** ALL TESTS PASSED ***"

# === install =================================================================
install:
	@echo	$(BINDIR)
	install -d $(DESTDIR)$(BINDIR)
	install -m 0755 $(PRJNAME) $(DESTDIR)$(BINDIR)

# === uninstall ===============================================================
uninstall:
	-rm -f $(DESTDIR)$(BINDIR)/$(PRJNAME)

# === depend ==================================================================
depend: $(SRCS)
	$(CC) -E -MM $(SRCS) > $(DEPFILE)

# === clean the executable file(s) and object(s) ==============================
clean:
	-rm -f $(PRJNAME) $(OBJS) $(DEPFILE) *~ 
	-rm -rf ../doc

# === PHONY ===================================================================
.PHONY: all clean check install uninstall depend



