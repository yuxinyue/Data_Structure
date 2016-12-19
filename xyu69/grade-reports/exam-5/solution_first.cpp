#include <iostream>
#include <set>
#include <string>
#include <map>
#include <queue>

using namespace std;
using std::set;

/* STL Sets have several methods you may (or may not) need:
 *
 * begin() -- return iterator from beginning
 * count(x) -- return number of instances of x in the set (will be 0 or 1)
 * insert(x) -- insert an element x into the set
 * erase(x) -- remove an element x from the set
 * empty() -- test if the set is empty
 * size() -- return number of elements in set
 */


set<string> findNeighbors(string curr,  set<string>& wordList)
{
    set<string> neighbors;
    int N = curr.size();
    for(int i = 0; i < N; i++)
    {
        for(char c = 'a'; c <= 'z'; c++)
        {
            if(c == curr[i])
                continue;
            string oneChange = curr.substr(0,i) + (c) + curr.substr(i+1);
            if(wordList.count(oneChange))
            {
                neighbors.insert(oneChange);
                wordList.erase(oneChange);
            }
        }
    }
    return neighbors;
}

int sequenceLength(string beginWord, string endWord, set<string>& wordList) {

	map<string, bool> visited;
	map<string, int> dis;
	queue<string> q;
	
	for(auto s = wordList.begin(); s != wordList.end(); s++){
		visited[*s] = false;
	}
	q.push(beginWord);
	visited[beginWord] = true;
	dis[beginWord] = 1;

	while(!q.empty()){
		string curr = q.front();
		q.pop();
		if(curr == endWord){
			return dis[curr];
		}
		set<string> neiSet = findNeighbors(curr, wordList); 
		for(auto n = neiSet.begin(); n != neiSet.end(); n++){
			if(! visited[*n]){
				visited[*n] = true;
				dis[*n] = dis[curr] + 1;
				q.push(*n);
			}
		}
	}
    return -1;
}
