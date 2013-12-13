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
SRCS = list.c queue.c stack.c vector.c matrix.o sparse-matrix.c \
	priority-queue.c set.c hashtable.c binary-tree.c binary-search-tree.c \
	heap.c n-way-search-tree.c
OBJS = list.o queue.o stack.o vector.o matrix.o sparse-matrix.o \
	priority-queue.o set.o hashtable.o binary-tree.o binary-search-tree.o \
	heap.o n-way-search-tree.o
HEADS = *.h
INCL_DIR = -Iinclude

all: libdstructs

libdstructs: $(OBJS)
	

list.o: include/list.h
	$(CC) $(CFLAGS) $(INCL_DIR) -o obj/$@ src/list.c

queue.o: include/queue.h include/list.h
	$(CC) $(CFLAGS) $(INCL_DIR) -o obj/$@ src/queue.c

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


style:
	astyle -r -s3 -a -S --indent-preprocessor --convert-tabs "src/*.c" \
	"include/*.h"

clean:
	rm -f obj/$(OBJS) lib/*.a lib/*.so

dist: clean style
	tar -cvzf libdstructs.tar ../libdstructs --exclude-backups --exclude-vcs \
		--exclude='libdstructs.tar'

