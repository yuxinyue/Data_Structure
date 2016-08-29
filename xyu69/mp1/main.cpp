#include"png.h"

int main(){

	PNG inImage("in.png");
	int xi = inImage.width();
	int yi = inImage.height();
	
	PNG outImage(xi,yi);
	
	for(int i = 0; i < yi; i++){
		for(int j = 0; j < xi; j++){
			//std::cout<<"yi: "<<yi<<", j: "<<j<<std::endl;
		  RGBAPixel a = *inImage(xi-1-j, yi-1-i);
		  *outImage(j, i) = a;
		}
	}
	outImage.writeToFile("out.png");
	return 0;
}
