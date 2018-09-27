// rearrangeLastN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stack>

template<typename T>
struct ListNode {
	ListNode(const T &v) : value(v), next(nullptr) {}
	T value;
	ListNode *next;
};
ListNode<int>* createList(int a[], int n);
ListNode<int> * rearrangeLastN(ListNode<int> * l, int n);

int main()
{
	int arr1[] = { 0,1,2,3,4,5,6 };
	ListNode<int>* head1 = createList(arr1, sizeof(arr1) / sizeof(int));

	ListNode<int> *ret = rearrangeLastN(head1, 1);
    return 0;
}

ListNode<int>* createList(int a[], int n)
{
	ListNode<int> *head = NULL, *p = NULL;
	for (int i = 0; i < n; i++) {
		if (head == NULL) {
			head = p = new ListNode<int>(a[i]);
		}
		else {
			p->next = new ListNode<int>(a[i]);
			p = p->next;
		}
	}
	return head;
}

ListNode<int> * rearrangeLastN(ListNode<int> * l, int n) {
	if (l == NULL || l->next == NULL) return l;

	int count = 0;
	ListNode<int> * current = l;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	if (count == n) return l;
	int lastElement = count - n;
	current = l;
	for (int i = 0; i < lastElement - 1; i++)
	{
		current = current->next;
	}
	ListNode<int>* last = current;

	std::stack<ListNode<int>*> st;
	current = current->next;
	while (current != NULL)
	{
		st.push(current);
		current = current->next;
	}

	current = l;
	ListNode<int> * newNode;
	while (!st.empty())
	{
		newNode = st.top();
		newNode->next = current;
		current = newNode;
		st.pop();
	}
	last->next = NULL;
	return current;
}