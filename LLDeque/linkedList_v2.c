/***********************************************************
* Author: Ryan DiRezze
* Email: direzzer@oregonstate.edu
* Date Created: 1/28/19
* Filename: linkedList.c
*
* Overview:
*   This program is a linked list implementation of the deque 
*	(as worked on in Worksheet 19) and bag (as worked on in 
*	Worksheet 22) ADTs. 
*	The deque ADT allows for the following behavior:
*		- adding a new link to the front/back
*		- getting the value of the front/back links
*		- removing the front/back link
*	The bag ADT allows for the following behavior:
*		- adding a new link
*		- checking if a link exists with a given value
*		- removing a link  with a given value if it exists
*	Both allow for:
*		- checking if empty
*		- printing the values of all of the links
*
*	Note that both implementations utilize a linked list with
*	both a front and back sentinel and double links (links with
*	next and prev pointers).
************************************************************/
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef FORMAT_SPECIFIER
#define FORMAT_SPECIFIER "%d"
#endif

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	struct Link* frontSentinel;
	struct Link* backSentinel;
	int size;
};

/**
  	Allocates the list's sentinel and sets the size to 0.
  	The sentinels' next and prev should point to eachother or NULL
  	as appropriate.
	param: 	list 	struct LinkedList ptr
	pre: 	list is not null
	post: 	list front and back sentinel not null
			front sentinel next points to back
			front sentinel prev points to null
			back sentinel prev points to front
			back sentinel next points to null
			list size is 0
 */
 /* FIXME: You will write this function */
static void init(struct LinkedList* list) 
{
	/* validate list != NULL */
	assert(list != 0);

	/* allocate memory for both sentinels */
	struct Link* fSentinel = (struct Link*)malloc(sizeof(struct Link));
	struct Link* bSentinel = (struct Link*)malloc(sizeof(struct Link));

	/* point LL sentinel pointers to the proper memory addresses */
	list->frontSentinel = fSentinel;
	list->backSentinel = bSentinel;

	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;

	/* update sentinel and list values */
	list->frontSentinel->value = 0;
	list->backSentinel->value = 0;
	list->size = 0;
}

/**
 	Adds a new link with the given value before the given link and
	increments the list's size.
 	param: 	list 	struct LinkedList ptr
 	param:	link 	struct Link ptr
 	param: 	TYPE
	pre: 	list and link are not null
	post: 	newLink is not null
			newLink w/ given value is added before param link
			list size is incremented by 1
 */
 /* FIXME: You will write this function */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	/* assertions for validation */
	assert(list != 0);
	assert(link != 0);

	/* initialize a new node, which will be inserted into the LL */
	struct Link* node = (struct Link*)malloc(sizeof(struct Link));
	node->value = value;

	/* find the node that the new node must be inserted immediately before */
	struct Link* temp = list->frontSentinel;
	while (temp->next != link)
	{
		temp = temp->next;
	}

	/* insert the new node */
	node->next = link;
	temp->next = node;
	assert(temp->next == node && node->next == link);

	link->prev = node;
	node->prev = temp;
	assert(link->prev == node && node->prev == temp);

	/* increase the LL's size by 1 */
	list->size += 1;
}

/**
	Removes the given link from the list and
	decrements the list's size.
	param: 	list 	struct LinkedList ptr
 	param:	link 	struct Link ptr
	pre: 	list and link are not null
	post: 	param link is removed from param list
			memory allocated to link is freed
			list size is decremented by 1
 */
 /* FIXME: You will write this function */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	/* assertions for validation (list & link are not NULL */
	assert(list != 0);
	assert(link != 0);

	/* temp pointer to the front sentinel */
	struct Link* temp = list->frontSentinel;

	/* find the node that needs to be removed */
	while (temp->next != link)
	{
		temp = temp->next;
	}

	assert(temp->next == link && link->prev == temp);

	/* re-point node pointers */
	temp->next = link->next;
	link->next->prev = temp;

	/* free the removed node */
	free(link);
	list->size -= 1;
}

/**
	Allocates and initializes a list.
	pre: 	none
	post: 	memory allocated for new struct LinkedList ptr
			list init (call to init func)
	return: list
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* list = malloc(sizeof(struct LinkedList));
	init(list);
	return list;
}

/**
	Deallocates every link in the list including the sentinels,
	and frees the list itself.
	param:	list 	struct LinkedList ptr
	pre: 	list is not null
	post: 	memory allocated to each link is freed
			" " front and back sentinel " "
			" " list " "
 */
