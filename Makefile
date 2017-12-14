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
.phony: all pre-build test run style clean install uninstall dist

SHELL = bash
CC = gcc
CFLAGS = -ansi -Wall -O2 -c -fpic
TEST_FLAGS = -ansi -Wall -O2

INCL_PATH = -Iinclude

INCL_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
TEST_DIR = ./test

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADS = dstruct.h
LIBNAME = libdstruct

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.c=$(TEST_DIR)/%.o)
TEST_PROG = dstruct-tests


all: $(LIBNAME)

$(LIBNAME): pre-build $(OBJS)
	gcc -shared $(INCL_PATH) $(OBJS) -o $(LIBNAME).so
	ar -crs $(LIBNAME).a $(OBJS)

pre-build:
	mkdir -p $(OBJ_DIR)

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCL_PATH) $< -o $@

test: $(LIBNAME) $(TEST_OBJS)
	@#! List tests
	$(CC) $(TEST_FLAGS) $(INCL_PATH) -o $(TEST_PROG) $(TEST_OBJS) -L. -ldstruct

$(TEST_OBJS): $(TEST_DIR)/%.o : $(TEST_DIR)/%.c
	$(CC) $(TEST_FLAGS) $(INCL_PATH) -c $< -o $@

#! Run tests
run: test
	LD_LIBRARY_PATH=. $(TEST_PROG)

style:
	astyle -r -s3 -a -S --indent-preprocessor --convert-tabs \
	"$(SRCS)" "$(INCL_DIR)/$(HEADS)"

install: $(LIBNAME)
	mkdir -p /usr/local/include/dstruct
	cp $(INCL_DIR)/$(HEADS) /usr/local/include/dstruct

	mkdir -p /usr/local/lib
	cp $(LIBNAME).so /usr/local/lib
	cp $(LIBNAME).a  /usr/local/lib

	ldconfig

uninstall:
	rm -f /usr/local/include/dstruct/$(HEADS)
	rmdir /usr/local/include/dstruct
	rm -f /usr/local/lib/$(LIBNAME).so
	rm -f /usr/local/lib/$(LIBNAME).a

	ldconfig

clean:
	rm -f $(OBJ_DIR)/*.o
	rmdir $(OBJ_DIR)
	rm -f $(LIBNAME).so $(LIBNAME).a
	rm -f $(TEST_OBJS)
	rm -f $(TEST_PROG)

dist: clean style
	tar -cvzf $(LIBNAME).tar ../$(LIBNAME) --exclude-backups --exclude-vcs \
		--exclude='$(LIBNAME).tar'

