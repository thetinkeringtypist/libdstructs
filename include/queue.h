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

extern que_t*	__q_init	(size_t __elem_size);
extern void		q_free	(que_t* const q);

extern int		q_size	(que_t* const q);
extern void*	q_head	(que_t* const q);
extern void*	q_tail	(que_t* const q);
extern void		q_enq		(que_t* const q, void* const elem);
extern void*	q_deq		(que_t* const q);
extern void**	q_toarr	(que_t* const q);

#endif	/* __LIBDSTRUCTS_QUEUE_H__ */

