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
#ifndef __LIBDSTRUCTS_TREE_H__
#define __LIBDSTRUCTS_TREE_H__   /* Guard against multiple inclusion */


/**
 * Binary search tree public, opaque data type. Contents only accessable
 * through function calls.
 **/
typedef struct __bst_s bst_t;


/* Wrapper macro for __bst_init(size_t __alloc_size) */
#define bst_init(type) (__bst_init(sizeof(type)))

/* Semantic macro for determining if a binary search tree is empty */
#define bst_empty(B) (!bst_root(B))


/** FUNCTION PROTOTYPES **/

/**
 * NOTE: __bst_init(...) is not intended for use by the user. Use the wrapper
 * macro bst_init(...) instead.
 **/
extern   bst_t*	__bst_init	(size_t __elem_size);
extern   void		bst_free		(bst_t* const tree);

extern	void*		bst_root		(bst_t* const tree);

extern	int		bst_height	(bst_t* const tree);
extern	int		bst_size		(bst_t* const tree);

extern   int		bst_contains(bst_t* const tree, void* const elem);
extern	bst_t*	bst_tree		(bst_t* const tree, void* const elem);

extern   void*		bst_getl  	(bst_t* const tree);
extern	void*		bst_getr		(bst_t* const tree);
extern	bst_t*	bst_left		(bst_t* const tree);
extern	bst_t*	bst_right	(bst_t* const tree);

extern   int		bst_add   	(bst_t* const tree, void* const elem);
extern   void*		bst_rem   	(bst_t* const tree, void* const elem);

extern   void		bst_apply 	(bst_t* const tree, void (*funct)(void* const));

extern   void**   bst_toarr 	(bst_t* const tree);

#endif   /* __LIBDSTRUCTS_TREE_H__ */

