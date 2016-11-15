/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<3>> vec;
    map<RGBAPixel, TileImage> mapforTiles;
    for(int i = 0; i < (int)theTiles.size(); i++){
    	RGBAPixel color = theTiles[i].getAverageColor();
 
    	Point<3> tilePoint(color.red, color.green, color.blue);
    	vec.push_back(tilePoint);

    	mapforTiles[color] = theTiles[i];
    }

   	KDTree<3> kdt(vec);

   	int x = theSource.getRows();
   	int y = theSource.getColumns();
   	MosaicCanvas* mCanvas = new MosaicCanvas(x, y);

   	for(int j = 0; j < x; j++){
   		for(int k = 0; k < y; k++){
   			RGBAPixel color = theSource.getRegionColor(j, k);
   			Point<3> sourcePoint(color.red, color.green, color.blue);
   			Point<3> resultPoint = kdt.findNearestNeighbor(sourcePoint);
   			
   			RGBAPixel resultPixel(resultPoint[0], resultPoint[1], resultPoint[2]);
   			TileImage image = mapforTiles[resultPixel];

   			mCanvas->setTile(j, k, image);
   		}
   	}
   	return mCanvas;
}

