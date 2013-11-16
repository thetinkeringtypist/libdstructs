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
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "linkedlist.h"


/**
 * Internal definition of a queue. Built upon a linkedlist.
 **/
struct que_s{
	llist_t *__list;
};


/**
 * A simulated constructor for a queue.
 *
 * NOTE: This is a function that is not intended for use by the user. The user
 * should instead use the macro q_init(type), where type is the type that
 * the user wishes to restrict the list to.
 *
 * @param __elem_size - the size of an element in the queue.
 * @return a pointer to an empty queue. Returns a NULL pointer upon allocation
 * 	error.
 **/
que_t* __q_init(size_t __elem_size){
	que_t *queue;

	queue = malloc(sizeof(que_t));

	if(!queue) return NULL;

	queue->__list = __ll_init(__elem_size);
	
	if(!queue->__list){
		free(queue);
		return NULL;
	}

	return queue;
}


/**
 * A simulated destructor for a queue.
 *
 * @param q - the queue to destroy.
 **/
void q_free(que_t* const q){
	if(!q) return;

	ll_free(q->__list);
	free(q);

	return;
}


/**
 * Retrieve the size of a queue.
 *
 * @param q - the queue to retrieve the size of.
 * @return the number of elements in the queue. Returns -1 if the queue is
 * 	NULL.
 **/
int q_size(que_t* const q){
	return (q ? ll_size(q->__list) : -1);
}


/**
 * Retrieves (but does not remove) the next item to be removed from the queue.
 * That is, this function retrieves the next item that would be returned by the
 * next sucessful call to q_deq(...).
 *
 * @param q - the queue to retrieve the element from.
 * @return the next element to be returned by a call to q_deq(...). Returns
 * 	NULL if the queue is NULL.
 **/
void* q_head(que_t* const q){
	return (q ? ll_first(q->__list) : NULL);
}


/**
 * Retrieves (but does not remove) the item most recently added to the queue.
 * That is, this function retrieves the next item that would be returned by the
 * most recent sucessful call of q_enq(...).
 *
 * @param q - the queue to retrieve the element from.
 * @return the next element to be returned by a call to q_enq(...). Returns
 * 	NULL if the queue is NULL.
 **/
void* q_tail(que_t* const q){
	return (q ? ll_last(q->__list) : NULL);
}


/**
 * Add a specified element to the queue. The item to be added will be added to
 * the end of the queue.
 *
 * @param q - the queue to add the specified element to.
 * @param elem - the element to add to the queue.
 **/
void q_enq(que_t* const q, void* const elem){
	if(!q || !elem) return;

	ll_addl(q->__list, elem);
}


/**
 * Removes and returns the head of the queue.
 *
 * @param q - the queue to retrieve the element from.
 * @return the head of the queue. Returns NULL if the queue is empty or NULL.
 **/
void* q_deq(que_t* const q){
	return (q ? ll_remf(q->__list) : NULL);
}


/**
 * Creates and returns a pointer to an array representation of the queue,
 * which free(...) may be called on.
 *
 * @param q - the queue to translate to an array.
 * @return a pointer to an array representation of the queue. Returns NULL if
 * 	the queue is NULL.
 **/
void** q_toarr(que_t* const q){
	return (q ? ll_toarr(q->__list) : NULL);
}