void linkedListDestroy(struct LinkedList* list)
{
	assert(list != NULL);
	while (!linkedListIsEmpty(list)) {
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
	list = NULL;
}

/**
	Adds a new link with the given value to the front of the deque.
	param: 	deque 	struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created w/ param value stored before current first link
			(call to addLinkBefore)
 */
 /* FIXME: You will write this function */
void linkedListAddFront(struct LinkedList* deque, TYPE value)
{
	/* assertion for validation (deque is not NULL) */
	assert(deque != 0);

	/* initialize a new node */
	struct Link* node = (struct Link*)malloc(sizeof(struct Link));
	node->value = value;

	/* temp pointer that represents the front sentinel */
	struct Link* temp = deque->frontSentinel;
	
	/* update node pointers */
	temp->next->prev = node;
	node->next = temp->next;
	temp->next = node;
	node->prev = temp;

	/* update deque's size */
	deque->size += 1;
}

/**
	Adds a new link with the given value to the back of the deque.
	param: 	deque 	struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created with given value before current last link
			(call to addLinkBefore)
 */
 /* FIXME: You will write this function */
void linkedListAddBack(struct LinkedList* deque, TYPE value)
{
	/* assertion for validation (deque is not NULL) */
	assert(deque != 0);

	/* initialize the new node */
	struct Link* node = (struct Link*)malloc(sizeof(struct Link));
	node->value = value;

	/* node that points to the deque's back sentinel */
	struct Link* temp = deque->backSentinel;

	/* re-point node pointers */
	temp->prev->next = node;
	node->prev = temp->prev;
	temp->prev = node;
	node->next = temp;

	/* update the deque's size */
	deque->size += 1;
}

/**
	Returns the value of the link at the front of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	first link's value 
 */
 /* FIXME: You will write this function */
TYPE linkedListFront(struct LinkedList* deque)
{
	/* assertions for validation (deque is not NULL & deck is not empty) */
	assert(deque != 0);
	assert(deque->size > 0);

	/* return the first node's value in the list (deque) */
	return deque->frontSentinel->next->value;
}

/**
	Returns the value of the link at the back of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	last link's value 
 */
 /* FIXME: You will write this function */
TYPE linkedListBack(struct LinkedList* deque)
{
	/* assertions for validation (deque is not NULL & deque is not empty) */
	assert(deque != 0);
	assert(deque->size > 0);

	/* return the last node's value in the list (deque) */
	return deque->backSentinel->prev->value;
}

/**
	Removes the link at the front of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	first link is removed and freed (call to removeLink)
 */
 /* FIXME: You will write this function */
void linkedListRemoveFront(struct LinkedList* deque)
{
	/* assertions for validation (deque is not NULL & deque is not empty) */
	assert(deque != 0);
	assert(deque->size > 0);

	/* variable that points to the first node in the list (deque) */
	struct Link* front = deque->frontSentinel->next;

	/* re-point frontSentinel & the 2nd node's pointers so that the 2nd node is now the 1st node */
	front->next->prev = deque->frontSentinel;
	deque->frontSentinel->next = front->next;

	/* free memory of the removed node & update the deque's size */
	free(front);
	deque->size -= 1;
}

/**
	Removes the link at the back of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	last link is removed and freed (call to removeLink)
 */
 /* FIXME: You will write this function */
void linkedListRemoveBack(struct LinkedList* deque)
{
	/* assertions for validation (deque is not NULL & deque is not empty) */
	assert(deque != 0);
	assert(deque->size > 0);

	/* point to the last (non-sentinel) node in the deque */
	struct Link* last = deque->backSentinel->prev;

	/* re-point next (backSentinel) & prev node pointers to remove the last node from the deque */
	last->prev->next = deque->backSentinel;
	deque->backSentinel->prev = last->prev;

	/* free the removed node's memory & update deque's size */
	free(last);
	deque->size -= 1;
}

/**
	Returns 1 if the deque is empty and 0 otherwise.
	param:	deque	struct LinkedList ptr
	pre:	deque is not null
	post:	none
	ret:	1 if its size is 0 (empty), otherwise 0 (not empty)
 */
 /* FIXME: You will write this function */
int linkedListIsEmpty(struct LinkedList* deque)
{
	/* validate the deque is not NULL */
	assert(deque != 0);

	/* deque is empty */
	if (deque->frontSentinel->next == deque->backSentinel && deque->backSentinel->prev == deque->frontSentinel)
	{
		return 1;
	}

	/* deque is NOT empty */
	else
	{
		return 0;
	}
}

/**
	Prints the values of the links in the deque from front to back.
	param:	deque	struct LinkedList ptr
	pre:	deque is not null
	post:	none
	ret:	outputs to the console the values of the links from front 
			to back; if empty, prints msg that is empty
 */
 /* FIXME: You will write this function */
void linkedListPrint(struct LinkedList* deque)
{
	/* assertion to validate the deque is not NULL */
	assert(deque != 0);

	/* list is NOT empty */
	if (linkedListIsEmpty(deque))
	{
		/* point to the frontSentinel & iterate through the list while printing node values */
		struct Link* link = deque->frontSentinel->next;

		printf("Printing the deque's list of values...\n");
		while (link != deque->backSentinel)
		{
			printf("%d ", link->value);
			link = link->next;
		}
		printf("\n");
	}

	/* list is empty */
	else
	{
		printf("Deque's list is empty...\n");
	}
}

/**
	Adds a link with the given value to the bag.
	param:	bag		struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	bag is not null
	post: 	link is created w/ given value before current first link
			(call to addLinkBefore)
			Note that bag doesn't specify where new link should be added;
			can be anywhere in bag according to its ADT.
 */
void linkedListAdd(struct LinkedList* bag, TYPE value)
{
	/* FIXME: You will write this function */
}

/**
	Returns 1 if a link with the value is in the bag and 0 otherwise.
	param:	bag		struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	bag is not null
	post:	none
	ret:	1 if link with given value found; otherwise, 0
 */
int linkedListContains(struct LinkedList* bag, TYPE value)
{

	/* FIXME: You will write this function */
}

/**
	Removes the first occurrence of a link with the given value.
	param:	bag		struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	bag is not null
	post:	if link with given value found, link is removed
			(call to removeLink)
 */
void linkedListRemove(struct LinkedList* bag, TYPE value)
{
	/* FIXME: You will write this function */
}
