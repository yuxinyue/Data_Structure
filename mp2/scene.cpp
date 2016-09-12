#include "scene.h"
using namespace std;

Scene::Scene(int newMax){
 
  max = newMax;
  array = new Image*[max];
  xco = new int[max];
  yco = new int[max];
  for(int i = 0; i < max; i++){
    array[i] = NULL;
    xco[i] = 0;
    yco[i] = 0;
  }
}


Scene::~Scene(){

  clear();
}


Scene::Scene(const Scene & source){

  copy(source);
}



//Return Type??????Const????????
const Scene& Scene::operator=(const Scene & source){
  if  (this != &source){
      clear();
      copy(source);
  }
  return *this;
}


void Scene::changemaxlayers(int newmax){
  
  bool valid = true;
  Image ** newArray = new Image*[newmax];
  int *newXco = new int[newmax];
  int *newYco = new int[newmax];

   if(newmax < max){

      for(int i = newmax; i < max; i++)
      {
	if (array[i] != NULL)
        valid = false;
	break;
      } 

    if(!valid)
    {
    cout<<"invalid newmax"<<endl;
    }else
    {

	for(int i = 0; i < max; i++)
         {
	    *newArray[i] = *array[i];
	     newXco[i] = xco[i];
	     newYco[i] = yco[i];	
	 }
    }
   }
    else 
        {

	for(int i = 0; i < max; i++)
        {
	    *newArray[i] = *array[i];
	     newXco[i] = xco[i];
	     newYco[i] = yco[i];
	}
	for(int i = max; i < newmax; i++)
        {
	    newArray[i] = NULL;
	    newXco = 0;
	    newYco = 0;
	}
    }
  //CLEAR!!!!!! how to use destructor?
  clear();
  array = newArray;
  xco = newXco;
  yco = newYco;
}


//????FileName??????????????
void Scene::addpicture(const char *FileName, int index, int x, int y){
	
	if((index > (max-1))|| (index < 0)){ 
	cout<<"index out of bounds"<<endl;
	return;
	}
////THINK MEMORY
	Image* image = new Image();
	image->readFromFile(FileName);
	if(array[index] != NULL){
	delete array[index];
//CHECK IF NEED!!!!!!!!!!!
//	array[index] = NULL;
	}

	array[index] = image;
	xco[index] = x;
	yco[index] = y;	
}

void Scene::changelayer(int index, int newindex){

	if((index < 0) |(index > (max-1)))
	{

	cout<<"invalid index"<<endl;

	}
	else if(newindex < 0| newindex > (max-1))
	{

	cout<<"invalid index"<<endl;

	}
	else
	{
		if(index == newindex)
		return;

	 	if(array[newindex] != NULL)
		delete array[newindex];
	
		array[newindex] = array[index];
//Don't delete array[index], cause they are pointing to the same thing!!!!
		array[index] = NULL;

	xco[newindex] = xco[index];
	yco[newindex] = yco[index];
	xco[index] = 0;
	yco[index] = 0;
        }
}

void Scene::translate (int index, int xcoord, int ycoord){

	if((index < 0) | (index > (max-1)) | (array[index]==NULL))
	cout<<"invalid index"<<endl;
	else
	{
	xco[index] = xcoord;
	yco[index] = ycoord;
	}
}


void Scene::deletepicture (int index){

        if((index < 0) | (index > (max-1)) | (array[index]==NULL))
        cout<<"invalid index"<<endl;
	else
	{
	delete array[index];
	array[index] = NULL;
	xco[index] = 0;
	yco[index] = 0;
	}
}




Image* Scene::getpicture (int index) const{

        if((index < 0) | (index > (max-1)) | (array[index]==NULL))
        cout<<"invalid index"<<endl;
	return array[index];
}


Image Scene::drawscene() const{

	int maxWidth = 0;
	int maxHeight = 0;

	for (int i = 0; i < max; i++){
		
		if(array[i] != NULL){
	
		if((xco[i] +(int)array[i]->width()) > maxWidth)
		maxWidth = (xco[i] + array[i]->width());

		if((int)(yco[i] + array[i]->height()) > maxHeight)
		maxHeight = (yco[i] + array[i]->height());
		}
	}
	Image outImage(maxWidth, maxHeight);
	
	for(int i = 0; i < max; i++)
	{
		if(array[i] == NULL)
		continue;
		else
		{
			int xend = xco[i] + array[i]->width();
			int yend = yco[i] + array[i]->height();
			for(int j = xco[i]; j < xend; j++)
			{
			    for(int k = yco[i]; k < yend; k++)
			    {
				*outImage(j,k) = *(*array[i])(j-xco[i], k-yco[i]);
			    }
			}
		}
	}

	return outImage;
}

void Scene::copy(const Scene & source){

  max = source.max;
  array = new Image*[max];
  xco = new int[max];
  yco = new int[max];
  for(int i = 0; i < max; i++)
  {
    if(source.array[i] != NULL){

    array[i] = new Image(*source.array[i]);
    xco[i] = source.xco[i];
    yco[i] = source.yco[i]; 
    }
    else
    {
    array[i] = NULL;
    xco[i] = 0;
    yco[i] = 0;
    }
  }
 
}


void Scene::clear(){

  for(int i = 0 ; i < max; i++)
  {
    if(array[i] != NULL)
    delete array[i];
    array[i] = NULL;
  }
  delete [] array;
  delete [] xco;
  xco = NULL;
  delete [] yco;
  yco = NULL;

}
