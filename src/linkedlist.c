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
#include <stdlib.h> 			/* For malloc(...), free(...) */
#include <string.h>			/* For memcmp(...) */
#include "linkedlist.h"		/* For llist_t, ll_itr_t */


#define ADDED 1
#define EXIST 1


/**
 * Internal linkedlist definition.
 **/
struct __llist_s{
	void *__first;
	void *__last;
	size_t __elem_size;
	int __size;
};


/**
 * Internal linkedlist iterator definition.
 **/
struct __ll_iter_s{
	void *__next;
	void *__prev;
};


/**
 * Internal node type. Only used in this file.
 **/
typedef struct __node_s{
	void *element;
	int index;
	struct __node_s *prev;
	struct __node_s *next;
} __node_t;


/**
 * A simulated constructor for a linkedlist.
 *
 * NOTE: This is a function that is not intended for use by the user. The user
 * should instead use the macro ll_create(type), where type is the type that
 * the user wishes to restrict the list to.
 *
 * @param __elem_size - the size of an element in the linkedlist.
 * @return a pointer to an empty linkedlist. Returns a NULL pointer upon
 * 	allocation error.
 **/
llist_t* __ll_init(size_t __elem_size){
	llist_t *list;

	list = malloc(sizeof(llist_t));
	
	/* Alloc error */
	if(!list) return NULL;

	/* Initialize */
	list->__first = NULL;
	list->__last = NULL;
	list->__elem_size = __elem_size;
	list->__size = 0;
	
	return list;
}


/**
 * A simulated destructor for a linkedlist.
 *
 * @param list - the list to destroy.
 **/
void ll_free(llist_t* const list){
	if(!list) return;

	ll_clear(list);	/* Remove elements in list */
	free(list);
}


/**
 * Retrieve the size of a list.
 *
 * @param list - the list to retrieve the size of.
 * @return the length of the list. Returns -1 if the list is NULL.
 **/
int ll_size(llist_t* const list){
	return (list ? list->__size : -1);
}


/**
 * Adds the specified element at the specified index in the list. Shifts
 * remaining elements right one position (incrementing indices).
 *
 * @param list - the linkedlist to add the specified element to.
 * @param index - the index to insert the specified element.
 * @param element - the specified element to add to the list.
 * @return 1 if the element is added to the list. Return 0 if the list is NULL,
 * 	or if the specified index is less than zero (0) or larger than the size
 * 	of the list.
 **/
int ll_add(llist_t* const list, int index, void* const element){
	__node_t *temp, *new;
	int count;

	if(!list) return !ADDED;

	if(index < 0 || index > ll_size(list))
		return !ADDED;

	new = malloc(sizeof(__node_t));	/* Allocate */

	if(!new) return !ADDED;


	/* Initialize */
	new->element = element;
	new->index = index;
	new->prev = NULL;
	new->next = NULL;
	
	/* Adding to empty list */
	if(ll_size(list) == 0){
		list->__first = new;
		list->__last = new;
		
		list->__size++;
		return ADDED;
	}

	/* Adding to end of list */
	if(index == ll_size(list)){
		temp = list->__last;
		temp->next = new;
		new->prev = temp;
		list->__last = new;

		list->__size++;
		return ADDED;
	}

	/* Adding to front of list */
	if(index == 0){
		new->next = list->__first;
		((__node_t*) list->__first)->prev = new;
		list->__first = new;
	}

	/* Adding somewhere in middle of list */
	else{
		count = 0;
		temp = list->__first;
		
		/* Loop until temp is at the desired index */
		while(temp->next){
			if(count == index){
				new->next = temp->next;
				new->prev = temp;
				temp->next->prev = new;
				temp->next = new;
				
				break;
			}

			temp = temp->next;
			count++;
		}
	}

	temp = new->next;

	/* Item added */
	list->__size++;
	return ADDED;
}


/**
 * Add a specified element to the front of this list.
 *
 * @param list - the list to add the specified element to.
 * @param element - the element to add to the list.
 **/
void ll_addf(llist_t* const list, void* const element){
	ll_add(list, 0, element);
}


/**
 * Add a specified element to the end of this list.
 *
 * @param list - the list to add the specified element to.
 * @param element - the element to add to the list.
 **/
void ll_addl(llist_t* const list, void* const element){
	ll_add(list, ll_size(list), element);
}


/**
 * Removes all elements in the specified list. Frees all memory associated with
 * the underlying implementation of the linkedlist as well as the elements that
 * were placed into the list by the user.
 *
 * @param list - the list to clear.
 **/
void ll_clear(llist_t* const list){
	if(!list) return;

	/**
	 * While the list is not empty, remove
	 * the first element in the list.
	 **/
	while(ll_size(list) != 0)
		free(ll_rem(list, 0));
}


