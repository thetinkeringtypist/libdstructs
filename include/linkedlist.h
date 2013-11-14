/**
 * libdstructs: a simple, generic data structures library written in ANSI C.
 *
 * Copyright (C) 2013 Evan Bezeredi <bezeredi.dev@gmail.com>
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
#ifndef __LIBDSTRUCTS_LINKEDLIST_H__
#define __LIBDSTRUCTS_LINKEDLIST_H__	/* Guard against multiple inclusion */


/**
 * Linkedlist public, opaque data type. Contents only accessable through
 * function calls.
 **/
typedef struct __llist_s llist_t;


/**
 * Linkedlist iterator public, opaque data type. Contents only accessable
 * through function calls.
 **/
typedef struct __ll_iter_s ll_itr_t;


/**
 * Wrapper macro for __ll_init(size_t __alloc_size).
 **/
#define ll_init(type) __ll_init(sizeof(type))


/** FUNCTION PROTOTYPES **/

/**
 * NOTE: __ll_init(...) is not intended for use by the user. Use the wrapper
 * macro ll_init(...) instead.
 **/
extern	llist_t*				__ll_init	(size_t __element_size);
extern	void					ll_free		(llist_t* const list);

extern	int	ll_size		(llist_t* const list);

extern	int	ll_add		(llist_t* const list, int index,
										void* const element);
extern	void	ll_addfirst	(llist_t* const list, void* const element);
extern	void	ll_addlast	(llist_t* const list, void* const element);

extern	void	ll_clear		(llist_t* const list);
extern	int	ll_contains	(llist_t* const list, void* const element);

extern	void*	ll_get		(llist_t* const list, int index);
extern	void*	ll_first		(llist_t* const list);
extern	void*	ll_last		(llist_t* const list);

extern	int	ll_indexof	(llist_t* const list, void* const element);

extern	void*	ll_remove	(llist_t* const list, int index);
extern	void*	ll_set		(llist_t* const list, int index,
										 void* const element);

/* Linkedlist Iterator Functions */
extern	ll_itr_t*	ll_itr		(llist_t* const list, int index);
extern	void			li_free		(ll_itr_t* const iterator);

extern	int			li_hasnext	(ll_itr_t* const iterator);
extern	int			li_has_prev	(ll_itr_t* const iterator);
extern	void*			li_next		(ll_itr_t* const iterator);
extern	void*			li_prev		(ll_itr_t* const iterator);

#endif	/* __LIBDSTRUCTS_LINKEDLIST_H__ */

