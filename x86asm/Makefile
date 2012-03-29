# $Id: Makefile,v 1.3 2008/07/11 18:38:13 dvermeir Exp $
%:	%.s
	as --32 $@.s -o $@.o >$@.txt && ld -m elf_i386 $@.o -o $@
