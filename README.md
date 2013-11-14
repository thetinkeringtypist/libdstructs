libdstructs
===========

Simple ANSI C Data Structures Library. This is generic data structures library
written in ANSI C. As of this moment, these implementations are not intended to
be C++ compatible or thread-safe.

I found myself writing the same data structures over and over again in my
projects for school like linkedlists, queues, stacks, and hashtables. Many
times, this was born out of the restriction of not being able to use arrays in
projects. So, why not build a collection of the data structures most commonly
used and put them in a library for future use? There are a bunch of libraries
like this one out there. This library, `libdstructs`, was built to model the
basic functionality of the
[Java Collections Framework](http://docs.oracle.com/javase/7/docs/technotes/guides/collections/overview.html).

The list of data structures that will be included will be those that are fairly
commonplace, including, but not limited to, linkedlists, queues, vectors,
trees, sets, and hashtables.


Implemenation
-------------
All data structures are implemented as opaque data types. This means that they
cannot be allocated on the stack and must be accessed though function calls and
pointers. For example:

	void example(void){
		llist *list;	/* Pointer */

		list = ll_init(int);	/* Allocation on the heap */

		.
		.
		.

		ll_free(list);
	}

is how you would create and destroy a linkedlist. The following is an example
of something that cannot be done:

	void example(void){
		llist list;	/* Allocation on the stack */

		.
		.
		.
	}

The compiler cannot determine how much space on the stack to make for the
linkedlist since the data type is opaque. All of that information is hidden
inside of the appropriate translation unit.


Installation
------------
Coming soon.


Notes
-----
Graphs are not currently planned to be a part of this library. See
[libgstructs](https://github.com/bezeredi/libgstructs) for graph structure
implementations.


License
-------
The `libdstructs` library is distributed under the GNU General Public License
(GPL) version 3. See
[LICENSE](https://github.com/bezeredi/libdstructs/blob/master/LICENSE) for more
information.

