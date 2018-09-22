// addTwoHugeNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 
#include <stdlib.h>

template<typename T>
 struct ListNode {
   ListNode(const T &v) : value(v), next(nullptr) {}
   T value;
   ListNode *next;
 };

 // Definition for singly-linked list:
 // template<typename T>
 // struct ListNode<int> {
 //   ListNode<int>(const T &v) : value(v), next(nullptr) {}
 //   T value;
 //   ListNode<int> *next;
 // };
 //

 void push(struct ListNode<int>** head_ref, int new_data);
 void printList(struct ListNode<int> *node);
 void swapPointer(ListNode<int>** a, ListNode<int>** b);
 int getSize(struct ListNode<int> *node);
 ListNode<int>* addSameSize(ListNode<int>* head1, ListNode<int>* head2, int* carry);
 void addCarryToRemaining(ListNode<int>* head1, ListNode<int>* cur, int* carry, ListNode<int>** result);
 void addTwoHugeNumbers(ListNode<int> * head1, ListNode<int> * head2, ListNode<int>** result);
 
int main()
{
	ListNode<int> *head1 = NULL, *head2 = NULL, *result = NULL;

	int arr1[] = { 9876, 5432, 1999 };
	int arr2[] = { 1, 8001 };
	//[9876, 5434, 0]
	int size1 = sizeof(arr1) / sizeof(arr1[0]);
	int size2 = sizeof(arr2) / sizeof(arr2[0]);

	// Create first list as 9->9->9 
	int i;
	for (i = size1 - 1; i >= 0; --i)
		push(&head1, arr1[i]);

	// Create second list as 1->8 
	for (i = size2 - 1; i >= 0; --i)
		push(&head2, arr2[i]);

	addTwoHugeNumbers(head1, head2, &result);

	printList(result);
    return 0;
}

/* A utility function to insert a node at the beginning of linked list */
void push(struct ListNode<int>** head_ref, int new_data)
{
	/* allocate node */
	struct ListNode<int>* new_node = (struct ListNode<int>*) malloc(sizeof(struct ListNode<int>));

	/* put in the data  */
	new_node->value = new_data;

	/* link the old list off the new node */
	new_node->next = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

/* A utility function to print linked list */
void printList(struct ListNode<int> *node)
{
	while (node != NULL)
	{
		printf("%d  ", node->value);
		node = node->next;
	}
	printf("n");
}

// A utility function to swap two pointers 
void swapPointer(ListNode<int>** a, ListNode<int>** b)
{
	ListNode<int>* t = *a;
	*a = *b;
	*b = t;
}

/* A utility function to get size of linked list */
int getSize(struct ListNode<int> *node)
{
	int size = 0;
	while (node != NULL)
	{
		node = node->next;
		size++;
	}
	return size;
}

// Adds two linked lists of same size represented by head1 and head2 and returns 
// head of the resultant linked list. Carry is propagated while returning from 
// the recursion 
ListNode<int>* addSameSize(ListNode<int>* head1, ListNode<int>* head2, int* carry)
{
	// Since the function assumes linked lists are of same size, 
	// check any of the two head pointers 
	if (head1 == NULL)
		return NULL;

	int sum;

	// Allocate memory for sum node of current two nodes 
	ListNode<int>* result = (ListNode<int> *)malloc(sizeof(ListNode<int>));

	// Recursively add remaining nodes and get the carry 
	result->next = addSameSize(head1->next, head2->next, carry);

	// add digits of current nodes and propagated carry 
	sum = head1->value + head2->value + *carry;
	*carry = sum / 10;
	sum = sum % 10;

	// Assigne the sum to current node of resultant list 
	result->value = sum;

	return result;
}

// This function is called after the smaller list is added to the bigger 
// lists's sublist of same size.  Once the right sublist is added, the carry 
// must be added toe left side of larger list to get the final result. 
void addCarryToRemaining(ListNode<int>* head1, ListNode<int>* cur, int* carry, ListNode<int>** result)
{
	int sum;

	// If diff. number of nodes are not traversed, add carry 
	if (head1 != cur)
	{
		addCarryToRemaining(head1->next, cur, carry, result);

		sum = head1->value + *carry;
		*carry = sum / 10;
		sum %= 10;

		// add this node to the front of the result 
		push(result, sum);
	}
}
void addTwoHugeNumbers(ListNode<int> * head1, ListNode<int> * head2, ListNode<int>** result) {
	ListNode<int> *cur;
	//ListNode<int>* result;
	// first list is empty 
	if (head1 == NULL)
	{
		*result = head2;
		return;
	}

	// second list is empty 
	else if (head2 == NULL)
	{
		*result = head1;
		return;
	}

	int size1 = getSize(head1);
	int size2 = getSize(head2);

	int carry = 0;

	// Add same size lists 
	if (size1 == size2)
		*result = addSameSize(head1, head2, &carry);

	else
	{
		int diff = abs(size1 - size2);

		// First list should always be larger than second list. 
		// If not, swap pointers 
		if (size1 < size2)
			swapPointer(&head1, &head2);

		// move diff. number of nodes in first list 
		for (cur = head1; diff--; cur = cur->next);

		// get addition of same size lists 
		*result = addSameSize(cur, head2, &carry);

		// get addition of remaining first list and carry 
		addCarryToRemaining(head1, cur, &carry, result);
	}

	// if some carry is still there, add a new node to the fron of 
	// the result list. e.g. 999 and 87 
	if (carry)
		push(result, carry);

	//return result;
}