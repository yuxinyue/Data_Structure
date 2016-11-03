#include "common.h"
#include <iostream>
#include <queue>

/*
  As a reminder, useful STL queue methods include:
  empty : Test whether container is empty (public member function)
  size : Return size (public member function)
  front : Access next element (public member function)
  push : Insert element (public member function)
  pop : Remove next element (public member function)
*/

using namespace std;

int insertAt(queue<int> &q, int data, int pos)
{
	// YOUR CODE HERE!
	int size = q.size();
	if((pos >= 0) && (pos <= size)){
		if(pos == size){
			q.push(data);
		}else{
		for(int i = 0; i < size; i++){
			if(i == pos){
				q.push(data);
			}
			q.push(q.front());
			q.pop();
		}
		}
	return 1;
	} 
	else return -1;
}
