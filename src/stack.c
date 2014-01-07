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
#include <stdlib.h>
#include "stack.h"
#include "list.h"


/**
 * Stack public, opaque data type. Contents only accessable through function
 * calls.
 **/
struct stack_s {
   llist_t *__list;
};


/* Wrapper macro for __s_init(...) */
#define s_init(type) (__s_init(sizeof(type)))
#define s_empty(S) (!s_top(S))


/**
 * A simulated constructor for a stack.
 *
 * NOTE: This is a function that is not intended for use by the user. The user
 * should instead use the macro s_init(type), where type is the type that
 * the user wishes to restrict the list to.
 *
 * @param __elem_size - the size of an element in the stack.
 * @return a pointer to an empty stack. Returns a NULL pointer upon allocation
 *    error.
 **/
stack_t* __s_init(size_t __elem_size) {
   stack_t *stack;

   stack = malloc(sizeof(stack_t));

   if(!stack) return NULL;

   stack->__list = __ll_init(__elem_size);

   if(!stack->__list) {
      free(stack);
      return NULL;
   }

   return stack;
}


/**
 * A simulated destructor for a stack.
 *
 * @param s - the stack to destroy.
 **/
void s_free(stack_t* const s) {
   if(!s) return;

   ll_free(s->__list);
   free(s);
}


/**
 * Retrieve the size of a stack.
 *
 * @param s - the stack to retrieve the size of.
 * @return the number of elements in the stack. Returns -1 if the stack is
 *    NULL.
 **/
int s_size(stack_t* const s) {
   return (s ? ll_size(s->__list) : -1);
}


/**
 * Retrieves (but does not remove) the next item to be removed from the stack.
 * That is, this function retrieves the next item that would be returned by the
 * next sucessful call to s_pop(...).
 *
 * @param s - the stack to retrieve the element from.
 * @return the next element to be returned by a call to s_pop(...). Returns
 *    NULL if the stack is NULL.
 **/
void* s_top(stack_t* const s) {
   return (s ? ll_first(s->__list) : NULL);
}


/**
 * Add a specified element to the stack. The item to be added will be added to
 * the top of the stack.
 *
 * @param s - the stack to add the specified element to.
 * @param elem - the element to add to the stack.
 **/
void s_push(stack_t* const s, void* const elem) {
   if(!s || !elem) return;

   ll_addf(s->__list, elem);
}


/**
 * Removes and returns the top of the stack.
 *
 * @param s - the stack to retrieve the element from.
 * @return the top of the stack. Returns NULL if the stack is empty or NULL.
 **/
void* s_pop(stack_t* const s) {
   return (s ? ll_remf(s->__list) : NULL);
}


/**
 * Creates and returns a pointer to an array representation of the stack,
 * which free(...) may be called on.
 *
 * @param s - the stack to translate to an array.
 * @return a pointer to an array representation of the stack. Returns NULL if
 *    the stack is NULL.
 **/
void** s_toarr(stack_t* const s) {
   return (s ? ll_toarr(s->__list) : NULL);
}

