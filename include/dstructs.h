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
#ifndef __LIBDSTRUCTS_LIST_H__
#define __LIBDSTRUCTS_LIST_H__   /* Guard against multiple inclusion */

#include <unistd.h>


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


/* Wrapper macro for __ll_init(size_t __alloc_size) */
#define ll_init(type) (__ll_init(sizeof(type)))

/* Semantic macro for determining if a list is empty */
#define ll_empty(L) (!ll_first(L))


/** FUNCTION PROTOTYPES **/

/**
 * NOTE: __ll_init(...) is not intended for use by the user. Use the wrapper
 * macro ll_init(...) instead.
 **/
extern   llist_t*          __ll_init   (size_t __elem_size);
extern   void              ll_free     (llist_t* const list);

extern   int   ll_size     (llist_t* const list);

extern   void  ll_addf     (llist_t* const list, void* const elem);
extern   void  ll_addl     (llist_t* const list, void* const elem);
extern   int   ll_add      (llist_t* const list, int index,
                            void* const elem);

extern   void  ll_clear    (llist_t* const list);
extern   int   ll_contains (llist_t* const list, void* const elem);

extern   void* ll_get      (llist_t* const list, int index);
extern   void* ll_first    (llist_t* const list);
extern   void* ll_last     (llist_t* const list);

extern   int   ll_indexof  (llist_t* const list, void* const elem);
extern   void  ll_apply    (llist_t* const list, void (*funct)(void* const));

extern   void* ll_rem      (llist_t* const list, int index);
extern   void* ll_remf     (llist_t* const list);
extern   void* ll_reml     (llist_t* const list);
extern   void* ll_set      (llist_t* const list, int index, void* const elem);

extern   void**   ll_toarr (llist_t* const list);


/* Linkedlist Iterator Functions */
extern   ll_itr_t*   ll_itr      (llist_t* const list, int index);
extern   void        li_free     (ll_itr_t* const itr);

extern   int         li_hasnext  (ll_itr_t* const itr);
extern   int         li_hasprev  (ll_itr_t* const itr);
extern   void*       li_next     (ll_itr_t* const itr);
extern   void*       li_prev     (ll_itr_t* const itr);

#endif   /* __LIBDSTRUCTS_LIST_H__ */

#ifndef __LIBDSTRUCTS_QUEUE_H__
#define __LIBDSTRUCTS_QUEUE_H__


/**
 * Queue public, opaque data type. Contents only accessable through function
 * calls.
 **/
typedef struct que_s que_t;


/* Wrapper macro for __q_init(...) */
#define q_init(type) (__q_init(sizeof(type)))
#define q_empty(Q) (!q_head(Q))

extern que_t*  __q_init (size_t __elem_size);
extern void    q_free   (que_t* const q);

extern int     q_size   (que_t* const q);
extern void*   q_head   (que_t* const q);
extern void*   q_tail   (que_t* const q);
extern void    q_enq    (que_t* const q, void* const elem);
extern void*   q_deq    (que_t* const q);
extern void**  q_toarr  (que_t* const q);

#endif   /* __LIBDSTRUCTS_QUEUE_H__ */

#ifndef __LIBDSTRUCTS_STACK_H__
#define __LIBDSTRUCTS_STACK_H__


/**
 * Stack public, opaque data type. Contents only accessable through function
 * calls.
 **/
typedef struct stack_s stack_t;


/* Wrapper macro for __s_init(...) */
#define s_init(type) (__s_init(sizeof(type)))
#define s_empty(S) (!s_top(S))

extern stack_t*  __s_init (size_t __elem_size);
extern void    s_free   (stack_t* const s);

extern int     s_size   (stack_t* const s);
extern void*   s_top    (stack_t* const s);
extern void    s_push   (stack_t* const s, void* const elem);
extern void*   s_pop    (stack_t* const s);
extern void**  s_toarr  (stack_t* const s);

#endif   /* __LIBDSTRUCTS_STACK_H__ */

#ifndef __LIBDSTRUCTS_TABLE_H__
#define __LIBDSTRUCTS_TABLE_H__   /* Guard against multiple inclusion */


/**
 * Hashtable public, opaque data type. Contents only accessable through
 * function calls.
 **/
typedef struct __hashtab_s hashtab_t;


