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

