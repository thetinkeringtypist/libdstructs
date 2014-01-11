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
#include <stdlib.h>     /* For malloc(...), free(...) */
#include <string.h>     /* For memcmp(...), memcpy(...) */
#include "vector.h"

#define INIT_SIZE 10
#define ADDED 1
#define EXIST 1


/* Local functions */
static void __v_expand(vect_t* const v);


/**
 * Internal vector definition.
 **/
struct __vect_s {
   int **__elements;
   size_t __elem_size;
   int __cap;
   int __size;
};


/**
 * Internal vector iterator definition.
 **/
struct __v_itr_s {
   vect_t *vector;
   int pos;
};



/**
 * A simulated constructor for a vector. Creates a vector has an initial
 * capacity of 10 elements.
 *
 * NOTE: This is a function that is not intended for use by the user. The user
 * should instead use the macro v_init(type), where type is the type that
 * the user wishes to restrict the list to.
 *
 * @param __elem_size - the size of an element in the vector.
 * @return a pointer to an empty vector. Returns a NULL pointer upon allocation
 *    error.
 **/
vect_t* __v_init(size_t __elem_size) {
   vect_t *vector;

   vector = malloc(sizeof(vect_t));

   if(!vector) return NULL;

   vector->__elements = calloc(INIT_SIZE, sizeof(void*));

   if(!vector->__elements) {
      free(vector);
      return NULL;
   }

   vector->__elem_size = __elem_size;
   vector->__cap = INIT_SIZE;
   vector->__size = 0;

   return vector;
}


/**
 * A simulated destructor for a vector.
 *
 * @param v - the vector to destroy.
 **/
void v_free(vect_t* const v) {
   if(!v) return;

   v_clear(v);          /* Remove elements in vector */
   free(v->__elements);
   free(v);
}


/**
 * Retrieve the size of a vector.
 *
 * @param v - the vector to retrieve the size of.
 * @return the length of the vector. Returns -1 if the vector is NULL.
 **/
int v_size(vect_t* const v) {
   return (v ? v->__size : -1);
}


/**
 * Retrieve the capacity of a vector.
 *
 * @param v - the vector to retrieve the capacity of.
 * @return the capacity of the vector. Returns -1 if the vector is NULL.
 **/
int v_cap(vect_t* const v) {
   return (v ? v->__cap : -1);
}


/**
 * If a vector is full, expand it by a factor of 2 times its capacity plus 1.
 * In other words expand by ((2 * v->__cap) + 1).
 *
 * @param v - the vector to expand.
 **/
static void __v_expand(vect_t* const v) {
   v->__cap <<= 1;
   v->__cap++;

   v->__elements = realloc(v->__elements, v->__cap * sizeof(void*));
}


/**
 * Adds the specified element at the specified index in the vector. Shifts
 * remaining elements right one position (incrementing indices).
 *
 * @param v - the vector to add the specified element to.
 * @param index - the index to insert the specified element.
 * @param elem - the specified element to add to the vector.
 * @return 1 if the element is added to the vector. Return 0 if the vector is
 *    NULL, or if the specified index is less than zero (0) or larger than the
 *    size of the vector.
 **/
int v_add(vect_t* const v, int index, void* const elem) {
   int i, size;

   if(!v) return !ADDED;

   if(index < 0 || index > v->__size)
      return !ADDED;

   size = ++v->__size;

   if(size == v->__cap)
      __v_expand(v);

   /* Move elements right one position */
   for(i = size; i > index; i--)
      v->__elements[i] = v->__elements[i - 1];

   v->__elements[index] = elem;

   return ADDED;
}


/**
 * Add a specified element to the front of this vector.
 *
 * @param v - the vector to add the specified element to.
 * @param elem - the element to add to the vector.
 **/
void v_addf(vect_t* const v, void* const elem) {
   v_add(v, 0, elem);
}


/**
 * Add a specified element to the end of this vector.
 *
 * @param v - the vector to add the specified element to.
 * @param elem - the element to add to the vector.
 **/
void v_addl(vect_t* const v, void* const elem) {
   if(!v) return;

   v_add(v, v->__size, elem);
}


/**
 * Attempts to remove all elements in the specified vector. Applies free(...)
 * to each element in a vector and sets the size of the vector to 0.
 *
 * @param v - the vector to clear.
 **/
void v_clear(vect_t* const v) {
   v_apply(v, free);
}


