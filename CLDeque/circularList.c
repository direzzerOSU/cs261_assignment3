/***********************************************************
* Author:
* Email: 
* Date Created: 
* Filename: circularList.c
*
* Overview:
*   This program is a circular doubly linked list implementation 
*	of a deque with a front sentinel.
*	It allows for the following behavior:
*		- adding a new link to the front/back
*		- getting the value of the front/back links
*		- removing the front/back link
*		- checking if the deque is empty
*		- printing the values of all the links
*		- reversing the order of the links
*
*	Note that this implementation uses double links (links with
*	next and prev pointers) and that given that it is a circular
*	linked deque the last link points to the sentinel and the first
*	link points to the last link -- instead of null.
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

#ifndef FORMAT_SPECIFIER
#define FORMAT_SPECIFIER "%g"
#endif

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/* FIXME: You will write this function */
/**
  	Allocates the deque's sentinel and sets the size to 0.
  	The sentinel's next and prev should point to the sentinel itself.
 	param: 	deque 	struct CircularList ptr
	pre: 	deque is not null
	post: 	deque sentinel not null
			sentinel next points to sentinel
			sentinel prev points to sentinel
			deque size is 0
 */
static void init(struct CircularList* deque)
{
	/* allocate memory for the CircularList's sentinel */
	struct Link* sentinel = (struct Link*)malloc(sizeof(struct Link));

	/* point the CircularList's sentinel pointer to the above link/node for a sentinel */
	deque->sentinel = sentinel;

	/* update sentinel's value & pointers (sentinel's pointers: sentinel <- sentinel -> sentinel ) */
	sentinel->value = 0;
	sentinel->next = sentinel;
	sentinel->prev = sentinel;
}

/* FIXME: You will write this function */
/**
	Creates a link with the given value and NULL next and prev pointers.
	param: 	value 	TYPE
	pre: 	none
	post: 	newLink is not null
			newLink value init to value 
			newLink next and prev init to NULL
 */
static struct Link* createLink(TYPE value)
{
	/* create a new node/link */
	struct Link* node = (struct Link*)malloc(sizeof(struct Link));
	node->value = value;

	/* update pointers to NULL */
	node->next = NULL;
	node->prev = NULL;

	/* return the pointer to the node/link */
	return node;
}

/* FIXME: You will write this function */
/**
	Adds a new link with the given value after the given link and
	increments the deque's size.
	param: 	deque 	struct CircularList ptr
 	param:	link 	struct Link ptr
 	param: 	TYPE
	pre: 	deque and link are not null
	post: 	newLink is not null
			newLink w/ given value is added after param link
			deque size is incremented by 1
 */
static void addLinkAfter(struct CircularList* deque, struct Link* link, TYPE value)
{
	/* assert validations: deque & link are not NULL */
	assert(deque != 0);
	assert(link != 0);

	/* initialize the new node/link */
	struct Link* node = createLink(value);

	/* create a pointer to the other node/link that the new node/link must be inserted between */
	struct Link* temp = link->next;

	/* insert the new node/link & update pointers */
	link->next = node;
	temp->prev = node;
	node->next = temp;
	node->prev = link;

	/* increment the deque's size */
	deque->size += 1;
}

/* FIXME: You will write this function */
/**
	Removes the given link from the deque and decrements the deque's size.
	param: 	deque 	struct CircularList ptr
 	param:	link 	struct Link ptr
	pre: 	deque and link are not null
	post: 	param link is removed from param deque
			memory allocated to link is freed
			deque size is decremented by 1
 */
static void removeLink(struct CircularList* deque, struct Link* link)
{
	/* assert validations that deque and link are not NULL */
	assert(deque != 0);
	assert(link != 0);

	/* update the pointers of the nodes/links before/after the link that will be removed */
	link->next->prev = link->prev;
	link->prev->next = link->next;

	/* free the removed node/link's memory */
	free(link);

	/* decrement the deque's size by 1 */
	deque->size -= 1;
}

/**
	Allocates and initializes a deque.
	pre: 	none
	post: 	memory allocated for new struct CircularList ptr
			deque init (call to init func)
	return: deque
 */
struct CircularList* circularListCreate()
{
	struct CircularList* deque = (struct CircularList*)malloc(sizeof(struct CircularList));
	init(deque);
	return deque;
}

/* FIXME: You will write this function */
/**
	Deallocates every link in the deque and frees the deque pointer.
	pre: 	deque is not null
	post: 	memory allocated to each link is freed
			" " sentinel " "
			" " deque " "
 */
void circularListDestroy(struct CircularList* deque)
{
	/* assert to validate deque is not NULL */
	assert(deque != 0);

	/* point to the deque's first link/node (& create a temp pointer to a node/link for freeing each link/node's memory) */
	struct Link* node = deque->sentinel->next;
	struct Link* temp = deque->sentinel->next;

	/* iterate through the list & free each link/node */
	while (node != deque->sentinel)
	{
		node = node->next;
		free(temp);
		temp = node;
	}

	/* free the sentinel */
	free(deque->sentinel);

	/* free the pointer to the deque */
	free(deque);
}