/**
 * Determines if the specified element is contained within this list.
 *
 * NOTE: This function uses memcmp(...). Objects are compared as byte arrays.
 * Accordingly, each element in the object is used to measure equality. As
 * such, it is best that unused items in objects be initialized to either
 * zero (0) or NULL. Uninitialized items in objects may cause comparison
 * differences.
 *
 * @param list - the list possibly containing the specified element.
 * @param element - the element possibly contained within the specified list.
 * @return 1 if the element exists in the specified list. Returns 0 otherwise
 * 	or if the list is NULL;
 **/
int ll_contains(llist_t* const list, void* const element){
	__node_t *temp;
	size_t num_bytes;

	if(!list) return !EXIST;

	temp = list->__first;
	num_bytes = list->__elem_size;

	/* Loop through to find the element */
	while(temp){
		/* If the element is found */
		if(memcmp(element, temp->element, num_bytes) == 0)
			return EXIST;

		temp = temp->next;
	}

	/* Element does not exist */
	return !EXIST;
}


/**
 * Retrieves (but does not remove) the element at the specified index in
 * the list.
 *
 * @param list - the list to retrieve the element from.
 * @param index - the index in the specified list to retrieve.
 * @return the element at the specified index. Returns 0 if the list is NULL,
 * 	if the index is less than zero (0), or if the index is greater than the
 * 	size of the list.
 **/
void* ll_get(llist_t* const list, int index){
	__node_t *temp;
	int count;

	if(!list) return NULL;

	if(index < 0 || index >= ll_size(list))
		return NULL;
	
	temp = list->__first;
	count = 0;

	/* Loop until desired index is found */
	while(temp){
		if(count == index)
			return temp->element;	/* Return the element */

		temp = temp->next;
		count++;
	}
	
	/* Index not found */
	return NULL;
}


/**
 * Retrieves (but does not remove) the first element in the specified
 * list.
 *
 * @param list - the list to retrieve the element from.
 * @return the element at the specified index. Returns 0 if the list is NULL,
 * 	if the index is less than zero (0), or if the index is greater than the
 * 	size of the list.
 **/
void* ll_first(llist_t* const list){
	return ll_get(list, 0);
}


/**
 * Retrieves (but does not remove) the last element in the specified
 * list.
 *
 * @param list - the list to retrieve the element from.
 * @return the element at the specified index. Returns 0 if the list is NULL,
 * 	if the index is less than zero (0), or if the index is greater than the
 * 	size of the list.
 **/
void* ll_last(llist_t* const list){
	return ll_get(list, ll_size(list) - 1);
}


/**
 * Retrieve the index of the first occurrence of the specifed element in
 * the specified list.
 * 
 * NOTE: This function uses memcmp(...). Objects are compared as byte arrays.
 * Accordingly, each element in the object is used to measure equality. As
 * such, it is best that unused items in objects be initialized to either zero
 * (0) or NULL. Uninitialized items in objects may cause comparison
 * differences.
 *
 * @param list - the list to retreive the index from.
 * @param element - the element to search for.
 * @return the index of the first occurrence of the specified element, or -1 if
 * 	the list is NULL or does not contain the specified element.
 **/
int ll_indexof(llist_t* const list, void* const element){
	__node_t *temp;
	size_t num_bytes;
	int count;

	if(!list) return -1;
	
	temp = list->__first;
	num_bytes = list->__elem_size;
	count = 0;

	/* Look for first occurrence of element */
	while(temp){
		/* If the element is found */
		if(memcmp(element, temp->element, num_bytes) == 0)
			return count;

		temp = temp->next;
		count++;
	}

	/* Element not found */
	return -1;
}


/**
 * Removes the element at the specified index in the specified list. Shifts
 * remaining elements left one position (decrementing indices).
 *
 * @param list - the list to remove the specified element from.
 * @param index - the index of the element to be removed.
 * @return 1 if the list contained the specified element. Returns 0 if the list
 * 	is NULL or the index is less than zero (0) or the index is greater than
 * 	the size of the list.
 **/
void* ll_rem(llist_t* const list, int index){
	__node_t *temp, *target;
	void *result;
	int count;

	if(!list) return NULL;
	
	if(index < 0 || index >= ll_size(list))
		return NULL;
	
	/* Removing from empty list */
	if(ll_size(list) == 0) return NULL;

	/* Removing from front of list */
	if(index == 0){
		target = list->__first;
		temp = target->next;
		temp->prev = NULL;
		list->__first = temp;

		/* There was only one element in the list to remove */
		if(!temp)
			list->__last = temp;
	}

	/* Remove from elsewhere in list */
	else{
		temp = list->__first;
		count = 1;
		
		/* Loop until temp is at the desired index */
		while(temp->next){
			if(count == index){
				target = temp->next;
				target->next->prev = temp;
				temp->next = target->next;

				break;
			}

			temp = temp->next;
			count++;
		}
	}

	temp = target->next;

	/* Grab element, free containing node */
	result = target->element;
	free(target);

	list->__size--;
	return result;
}


/**
 * Removes and returns the first element in the specified list.
 *
 * @param list - the list to retrieve the element from.
 * @return the first element in the list. Returns NULL if the list is empty or
 * 	NULL.
 **/
