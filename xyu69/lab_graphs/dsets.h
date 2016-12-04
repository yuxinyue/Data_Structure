/* Your code here! */
#ifndef DISJOINTSETS_H 
#define DISJOINTSETS_H

#include <vector>
using namespace std;

class DisjointSets{
	public:
		void addelements(int num);
		int find(int elem);
		void setunion(int a, int b);			
	private:
		vector<int> vec;
};

#endif







