#include<cstdint>
using std::uint8_t;

#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

class RGBAPixel {

	public:
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;
	
 		RGBAPixel();
		RGBAPixel(uint8_t red,uint8_t green, uint8_t blue);
};
#endif

