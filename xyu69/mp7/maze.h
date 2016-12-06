#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include <time.h>
#include <algorithm>
#include <random>
#include "png.h"
#include "dsets.h"
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <queue>
#include <unordered_map>
#include <map>
#include <stack>

#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
using namespace std;



class SquareMaze{
 	   
public: 	   
	SquareMaze ();
	~SquareMaze ();
	void makeMaze (int width, int height);
	bool canTravel (int x, int y, int dir) const;
	void setWall (int x, int y, int dir, bool exists);
	vector<int> solveMaze ();

	PNG* drawMaze () const; 
	PNG* drawMazeWithSolution ();
	
private:
	class square{
	public:
		bool down;
		bool right;
		int  x_axis;
		int  y_axis;
		bool operator==(const square  & other) const{
			return this->x_axis == other.x_axis && this->y_axis == other.y_axis;
		}

		bool operator<(const square  & other ) const{
			if(x_axis<other.x_axis) return true;
			if (x_axis==other.x_axis && y_axis>other.y_axis) return true;
			return false;
		}
		bool operator>(const square  & other ) const{
			if(x_axis>other.x_axis) return true;
			if (x_axis==other.x_axis && y_axis<other.y_axis) return true;
			return false;
		}
	};
		square** grid;
		int grid_width;
		int grid_height;

		void clear();
	
};
#endif