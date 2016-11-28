/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num){
	for(int i = 0; i < num; i++){
	vec.push_back(-1);
	}
}

int DisjointSets::find(int elem){
	if(vec[elem] < 0) return elem;
	return vec[elem] = find(vec[elem]);
}

void DisjointSets::setunion(int a, int b){
	int root1 = find(a);
	int root2 = find(b);
	int size = vec[root1] + vec[root2];
//second points to first
	if(vec[root1] <= vec[root2]){
		vec[root2] = root1;
		vec[root1] = size;
	}
	else{
		vec[root1] = root2;
		vec[root2] = size;
	}
}