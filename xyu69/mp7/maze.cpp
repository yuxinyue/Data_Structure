#include "maze.h"
#define mp make_pair


/*
bool SquareMaze::operater==(square  & other);
	{
		return this->x_axis == otehr.x_axis && this->y_axis == other.y_axis;
	}
*/
SquareMaze::SquareMaze (){
	/*nothing*/
	grid = NULL;
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
			grid[x][y].x_axis = x;
			grid[x][y].y_axis = y;
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
	square theEnd;
	vector<int> vec;
	stack<int> s;
	square curr_s;
		square start = grid[0][0];   
		queue<square> q;
		q.push(start);
		map<square, int> dis;
		map<square, square> preSquare;
		map<pair<int,int>, bool> visited;
		map<square, int> preDir;
        
		for(int i = 0; i < grid_width; i++){
			for(int j = 0; j < grid_height; j++){
				visited[mp(i,j)] = false;
			}
		}
		visited[mp(0,0)] = true;
		//cout<<__LINE__<<endl;
		while(! q.empty()){
			square curr = q.front();
			q.pop();
			//cout<<curr.x_axis<<" "<<curr.y_axis<<endl;

			if(canTravel(curr.x_axis, curr.y_axis, 0) && !visited[mp(curr.x_axis + 1,curr.y_axis)]){
				square next0 = grid[curr.x_axis + 1][curr.y_axis];	
				q.push(next0);
				visited[mp(curr.x_axis + 1,curr.y_axis)] = true;
				preSquare[next0] = curr;
				preDir[next0] = 0;
				dis[next0] = dis[curr] + 1;
				//cout<<0<<endl;
			}
			if(canTravel(curr.x_axis, curr.y_axis, 1) && !visited[mp(curr.x_axis,curr.y_axis + 1)]){
				square next1 = grid[curr.x_axis][curr.y_axis + 1];
				q.push(next1);
				visited[ mp(curr.x_axis,curr.y_axis + 1)] = true;
				preSquare[next1] = curr;
				preDir[next1] = 1;
				dis[next1] = dis[curr] + 1;
				//cout<<1<<endl;
			}

			if(canTravel(curr.x_axis, curr.y_axis, 2) && !visited[mp(curr.x_axis - 1,curr.y_axis)]){
				square next2 = grid[curr.x_axis - 1][curr.y_axis];
				q.push(next2);
				visited[mp(curr.x_axis - 1,curr.y_axis)] = true;
				preSquare[next2] = curr;
				preDir[next2] = 2;
				dis[next2] = dis[curr] + 1;
				//cout<<2<<endl;
			}
			if(canTravel(curr.x_axis, curr.y_axis, 3) && !visited[mp(curr.x_axis,curr.y_axis - 1)]){
				square next3 = grid[curr.x_axis][curr.y_axis - 1];
				q.push(next3);
				visited[mp(curr.x_axis,curr.y_axis - 1)] = true;
				preSquare[next3] = curr;
				preDir[next3] = 3;
				dis[next3] = dis[curr] + 1;
				//cout<<3<<endl;
			}
			//getchar();
		}
		//cout<<__LINE__<<endl;
		for(int i = 0; i < grid_width; i++){
			square end = grid[i][grid_height - 1];
			//cout<<end.x_axis<<" "<<end.y_axis<<" "<<dis[end]<<endl;
			if(dis[end] > best_dis){
				best_dis = dis[end];
				theEnd = end;
	    	}
			if(dis[end] == best_dis){
				if(end.x_axis < theEnd.x_axis){
					theEnd = end;
				}
			}
		}	
	//cout<<__LINE__<<endl;
	curr_s = theEnd;
	//cout<<start.x_axis<<" "<<start.y_axis<<endl;
	//cout<<curr_s.x_axis<<" "<<curr_s.y_axis<<endl;
	while(!( curr_s == start)){
		s.push(preDir[curr_s]);
		curr_s = preSquare[curr_s];
	}
	while(!s.empty()){
		vec.push_back(s.top());
		s.pop();
	}
	//cout<<"Solution:"<<endl;
	//for (int i =0;i<(int)vec.size();i++)
		//cout<<vec[i]<<endl;
	return vec;
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

void SquareMaze::setRed(PNG & image, int x, int y){
	image(x,y)->red = 255;
	image(x,y)->green = 0;
	image(x,y)->blue = 0;
}

PNG* SquareMaze::drawMazeWithSolution (){
	PNG* image = drawMaze();
	vector<int> vec = solveMaze();
	int x = 5;
	int y = 5;
	setRed(*image, 5, 5);
	for(int i = 0; i < (int)vec.size(); i++){
		if(vec[i] == 0){
			int j;
			for(j = x + 1; j <= x + 10; j++){
				setRed(*image, j, y);
			}
			x = j-1;
		}
		if(vec[i] == 1){
			int j;
			for(j = y + 1; j <= y + 10; j++){
				setRed(*image, x, j);
			}
			y = j-1;
		}
		if(vec[i] == 2){
			int j;
			for(j = x - 1; j >= x - 10; j--){
				setRed(*image, j, y);
			}
			x = j+1;
		}
		if(vec[i] == 3){
			int j;
			for(j = y - 1; j >= y - 10; j--){
				setRed(*image, x, j);
			}
			y = j+1;
		}		
	}
	x = x - 5;
	y = y + 5;
	for(int i = 1; i < 10; i++){
		(*image)(x + i, y)->red = 255;
		(*image)(x+i, y)->green = 255;
		(*image)(x+i,y)->blue = 255;
	}
	return image;

}
void SquareMaze::clear(){
	for(int i = 0; i < grid_width; i++){
		delete [] grid[i];
		grid[i] = NULL;
	}
	delete [] grid;
	grid = NULL;	
}

 