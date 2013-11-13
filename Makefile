#  libdstructs: a simple, generic data structures library written in ANSI C.
#
#  Copyright (C) 2013 Evan Bezeredi <bezeredi.dev@gmail.com>
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see {http://www.gnu.org/licenses/}.
#
#!
#  Makefile for libdstructs.
#

CC = gcc
CFLAGS = -ansi -Wall -m32 -c
OBJS = linkedlist.o queue.o stack.o vector.o matrix.o sparse-matrix.o \
	priority-queue.o set.o hashtable.o binary-tree.o binary-search-tree.o \
	heap.o n-way-search-tree.o
INCL_DIR = -Iinclude

all: libdstructs

libdstructs: $(OBJS)
	

linkedlist.o: include/linkedlist.h
	$(CC) $(CFLAGS) $(INCL_DIR) -o obj/$@ src/linkedlist.c

queue.o:

stack.o:

vector.o:

matrix.o:

sparse-matrix.o:

priority-queue.o:

set.o:

hashtable.o:

binary-tree.o:

binary-search-tree.o:

heap.o:

n-way-search-tree.o:


clean:
	rm -f obj/$(OBJS) lib/*.a lib/*.so

dist: clean
	tar -cvzf libdstructs.tar ../libdstructs --exclude-backups --exclude-vcs \
		--exclude='libdstructs.tar'