/**
 * Determines if the specified element is contained within this vector.
 *
 * @param v - the vector possibly containing the specified element.
 * @param elem - the element possibly contained within the specified vector.
 * @return 1 if the element exists in the specified vector. Returns 0 otherwise
 *    or if the list is NULL;
 **/
int v_contains(vect_t* const v, void* const elem) {
   size_t num_bytes;
   int i, size;

   if(!v) return !EXIST;

   num_bytes = v->__elem_size;
   size = v->__size;

   /* Loop through to find the element */
   for(i = 0; i < size; i++)
      if(memcmp(elem, v->__elements[i], num_bytes) == 0)
         return EXIST;

   /* Element does not exist */
   return !EXIST;
}


/**
 * Retrieves (but does not remove) the element at the specified index in
 * the vector.
 *
 * @param v - the vector to retrieve the element from.
 * @param index - the index in the specified vector to retrieve.
 * @return the element at the specified index. Returns 0 if the vector is NULL,
 *    if the index is less than zero (0), or if the index is greater than the
 *    size of the vector.
 **/
void* v_get(vect_t* const v, int index) {
   if(!v) return NULL;

   if(index < 0 || index >= v->__size)
      return NULL;

   return v->__elements[index];
}


/**
 * Retrieves (but does not remove) the first element in the specified vector.
 *
 * @param v - the vector to retrieve the element from.
 * @return the first element in the vector. Returns NULL if the vector is NULL
 *    or empty.
 **/
void* v_first(vect_t* const v) {
   return v_get(v, 0);
}


/**
 * Retrieves (but does not remove) the last element in the specified vector.
 *
 * @param v - the vector to retrieve the element from.
 * @return the last element in the vector. Returns NULL if the vector is NULL
 *    or empty.
 **/
void* v_last(vect_t* const v) {
   if(!v) return NULL;

   return v_get(v, v->__size - 1);
}


/**
 * Retrieve the index of the first occurrence of the specifed element in
 * the specified vector.
 *
 * @param v - the vector to retreive the index from.
 * @param elem - the element to search for.
 * @return the index of the first occurrence of the specified element, or -1 if
 *    the vector is NULL or does not contain the specified element.
 **/
int v_indexof(vect_t* const v, void* const elem) {
   size_t num_bytes;
   int i, size;

   if(!v) return -1;

   num_bytes = v->__elem_size;
   size = v->__size;

   /* Look for first occurance */
   for(i = 0; i < size; i++)
      if(memcmp(elem, v->__elements[i], num_bytes) == 0)
         return i;

   /* Element not found */
   return -1;
}


/**
 * Apply a function over all the elements in a vector.
 *
 * @param v - the vector to apply an operation over.
 * @param funct - the function to apply over the specified vector, where the
 *    argument to the function is an element in the vector.
 **/
void v_apply(vect_t* const v, void (*funct)(void* const)) {
   int i, size;

   if(!v) return;

   size = v->__size;

   /* For each element in the list */
   for(i = 0; i < size; i++)
      (funct)(v->__elements[i]);

   if(funct == free)
      v->__size = 0;
}


/**
 * Removes the element at the specified index in the specified vector. Shifts
 * remaining elements left one position (decrementing indices).
 *
 * @param v - the vector to remove the specified element from.
 * @param index - the index of the element to be removed.
 * @return 1 if the vector contained the specified element. Returns 0 if the
 *    vector is NULL or the index is less than zero (0) or the index is greater
 *    than the size of the vector.
 **/
void* v_rem(vect_t* const v, int index) {
   void *target;
   int i, size;

   if(!v) return NULL;

   if(index < 0 || index >= v->__size)
      return NULL;

   /* Removing from empty list */
   if(v_empty(v)) return NULL;

   size = v->__size;
   target = v->__elements[index];

   /* Shift elements left one position */
   for(i = index; i < size; i++)
      v->__elements[i] = v->__elements[i + 1];

   v->__size--;
   return target;
}


/**
 * Removes and returns the first element in the specified vector.
 *
 * @param v - the vector to retrieve the element from.
 * @return the first element in the vector. Returns NULL if the list is empty
 *    or NULL.
 **/
void* v_remf(vect_t* const v) {
   return v_rem(v, 0);
}


/**
 * Removes and returns the last element in the specified vector.
 *
 * @param v - the vector to retrieve the element from.
 * @return the last element in the vector. Returns NULL if the vector is empty
 *    or NULL.
 **/
void* v_reml(vect_t* const v) {
   if(!v) return NULL;

   return v_rem(v, v->__size - 1);
}