void* ll_remf(llist_t* const list){
	return ll_rem(list, 0);
}


/**
 * Removes and returns the last element in the specified list.
 *
 * @param list - the list to retrieve the element from.
 * @return the last element in the list. Returns NULL if the list is empty or
 * 	NULL.
 **/
void* ll_reml(llist_t* const list){
	return ll_rem(list, ll_size(list) - 1);
}


/**
 * Replaces the element at the specified index with the specified element.
 *
 * @param list - the list in which to replace the specified element.
 * @param index - specified index of the element to replace.
 * @param element - element to be stored at the specified index.
 * @return the element previously stored at the specified index. 
 **/
void* ll_set(llist_t* const list, int index, void* const element){
	__node_t *temp;
	void *former;
	int count;

	if(!list) return NULL;

	if(index < 0 || index >= ll_size(list))
		return NULL;
	
	temp = list->__first;
	count = 0;

	/* Loop until desired index is found */
	while(temp){
		if(count == index){
			former = temp->element;
			temp->element = element;

			return former;
		}

		temp = temp->next;
		count++;
	}

	/* Index not found */
	return NULL;
}


/**
 * Creates and returns a pointer to an array representation of the list.
 *
 * @param list - the list to translate to an array.
 * @return a pointer to an array representation of the list.
 **/
void** ll_toarr(llist_t* const list){
	int** array;
	int i, count;

	if(!list) return NULL;

	count = list->__size;

	array = malloc(sizeof(void*));

	if(!array) return NULL;

	for(i = 0; i < count; i++)
		array[i] = ll_get(list, i);
	
	return (void**) array;
}


/** Linkedlist Iterator Functions */

/**
 * A simulated constructor for a linkedlist iterator. Returns an iterator over
 * a specified linkedlist starting at a specified index.
 *
 * @param list - the list to return an iterator over.
 * @param index - the position that the iterator will start at.
 * @return an iterator over the specified linkedlist. Returns a NULL pointer
 * 	if the specified list is NULL, (index < 0 || index >= ll_size(list)), or
 * 	upon allocation error.
 **/
ll_itr_t* ll_itr(llist_t* const list, int index){
	ll_itr_t *iterator;
	__node_t *temp;
	int count;

	if(!list) return NULL;
	
	if(index < 0 || index >= ll_size(list))
		return NULL;
	
	iterator = malloc(sizeof(ll_itr_t));

	if(!iterator) return NULL;
	
	temp = list->__first;
	count = 0;

	/* Loop to desired position */
	while(temp){
		if(count == index){
			iterator->__next = temp;
			iterator->__prev = temp->prev;

			return iterator;
		}

		temp = temp->next;
		count++;
	}

	/* Index not found */
	return NULL;
}


/**
 * A simulated destructor for a linkedlist iterator.
 *
 * @param iterator - the iterator to destroy.
 **/
void li_free(ll_itr_t* const iterator){
	free(iterator);
}


/**
 * Indicates whether or not the iterator has more elements. In other words,
 * returns 1 if li_next(...) would return an element.
 *
 * @param iterator - the iterator to check against for more elements.
 * @return 1 if there exists more elements in the iterator. Returns 0 if the
 * 	iterator is NULL or does not have anymore elements.
 **/
int li_hasnext(ll_itr_t* const iterator){
	if(!iterator) return !EXIST;

	/* There exists another element */
	return (iterator->__next ? EXIST : !EXIST);
}


/**
 * Indicates whether or not the iterator has previous elements. In other words,
 * returns 1 if li_prev(...) would return an element.
 *
 * @param iterator - the iterator to check against for previous elements.
 * @return 1 if there exists a previous element in the iterator. Returns 0 if
 * 	the iterator is NULL of does not have any previous elements.
 **/
int li_hasprev(ll_itr_t* const iterator){
	if(!iterator) return !EXIST;

	/* There exists a previous element */
	return (iterator->__prev ? EXIST : !EXIST);
}


/**
 * Retrieves (but does not remove) the next element in the iterator.
 *
 * @param iterator - the iterator to return an element from.
 * @return the next element in the iterator. Returns NULL if the iterator is
 * 	NULL or there are no more elements in the iterator.
 **/
void* li_next(ll_itr_t* const iterator){
	__node_t *temp;
	
	if(!iterator) return NULL;

	temp = iterator->__next;

	/* Move iterator ahead */
	if(temp){
		iterator->__next = temp->next;
		return temp->element;
	}

	/* No more items */
	return NULL;
}


/**
 * Retrieves (but does not remove) the previous element in the iterator.
 *
 * @param iterator - the iterator to return an element from.
 * @return the previous element in the iterator. Returns NULL if the iterator
 * 	is NULL or there are no previous elements in the iterator.
 **/
void* li_prev(ll_itr_t* const iterator){
	__node_t *temp;

	if(!iterator) return NULL;

	temp = iterator->__prev;

	/* Move iterator backwards */
	if(temp){
		iterator->__prev = temp->prev;
		return temp->element;
	}

	/* No previous items */
	return NULL;
}

