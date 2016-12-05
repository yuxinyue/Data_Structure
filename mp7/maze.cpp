#include "maze.h"


SquareMaze::SquareMaze (){
	/*nothing*/
}
SquareMaze::~SquareMaze (){
	clear();
}
int myrandom (int i) { return std::rand()%i;}
void SquareMaze::makeMaze (int width, int height){
	// /srand(time(NULL));
	  std::srand ( unsigned ( std::time(0) ) );
	if(grid != NULL){
		clear();		
	}

	grid_width = width;
	grid_height = height;
	grid = new square*[width];
	for(int i = 0; i < width; i++){
		grid[i] = new square[height];
	}
	for(int x = 0; x < width; x++){
		for(int y=0; y < height; y++){
			grid[x][y].down = true;
			grid[x][y].right = true;
			x_axis = x;
			y_axis = y;
		}
	}

	DisjointSets set;
	set.addelements(width*height);

	vector<int> vec;

	for(int i = 0; i < width*height; i++){
		vec.push_back(i);
	}	

		//cout<<i<<endl;
	random_shuffle(vec.begin(), vec.end(),myrandom);
	for(int i = 0; i < (int)vec.size(); i++){
		int idx = vec[i];
		int x = idx % width;
		int y = idx / width;
		int idx_down = (y+1)*width + x;
		if (y<height-1){//added by txu25
			if(set.find(idx) != set.find(idx_down)){
				grid[x][y].down = false;
				set.setunion(idx, idx_down);
			}
		}
		int idx_right = idx + 1;
		if (x < width-1){ //added by txu25
			if(set.find(idx) != set.find(idx_right)){
				grid[x][y].right = false;
				set.setunion(idx, idx_right);
			}
		}
	}	
}

bool SquareMaze::canTravel (int x, int y, int dir) const{
	if(dir == 0){
		if(x+1 >= grid_width) return false;
		return !grid[x][y].right;
	}
	else if(dir == 1){
		if(y + 1 >= grid_height) return false;
		return !grid[x][y].down;
	}
	else if(dir == 2){
		if(x-1 < 0) return false;
		return !grid[x-1][y].right;
	}
	else{
		if(y - 1 < 0) return false;
		return !grid[x][y-1].down;
	}

}
void SquareMaze::setWall (int x, int y, int dir, bool exists){
	if(dir == 0)
	grid[x][y].right = exists;
	if(dir == 1)
	grid[x][y].down = exists;
}
vector<int> SquareMaze::solveMaze (){
	//vector<int> * best_vec;
	int best_dis = 0;

	vector<int> vec;
	for(int i = 0; i < grid_width; i++){
		square start = grid[0][0];
		square end = grid[i][height-1];
		queue<square> q;
		q.push(start);
		int dis = 0;
		while(! q.empty()){
			square curr = q.front();
			q.pop();
			if()
		}

	}
}

PNG* SquareMaze::drawMaze () const{

	if(grid == NULL) return new PNG();
	int image_width = grid_width * 10 + 1;
	int image_height = grid_height * 10 + 1;
	PNG* image = new PNG(image_width, image_height);

	(*image)(0, 0)->red = 0;
	(*image)(0, 0)->green = 0;
	(*image)(0, 0)->blue = 0;

	for(int i = 10; i < image_width; i++){
		(*image)(i, 0)->red = 0;
		(*image)(i, 0)->green = 0;
		(*image)(i, 0)->blue = 0;
	}

	for(int j = 0; j < image_height; j++){
		(*image)(0, j)->red = 0;
		(*image)(0, j)->green = 0;
		(*image)(0, j)->blue = 0;
	}

	for(int x = 0; x < grid_width; x++){
		for(int y = 0; y < grid_height; y++){
			if(grid[x][y].right){
				for(int j = 0; j <= 10; j++){
					(*image)((x+1)*10, y*10+j)->red = 0;
					(*image)((x+1)*10, y*10+j)->green = 0;
					(*image)((x+1)*10, y*10+j)->blue = 0;
				}
			}
			if(grid[x][y].down){
				for(int i = 0; i <= 10; i++){
					(*image)(x*10+i, (y+1)*10)->red = 0;
					(*image)(x*10+i, (y+1)*10)->green = 0;
					(*image)(x*10+i, (y+1)*10)->blue = 0;					
				}
			}
		}
	}

	return image; 
}


PNG* SquareMaze::drawMazeWithSolution (){
	return new PNG();
}

void SquareMaze::clear(){
	for(int i = 0; i < grid_width; i++){
		delete [] grid[i];
		grid[i] = NULL;
	}
	delete [] grid;
	grid = NULL;	
}

 