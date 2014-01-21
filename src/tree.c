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
#include <string.h>
#include "tree.h"


#define EXIST 1
#define ADDED 1


/**
 * Internal binary search tree definition.
 **/
struct __bst_s{
	void *__elem;
	size_t __elem_size;
	struct __bst_s *__left;
	struct __bst_s *__right;
};



/** FUNCTION PROTOTYPES **/

/**
 * A simulated constructor for a binary search tree. Creates a new root for the
 * binary search tree to be created.
 *
 * NOTE: This is a function that is not intended for use by the user. The user
 * should instead use the macro bst_init(type), where type is the type that
 * the user wishes to restrict the binary search tree to.
 *
 * @param __elem_size - the size of an element in the binary search tree.
 * @return a pointer to an empty binary search tree. Returns a NULL pointer
 * 	upon allocation error.
 **/
bst_t* __bst_init(size_t __elem_size){
	bst_t *tree;

	tree = malloc(sizeof(bst_t));

	if(!tree) return NULL;

	tree->__elem = NULL;
	tree->__elem_size = __elem_size;
	tree->__left = NULL;
	tree->__right = NULL;

	return tree;
}


/**
 * A simulated destructor for a binary search tree.
 *
 * @param tree - the binary search tree to destroy.
 **/
void bst_free(bst_t* const tree){
	if(!tree) return;

	/* Tree has left child; descend */
	if(tree->__left){
		bst_free(tree->__left);
		tree->__left = NULL;
	}
	
	/* Tree has right child; descend */
	if(tree->__right){
		bst_free(tree->__right);
		tree->__right = NULL;
	}
	
	/* No more children; destroy */
	free(tree->__elem);
	free(tree);
}


/**
 * TODO:
 *
 * Get the root of a binary search tree.
 *
 * @param tree - the binary search tree to get the root of.
 * @return the element at the root of the binary search tree.
 **/
void* bst_root(bst_t* const tree){
	return NULL;
}


/**
 * TODO:
 *
 * Get the height of a binary search tree.
 *
 * @param tree - the binary search tree to get the height of.
 * @return the height of the binary search tree. Return -1 if the tree is NULL.
 * 	Returns the height of the tree otherwise.
 **/
int bst_height(bst_t* const tree){
	if(!tree) return -1;

	/* TODO: calculate the height */

	return 0;
}


/**
 * Get the size of a binary search tree. In other words, returns the number of
 * elements in the tree.
 *
 * @param tree - the binary search tree to get the size of.
 * @return return the size of the tree. In other words, return the number of
 * 	elements in the tree. Returns -1 if the tree is NULL.
 **/
int bst_size(bst_t* const tree){
	if(!tree) return -1;

	/* TODO: calculate the size */

	return 0;
}


/**
 * Determines if an element is in a binary search tree.
 *
 * @param tree - the binary search tree possibly containing the specified
 * 	element.
 * @param elem - the element possibly contained within tree binary search tree.
 * @return 1 if the element exists in the specified list. Returns 0 otherwise
 *    or if the list is NULL;
 **/
int bst_contains(bst_t* const tree, void* const elem){
	int cmp;

	if(!tree || !elem) return !EXIST;

	cmp = memcmp(elem, tree->__elem, tree->__elem_size);

	switch(cmp){
		/* Not here; search left tree */
		case -1:
			return bst_contains(tree->__left, elem);

		/* Here; element exists */
		case 0:
			return EXIST;

		/* Not here; search right tree */
		case 1:
			return bst_contains(tree->__right, elem);

		/* Error; should never occur */
		default:
			return !EXIST;
	}

	/* Error; should never occur */
	return !EXIST;
}


/**
 * TODO:
 *
 * Gets (but does not remove) a subtree of a binary search tree with the root
 * as element.
 *
 * @param tree - the binary search tree to get a subtree from.
 * @param elem - the element to start the new subtree at.
 * @return a pointer to the tree that has elem as its root. Returns NULL if
 * 	either parameter is NULL or if the element does not exist in the tree.
 **/
