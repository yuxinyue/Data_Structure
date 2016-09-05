#include"image.h"

void Image::flipleft(){

  int width = this->width();
  int height = this->height();

  for(int j = 0; j < height; j++){
    for(int i = 0; i < (int)width/2; i++){
      
      RGBAPixel temp = *(*this)(i, j);
      *(*this)(i,j) = *(*this)(width-1-i, j);
      *(*this)(width-1-i, j) = temp;
    }
  }
}

void Image::adjustbrightness(int r, int g, int b){
 
  int width = this->width();
  int height = this->height();

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){

	if((*this)(i, j)->red +r > 255)	
	(*this)(i, j)->red = 255;
	  else 
	    if((*this)(i, j)->red +r < 0)
		 (*this)(i, j)->red = 0;
	       else (*this)(i, j)->red += r;

	if((*this)(i, j)->green +g > 255)	
	(*this)(i, j)->green = 255;
	  else 
	    if((*this)(i, j)-> green +g < 0)
		 (*this)(i, j)->green = 0;
	       else (*this)(i, j)->green += g;

	if((*this)(i, j)->blue + b > 255)	
	(*this)(i, j)->blue = 255;
	  else 
	    if((*this)(i, j)->blue + b < 0)
		 (*this)(i, j)->blue = 0;
	       else (*this)(i, j)->blue += b;
    }
  }
}
void Image::invertcolors(){

  int width = this->width();
  int height = this->height();

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){

  (*this)(i, j)->red = 255- (*this)(i, j)->red;
  (*this)(i, j)->green = 255 - (*this)(i, j)->green;
  (*this)(i, j)->blue = 255 - (*this)(i, j)->blue;
    }
  }
}
