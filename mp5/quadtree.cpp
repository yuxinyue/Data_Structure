/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"


Quadtree::Quadtree (){
	root = NULL;
}
Quadtree::Quadtree (PNG const &source, int resolution){
    root = NULL;
    buildTree(source, resolution);
}

Quadtree::Quadtree (Quadtree const &other){
    root = copy(other.root);
}

Quadtree::~Quadtree(){
    clear(root);
}

Quadtree const & Quadtree::operator= (Quadtree const &other){
    if(this != & other){
        clear(root);
        root = copy(other.root);
    }
    return * this;
}

void Quadtree::buildTree (PNG const &source, int resolution){
    clear(root);
    root = helpBuildTree(source, 0, 0, resolution);
}


RGBAPixel Quadtree::calAve(QuadtreeNode* qroot){
    RGBAPixel r;
    r.red = (qroot->nwChild->element.red + qroot->neChild->element.red + qroot->swChild->element.red + qroot->seChild->element.red)/4;
    r.green = (qroot->nwChild->element.green + qroot->neChild->element.green + qroot->swChild->element.green + qroot->seChild->element.green)/4;
    r.blue = (qroot->nwChild->element.blue + qroot->neChild->element.blue + qroot->swChild->element.blue + qroot->seChild->element.blue)/4;
    return r;
}

Quadtree::QuadtreeNode* Quadtree::helpBuildTree (PNG const &source, int x, int y, int resolution){

    QuadtreeNode* qroot = new QuadtreeNode();

    if(resolution == 1){
        qroot->element = *source(x,y);
        qroot->resolution = resolution;
        qroot->x = x;
        qroot->y = y;
        return qroot;
    }
    qroot->nwChild = helpBuildTree(source, x, y, resolution/2);
    qroot->neChild = helpBuildTree(source, x + resolution/2, y, resolution/2);
    qroot->swChild = helpBuildTree(source, x, y + resolution/2, resolution/2);
    qroot->seChild = helpBuildTree(source, x + resolution/2, y + resolution/2, resolution/2);
    
    qroot->element = calAve(qroot);
    qroot->resolution = resolution;
    qroot->x = x;
    qroot->y = y;

    return qroot;
}


Quadtree::QuadtreeNode* Quadtree::copy( QuadtreeNode*  otherRoot ){
    	
        QuadtreeNode* qroot= NULL;
        if(otherRoot != NULL){
            qroot = new QuadtreeNode();
            qroot->element = otherRoot->element;
            qroot->resolution = otherRoot->resolution;
            qroot->x = otherRoot->x;
            qroot->y = otherRoot->y;
    		qroot->nwChild = copy(otherRoot->nwChild);
    		qroot->neChild = copy(otherRoot->neChild);
    		qroot->swChild = copy(otherRoot->swChild);
    		qroot->seChild = copy(otherRoot->seChild);
    	}
    	return qroot;
    }
void Quadtree::clear(QuadtreeNode* & qroot){

	if(qroot != NULL){
		clear(qroot->nwChild);
		clear(qroot->neChild);
		clear(qroot->swChild);
		clear(qroot->seChild);
		delete qroot;
		qroot = NULL;
	}
}

RGBAPixel Quadtree::getPixel (int x, int y) const{
    if(root == NULL) return RGBAPixel();
    if(x >= root->resolution || y >= root->resolution) return RGBAPixel(); 
    if(x < 0 || y < 0) return RGBAPixel();
    return helpGetPixel(root, x, y);
}

RGBAPixel Quadtree::helpGetPixel(QuadtreeNode* qroot, int x, int y)const{
    if( qroot->nwChild == NULL) return qroot->element;
    int resolution = qroot->resolution;
    if(qroot->x < x+resolution/2 && qroot->y < y+resolution/2)
        return helpGetPixel(qroot->nwChild, x, y);
    if(qroot->x >= x+resolution/2 && qroot->y < y+resolution/2)
        return helpGetPixel(qroot->nwChild, x, y);
    if(qroot->x < x+resolution/2 && qroot->y >= y+resolution/2)
        return helpGetPixel(qroot->swChild, x, y);
    if(qroot->x >= x+resolution/2 && qroot->y >= y+resolution/2)
        return helpGetPixel(qroot->seChild, x, y);
    return RGBAPixel();
}

PNG Quadtree::decompress () const{
    if (root == NULL)return PNG();
    PNG image = PNG(root->resolution, root->resolution);
    helpDecompress(root, image);
    return image;
}

void Quadtree::helpDecompress (QuadtreeNode* qroot, PNG & image) const{
    if(qroot->nwChild == NULL){
        for(int i = qroot->x; i < qroot->x + qroot->resolution; i++){
            for(int j = qroot->y; j < qroot->y + qroot->resolution; j++){
                *image(i, j) = qroot->element;
            }
        }
        return;
    }
    helpDecompress(qroot->nwChild, image);
    helpDecompress(qroot->neChild, image);
    helpDecompress(qroot->swChild, image);
    helpDecompress(qroot->seChild, image);
    return;
}
int Quadtree::pruneSize( int tolerance )  const{
    return 0;
}
int Quadtree::idealPrune  (   int   numLeaves )   const{
    return 0;
}
void Quadtree::clockwiseRotate  (     )   {

}
void Quadtree::prune  (   int   tolerance )   {

}