/* Wrapper macro for __ht_init(size_t __key_size, size_t __val_size) */
#define ht_init(key_type, val_type) \
	(__ht_init(sizeof(key_type), sizeof(val_type))



/** FUNCTION PROTOTYPES **/

/**
 * NOTE: __ht_init(...) is not intended for use by the user. Use the wrapper
 * macro ht_init(...) instead.
 **/
extern   hashtab_t*	__ht_init	(size_t __key_size, size_t __val_size);
extern   void			ht_free		(hashtab_t* const t);

extern   int   ht_size     (hashtab_t* const t);
extern	int	ht_empty		(hashtab_t* const t);
extern   void  ht_clear    (hashtab_t* const t);

extern   void* ht_get      (hashtab_t* const t, void* const key);
extern   void* ht_rem      (hashtab_t* const t, void* const key);
extern   void  ht_add		(hashtab_t* const t, void* const key,
									 void* const value);
extern   void* ht_set      (hashtab_t* const t, void* const key,
									 void* const value);

extern	void**	ht_keys	(hashtab_t* const t);
extern	void**	ht_vals	(hashtab_t* const t);

extern	int	ht_haskey	(hashtab_t* const t, void* const key);
extern	int	ht_hasval	(hashtab_t* const t, void* const value);

extern   void  ht_apply    (hashtab_t* const t, void (*funct)(void* const));


#endif   /* __LIBDSTRUCTS_TABLE_H__ */

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
extern   bst_t*   __bst_init  (size_t __elem_size);
extern   void     bst_free    (bst_t* const tree);

extern   void*    bst_root    (bst_t* const tree);

extern   int      bst_height  (bst_t* const tree);
extern   int      bst_size    (bst_t* const tree);

extern   int      bst_contains(bst_t* const tree, void* const elem);
extern   bst_t*   bst_tree    (bst_t* const tree, void* const elem);

extern   void*    bst_getl    (bst_t* const tree);
extern   void*    bst_getr    (bst_t* const tree);
extern   bst_t*   bst_left    (bst_t* const tree);
extern   bst_t*   bst_right   (bst_t* const tree);

extern   int      bst_add     (bst_t* const tree, void* const elem);
extern   void*    bst_rem     (bst_t* const tree, void* const elem);

extern   void     bst_apply   (bst_t* const tree, void (*funct)(void* const));

extern   void**   bst_toarr   (bst_t* const tree);

#endif   /* __LIBDSTRUCTS_TREE_H__ */

#ifndef __LIBDSTRUCTS_VECTOR_H__
#define __LIBDSTRUCTS_VECTOR_H__   /* Guard against multiple inclusion */


/**
 * Vector public, opaque data type. Contents only accessable through
 * function calls.
 **/
typedef struct __vect_s vect_t;


/**
 * Vector iterator public, opaque data type. Contents only accessable
 * through function calls.
 **/
typedef struct __v_itr_s v_itr_t;


/* Wrapper macro for __v_init(size_t __alloc_size) */
#define v_init(type) (__v_init(sizeof(type)))

/* Semantic macro for determining if a v is empty */
#define v_empty(V) (!v_first(V))

/* Semantic macro for determining the head of a vector */
#define v_head(V) (v_first(V))

/* Semantic macro for determining the tail of a vector */
#define v_tail(V) (v_last(V))


/** FUNCTION PROTOTYPES **/

/**
 * NOTE: __v_init(...) is not intended for use by the user. Use the wrapper
 * macro v_init(...) instead.
 **/
extern   vect_t*  __v_init(size_t __elem_size);
extern   void     v_free  (vect_t* const v);

extern   int   v_size     (vect_t* const v);
extern   int   v_cap      (vect_t* const v);

extern   void  v_addf     (vect_t* const v, void* const elem);
extern   void  v_addl     (vect_t* const v, void* const elem);
extern   int   v_add      (vect_t* const v, int index, void* const elem);

extern   void  v_clear    (vect_t* const v);
extern   int   v_contains (vect_t* const v, void* const elem);

extern   void* v_get      (vect_t* const v, int index);
extern   void* v_first    (vect_t* const v);
extern   void* v_last     (vect_t* const v);

extern   int   v_indexof  (vect_t* const v, void* const elem);
extern   void  v_apply    (vect_t* const v, void (*funct)(void* const));

extern   void* v_rem      (vect_t* const v, int index);
extern   void* v_remf     (vect_t* const v);
extern   void* v_reml     (vect_t* const v);
extern   void* v_set      (vect_t* const v, int index, void* const elem);

extern   void**   v_toarr (vect_t* const v);
extern   void     v_trim  (vect_t* const v);


/* Vector Iterator Functions */
extern   v_itr_t*    v_itr       (vect_t* const v, int index);
extern   void        vi_free     (v_itr_t* const itr);

extern   int         vi_hasnext  (v_itr_t* const itr);
extern   int         vi_hasprev  (v_itr_t* const itr);
extern   void*       vi_next     (v_itr_t* const itr);
extern   void*       vi_prev     (v_itr_t* const itr);

#endif   /* __LIBDSTRUCTS_VECTOR_H__ */

