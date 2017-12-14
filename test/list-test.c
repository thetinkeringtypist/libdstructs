/**
 * libdstructs: a simple, generic data structures library written in ANSI C.
 *
 * Copyright (C) 2013, 2014 Evan Bezeredi <bezeredi.dev@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see {http://www.gnu.org/licenses/}.
 **/
#include "ctest.h"
#include "dstruct.h"

CTEST_DATA(intlist){
	llist_t *l;
};

CTEST_SETUP(intlist){
	data->l= ll_init(int);
	int number = 1;
	int n = 2;
	int m = 3;

	ll_add(data->l, 1, &number);
	ll_add(data->l, 2, &n);
	ll_add(data->l, 3, &m);
}

CTEST_TEARDOWN(intlist){
	ll_free(data->l);
}

CTEST2(intlist, length_test){
	ASSERT_EQUAL(3, ll_size(data->l));
}