/**
 * Replaces the element at the specified index with the specified element.
 *
 * @param v - the vector in which to replace the specified element.
 * @param index - specified index of the element to replace.
 * @param elem - element to be stored at the specified index.
 * @return the element previously stored at the specified index.
 **/
void* v_set(vect_t* const v, int index, void* const elem) {
   void *target;

   if(!v) return NULL;

   if(index < 0 || index >= v->__size)
      return NULL;

   target = v->__elements[index];
   v->__elements[index] = elem;

   return target;
}


/**
 * Creates and returns a pointer to an array representation of the vector.
 * Returns a pointer to an array on which free(...) may be called.
 *
 * @param v - the vector to translate to an array.
 * @return a pointer to an array representation of the vector.
 **/
void** v_toarr(vect_t* const v) {
   int **array;
   int size;

   if(!v) return NULL;

   size = v->__size;

   array = malloc(sizeof(void*) * size);

   if(!array) return NULL;

   /* Assign pointers to new array */
   array = memcpy(array, v->__elements, sizeof(void*) * size);

   return (void**) array;
}


/**
 * Trim the capacity of the vector to the current size of the vector.
 *
 * @param v - the vector to trim to size.
 * @return the vector trimmed to its size. Returns NULL if the vector is NULL.
 **/
void v_trim(vect_t* const v) {
   int size;

   if(!v) return;

   size = v->__size;
   v->__elements = realloc(v->__elements, sizeof(void*) * size);
   v->__cap = size;
}


/** Vector Iterator Functions **/

/**
 * A simulated constructor for a vector iterator. Returns an iterator over
 * a specified vector starting at a specified index.
 *
 * @param v - the vector to return an iterator over.
 * @param index - the position that the iterator will start at.
 * @return an iterator over the specified vector. Returns a NULL pointer if the
 *    specified vector is NULL, (index < 0 || index >= v_size(v)), or upon
 *    allocation error.
 **/
v_itr_t* v_itr(vect_t* const v, int index) {
   v_itr_t *iterator;

   if(!v) return NULL;

   if(index < 0 || index >= v->__size)
      return NULL;

   iterator = malloc(sizeof(v_itr_t));

   if(!iterator) return NULL;

   iterator->vector = v;
   iterator->pos = index;

   /* Index not found */
   return iterator;
}


/**
 * A simulated destructor for a vector iterator.
 *
 * @param itr - the iterator to destroy.
 **/
void vi_free(v_itr_t* const itr) {
   free(itr);
}


/**
 * Indicates whether or not the iterator has more elements. In other words,
 * returns 1 if vi_next(...) would return an element.
 *
 * @param itr - the iterator to check against for more elements.
 * @return 1 if there exists more elements in the iterator. Returns 0 if the
 *    iterator is NULL or does not have anymore elements.
 **/
int vi_hasnext(v_itr_t* const itr) {
   if(!itr) return !EXIST;

   /* There exists another element */
   if(itr->pos == itr->vector->__size)
      return !EXIST;

   return EXIST;
}


/**
 * Indicates whether or not the iterator has previous elements. In other words,
 * returns 1 if vi_prev(...) would return an element.
 *
 * @param itr - the iterator to check against for previous elements.
 * @return 1 if there exists a previous element in the iterator. Returns 0 if
 *    the iterator is NULL of does not have any previous elements.
 **/
int vi_hasprev(v_itr_t* const itr) {
   if(!itr) return !EXIST;

   /* There exists a previous element */
   return (itr->pos ? EXIST : !EXIST);
}


/**
 * Retrieves (but does not remove) the next element in the iterator.
 *
 * @param itr - the iterator to return an element from.
 * @return the next element in the iterator. Returns NULL if the iterator is
 *    NULL or there are no more elements in the iterator.
 **/
void* vi_next(v_itr_t* const itr) {
   void *target;

   if(!itr) return NULL;

   /* If there are more elements */
   if(!vi_hasnext(itr)) return NULL;

   target = itr->vector->__elements[itr->pos];
   itr->pos++;

   return target;
}


/**
 * Retrieves (but does not remove) the previous element in the iterator.
 *
 * @param itr - the iterator to return an element from.
 * @return the previous element in the iterator. Returns NULL if the iterator
 *    is NULL or there are no previous elements in the iterator.
 **/
void* vi_prev(v_itr_t* const itr) {
   void *target;

   if(!itr) return NULL;

   /* If there are more elements */
   if(!vi_hasprev(itr)) return NULL;

   target = itr->vector->__elements[itr->pos];
   itr->pos--;

   return target;
}

