#include <iostream>
#include <vector>
#include <set>
using namespace std;

int find(vector<int> &uptree, int index)
{
    // Your code here!
	if(uptree[index] == index){
		return index;
	}
	return uptree[index] = find(uptree, uptree[index]);
}