bst_t* bst_tree(bst_t* const tree, void* const elem){
	int cmp;

	if(!tree || !elem) return NULL;

	cmp = memcmp(elem, tree->__elem, tree->__elem_size);

	switch(cmp){
		/* Not here; search left tree */
		case -1:
			return bst_tree(tree->__left, elem);

		/* Here; return tree */
		case 0:
			return tree;

		/* Not here; search right tree */
		case 1:
			return bst_tree(tree->__right, elem);

		/* Error; should never occur */
		default:
			return NULL;
	}

	/* Should never occur */
	return NULL;
}


/**
 * Gets (but does not remove) the left child (element) of a binary search tree.
 * 
 * @param tree - the binary search tree to get the left element of.
 * @return the left element of the binary search tree. Return NULL if the tree
 * 	is NULL or if there is no left child (element).
 **/
void* bst_getl(bst_t* const tree){
	if(!tree) return NULL;

	if(!tree->__left) return NULL;

	return tree->__left->__elem;
}


/**
 * Gets (but does not remove) the right child (element) of a binary search
 * tree.
 * 
 * @param tree - the binary search tree to get the right element of.
 * @return the right element of the binary search tree. Return NULL if the tree
 * 	is NULL or if there is no right child (element).
 **/
void* bst_getr(bst_t* const tree){
	if(!tree) return NULL;

	if(!tree->__right) return NULL;

	return tree->__right->__elem;
}


/**
 * Gets (but does not remove) the left subtree of a binary search tree.
 *
 * @param tree - the binary search tree to get the left subtree of.
 * @return a pointer to the left subtree of the binary search search tree.
 * 	Returns NULL if the tree is NULL or there is no left subtree.
 **/
bst_t* bst_left(bst_t* const tree){
	if(!tree) return NULL;

	return tree->__left;
}


/**
 * Gets (but does not remove) the right subtree of a binary search tree.
 *
 * @param tree - the binary search tree to get the right subtree of.
 * @return a pointer to the right subtree of the binary search search tree.
 * 	Returns NULL if the tree is NULL or there is no right subtree.
 **/
bst_t* bst_right(bst_t* const tree){
	if(!tree) return NULL;

	return tree->__right;
}

/**
 * TODO:
 *
 * Add an element to a binary search tree. If an element already exists in the
 * tree, it is not added. In other words, duplicate elements are not added.
 *
 * @param tree - the binary search tree to add an element to.
 * @param elem - the element to add to a binary search tree.
 * @return 1 if the element was added to the binary search tree.
 **/
int bst_add(bst_t* const tree, void* const elem){
	if(!tree || !elem) return !ADDED;

	/* TODO: add element to the tree */

	return !ADDED;
}


/**
 * TODO:
 *
 * Remove an element from a binary search tree.
 *
 * @param tree - the binary search tree to remove an element from.
 * @param elem - the element to remove from a binary search tree.
 * @return the element removed from the binary search tree. Returns NULL if the
 * 	tree is NULL, the element is NULL, or the element does not exist in the
 * 	tree.
 **/
void* bst_rem(bst_t* const tree, void* const elem){
	if(!tree || !elem) return NULL;

	/* TODO: remove an element from the tree */

	return NULL;
}


/**
 * Apply a given function over a binary search tree.
 *
 * @param tree - the binary search tree to apply a function over.
 * @param funct - the function to apply over a binary search tree.
 **/
void bst_apply(bst_t* const tree, void (*funct)(void* const)){
	if(!tree) return;

	if(funct == free){
		bst_free(tree);
		return;
	}

	/* Apply the function */
	(funct)(tree->__elem);

	/* Apply to left and right subtrees */
	bst_apply(tree->__left, funct);
	bst_apply(tree->__right, funct);
}


/**
 * TODO:
 *
 * Creates and returns a pointer to an array representation of a binary search
 * tree. Returns a pointer to an array on which free(...) may be called.
 *
 * @param tree - the binary search tree to translate to an array.
 * @return a pointer to an array representation of the binary search tree.
 **/
void** bst_toarr(bst_t* const tree){
	int **array;

	if(!tree) return NULL;

	array = malloc(sizeof(void*) * bst_size(tree));

	if(!array) return NULL;

	/* TODO: populate array */

	return (void**) array;
}