/* FIXME: You will write this function */
/**
	Adds a new link with the given value to the front of the deque.
	param:	deque 	struct CircularList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created w/ given value before current first link
			(call to addLinkAfter)
 */
void circularListAddFront(struct CircularList* deque, TYPE value)
{
	/* assert to validate the deque is not NULL */
	assert(deque != 0);

	/* insert new node/link after the sentinel */
	addLinkAfter(deque, deque->sentinel, value);
}

/* FIXME: You will write this function */
/**
	Adds a new link with the given value to the back of the deque.
	param: 	deque 	struct CircularList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created w/ given value before current last link
			(call to addLinkAfter)
 */
void circularListAddBack(struct CircularList* deque, TYPE value)
{
	/* assert to validate the deque is not NULL */
	assert(deque != 0);

	/* insert a new node/link before the sentinel (after the last link/node) */
	addLinkAfter(deque, deque->sentinel->prev, value);
}

/* FIXME: You will write this function */
/**
	Returns the value of the link at the front of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	first link's value 
 */
TYPE circularListFront(struct CircularList* deque)
{
	/* assert to validate the deque is not NULL & the deque is not empty */
	assert(deque != 0);
	assert(deque->size > 0);

	return deque->sentinel->next->value;
}

/* FIXME: You will write this function */
/**
  	Returns the value of the link at the back of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	last link's value 
 */
TYPE circularListBack(struct CircularList* deque)
{
	/* assert to validate the deque is not NULL & the deque is not empty */
	assert(deque != 0);
	assert(deque->size > 0);

	return deque->sentinel->prev->value;
}

/* FIXME: You will write this function */
/**
	Removes the link at the front of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	first link is removed and freed (call to removeLink)
 */
void circularListRemoveFront(struct CircularList* deque)
{
	/* assert to validate the deque is not NULL & is not empty */
	assert(deque != 0);
	assert(deque->size > 0);

	/* remove the first link/node */
	removeLink(deque, deque->sentinel->next);
}

/* FIXME: You will write this function */
/**
	Removes the link at the back of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	last link is removed and freed (call to removeLink)
 */
void circularListRemoveBack(struct CircularList* deque)
{
	/* assert to validate the deque is not NULL & is not empty */
	assert(deque != 0);
	assert(deque->size > 0);

	/* remove the last link/node */
	removeLink(deque, deque->sentinel->prev);
}

/* FIXME: You will write this function */
/**
	Returns 1 if the deque is empty and 0 otherwise.
	param:	deque	struct CircularList ptr
	pre:	deque is not null
	post:	none
	ret:	1 if its size is 0 (empty), otherwise 0 (not empty)
 */
int circularListIsEmpty(struct CircularList* deque)
{
	/* assert to validate the deque is not NULL */
	assert(deque != 0);

	/* deque is NOT empty (sentinel does NOT point to itself (next & prev) */
	if (deque->sentinel->next != deque->sentinel && deque->sentinel->prev != deque->sentinel)
	{
		return 0;
	}

	/* deque IS empty */
	else
	{
		assert(deque->sentinel->next == deque->sentinel);
		assert(deque->sentinel->prev == deque->sentinel);
		return 1;
	}
}

/* FIXME: You will write this function */
/**
	Prints the values of the links in the deque from front to back.
	param:	deque	struct CircularList ptr
	pre:	deque is not null
	post:	none
	ret:	outputs to the console the values of the links from front 
			to back; if empty, prints msg that is empty
 */
void circularListPrint(struct CircularList* deque)
{
	/* assert to validate the deque is not NULL */
	assert(deque != 0);

	/* list is empty */
	if (circularListIsEmpty(deque))
	{
		printf("\nCircularLinkedList is empty...\n");
	}

	/* list is NOT empty */
	else
	{
		/* iterate through each of the list's nodes/links & print each value */
		struct Link* node = deque->sentinel->next;

		printf("\nPrinting the CircularLinkedList's values...\n");
		printf("CircularLinkedList: ");

		while (node != deque->sentinel)
		{
			/* print the node/link's value */
			printf("%.2f ", node->value);

			/* update the node/link that the pointer points to */
			node = node->next;
		}
	}
}

/* FIXME: You will write this function */
/**
	Reverses the deque in place without allocating any new memory.
	The process works as follows: current starts pointing to sentinel;
	tmp points to current's next, current's next points to current's prev,
	current's prev is assigned to tmp and current points to current's next
	(which points to current's prev), so you proceed stepping back through 
	the deque, assigning current's next to current's prev, until current 
	points to the sentinel then you know the each link has been looked at
	and the link order reversed.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	order of deque links is reversed
 */
void circularListReverse(struct CircularList* deque)
{
	/* assert to validate the deque is not NULL & is not empty */
	assert(deque != 0);
	assert(deque->size > 0);

	/* create the "current" and "tmp" (temp) pointers */
	struct Link* current = deque->sentinel;
	struct Link* tmp = current->next;

	/* iterate through the list's nodes/links */
	do
	{
		/* update pointers */
		current->next = current->prev;
		current->prev = tmp;
		tmp = current;

		/* point "current" to the next node/link */
		current = current->next;
	} while (current != deque->sentinel);
}
