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

