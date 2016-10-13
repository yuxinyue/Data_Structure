#include "linkedlist.h"

void merge(LinkedList* lst1,
           LinkedList* lst2,
           LinkedList* mrg)
{
	// YOUR CODE HERE!
	Node * curr;
	Node * first = lst1.head;
	Node * second = lst2.head;
	if(lst1.head->data < lst2.head->data)
	{
		mrg.head = lst1.head;	
		first = first->next;
	}
	else
	{
		mrg.head = lst2.head;
		second = second->next;
	}
		curr = mrg.head;
	if(first->data < second->data)
	{
		curr->next = first;
		first = first->next;
	}
	else
	{
		curr->next = second;
		second = second->next;	
	}
	return;
}
