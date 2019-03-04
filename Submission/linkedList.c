/***********************************************************
* Author: Ryan DiRezze
* Email: direzzer@oregonstate.edu
* Date Created: 2/11/19
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

/* FIXME: You will write this function */
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

/* FIXME: You will write this function */
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

	/* insert the new node & update pointers of nodes within the list */
	node->next = link;
	temp->next = node;
	assert(temp->next == node && node->next == link);

	link->prev = node;
	node->prev = temp;
	assert(link->prev == node && node->prev == temp);

	/* increase the LL's size by 1 */
	list->size += 1;
}

/* FIXME: You will write this function */
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
	assert(link != list->frontSentinel && link != list->backSentinel);
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

/* FIXME: You will write this function */
/**
	Adds a new link with the given value to the front of the deque.
	param: 	deque 	struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created w/ param value stored before current first link
			(call to addLinkBefore)
 */
void linkedListAddFront(struct LinkedList* deque, TYPE value)
{
	/* assertion for validation (deque is not NULL) */
	assert(deque != 0);

	/* temp pointer that represents the first node/link (non-sentinel) */
	struct Link* temp = deque->frontSentinel->next;

	/* insert the node */
	addLinkBefore(deque, temp, value);
}

/* FIXME: You will write this function */
/**
	Adds a new link with the given value to the back of the deque.
	param: 	deque 	struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created with given value before current last link
			(call to addLinkBefore)
 */
void linkedListAddBack(struct LinkedList* deque, TYPE value)
{
	/* assertion for validation (deque is not NULL) */
	assert(deque != 0);

	/* node that points to the deque's back sentinel */
	struct Link* temp = deque->backSentinel;

	/* insert the node */
	addLinkBefore(deque, temp, value);
}

/* FIXME: You will write this function */
/**
	Returns the value of the link at the front of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	first link's value 
 */
TYPE linkedListFront(struct LinkedList* deque)
{
	/* assertions for validation (deque is not NULL & deck is not empty) */
	assert(deque != 0);
	assert(deque->size > 0);

	/* return the first node's value in the list (deque) */
	return deque->frontSentinel->next->value;
}

/* FIXME: You will write this function */
/**
	Returns the value of the link at the back of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	last link's value 
 */
TYPE linkedListBack(struct LinkedList* deque)
{
	/* assertions for validation (deque is not NULL & deque is not empty) */
	assert(deque != 0);
	assert(deque->size > 0);

	/* return the last node's value in the list (deque) */
	return deque->backSentinel->prev->value;
}

/* FIXME: You will write this function */
/**
	Removes the link at the front of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	first link is removed and freed (call to removeLink)
 */
void linkedListRemoveFront(struct LinkedList* deque)
{
	/* assertions for validation (deque is not NULL & deque is not empty) */
	assert(deque != 0);
	assert(deque->size > 0);

	/* variable that points to the first node in the list (deque) */
	struct Link* front = deque->frontSentinel->next;

	/* remove the front node/link */
	removeLink(deque, front);
}

/* FIXME: You will write this function */
/**
	Removes the link at the back of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	last link is removed and freed (call to removeLink)
 */
void linkedListRemoveBack(struct LinkedList* deque)
{
	/* assertions for validation (deque is not NULL & deque is not empty) */
	assert(deque != 0);
	assert(deque->size > 0);

	/* point to the last (non-sentinel) node in the deque */
	struct Link* last = deque->backSentinel->prev;

	/* remove the last node/link */
	removeLink(deque, last);
}

/* FIXME: You will write this function */
/**
	Returns 1 if the deque is empty and 0 otherwise.
	param:	deque	struct LinkedList ptr
	pre:	deque is not null
	post:	none
	ret:	1 if its size is 0 (empty), otherwise 0 (not empty)
 */
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

/* FIXME: You will write this function */
/**
	Prints the values of the links in the deque from front to back.
	param:	deque	struct LinkedList ptr
	pre:	deque is not null
	post:	none
	ret:	outputs to the console the values of the links from front 
			to back; if empty, prints msg that is empty
 */
void linkedListPrint(struct LinkedList* deque)
{
	/* assertion to validate the deque is not NULL */
	assert(deque != 0);

	/* list is NOT empty */
	if (!linkedListIsEmpty(deque))
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

/* FIXME: You will write this function */
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
	/* assertion to validate the bag is not NULL */
	assert(bag != 0);

	/* insert the new node (link) at the beginning of the bag's linked list */
	addLinkBefore(bag, bag->frontSentinel->next, value);
}

/* FIXME: You will write this function */
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
	/* assertion to validate the bag is not NULL */
	assert(bag != 0);

	/* point to the a node within the bag/linkedlist */
	struct Link* node = bag->frontSentinel->next;

	/* iterate through the linked list's nodes (links) to search for a specific value */
	while (node->next != 0 && node->next != bag->backSentinel)
	{
		/* node/link value equals the searched-for value */
		if (node->value == value)
		{
			return 1;
		}

		/* update the node's value to the next node */
		node = node->next;
	}
	
	/* value is not in the linked list */
	return 0;
}

/* FIXME: You will write this function */
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
	/* assert to validate the bag is not NULL */
	assert(bag != 0);

	/* bag contains the specific value */
	if (linkedListContains(bag, value))
	{
		/* point to the frontSentinel */
		struct Link* node = bag->frontSentinel->next;

		/* flag to end the below loop (and this function) is triggered */
		int nodeFound = 0;		// initial value of 0 == false

		/* find the node/link with the searched-for value (terminates this loop and function when the value is found) */
		while (nodeFound == 0 && (node->next != 0 && node->next != bag->backSentinel))
		{
			/* node/link contains the searched-for value */
			if (node->value == value)
			{
				/* remove the node/link */
				removeLink(bag, node);

				/* trigger the nodeFound flag to terminate this loop & function */
				nodeFound = 1;
			}
			
			node = node->next;
		}
	}
}
