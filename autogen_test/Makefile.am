SUBDIRS=src
.PHONY:auto_clean
auto_clean:distclean
	find . -name Makefile.in -exec rm -f {} \;
	rm -rf autom4te.cache
	rm -f missing aclocal.m4 config.h.in config.guess config.sub ltmain.sh
