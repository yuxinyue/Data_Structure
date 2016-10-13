#include "linkedlist.h"
#include <iostream>
using namespace std;

bool addAt(LinkedList &mylist, int pos, int newdata)
{
	// YOUR CODE HERE!
	Node * add = new Node(newdata);
	Node * curr = mylist.head;
	if (curr->next != NULL)
	{
		for(int i = 0; i < pos-1; i++)
		{
			curr = curr->next;	
		}
	add->next = curr->next;
	curr->next = add;
	return 1;
	}
	else
	{
	return 0;
	}
}
