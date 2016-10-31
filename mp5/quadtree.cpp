/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"
using std::cout;
using std::endl;

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
    if(x < qroot->x+resolution/2 && y < qroot->y+resolution/2)
        return helpGetPixel(qroot->nwChild, x, y);
    if(x >= qroot->x+resolution/2 && y < qroot->y+resolution/2)
        return helpGetPixel(qroot->neChild, x, y);
    if(x < qroot->x+resolution/2 && y >= qroot->y+resolution/2)
        return helpGetPixel(qroot->swChild, x, y);
    if(x >= qroot->x+resolution/2 && y >= qroot->y+resolution/2)
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

void Quadtree::clockwiseRotate  (     )   {
    if(root == NULL) return;
    helpClockwiseRotate(root);
    changeXY(root, 0, 0);
}

void Quadtree::helpClockwiseRotate(QuadtreeNode * qroot){
    if(qroot->nwChild == NULL) return;
  helpClockwiseRotate(qroot->nwChild);
    helpClockwiseRotate(qroot->neChild);
    helpClockwiseRotate(qroot->swChild);
    helpClockwiseRotate(qroot->seChild);
    
    QuadtreeNode * temp = qroot->nwChild;
    qroot->nwChild = qroot->swChild;
    qroot->swChild = qroot->seChild;
    qroot->seChild = qroot->neChild;
    qroot->neChild = temp;

} 

void Quadtree::changeXY(QuadtreeNode * qroot, int x, int y){
    if(qroot == NULL) return;
    qroot->x = x;
    qroot->y = y;
    changeXY(qroot->nwChild, x, y);
    changeXY(qroot->neChild, x + qroot->resolution/2, y);
    changeXY(qroot->swChild, x, y + qroot->resolution/2);
    changeXY(qroot->seChild, x + qroot->resolution/2, y + qroot->resolution/2);

}

void Quadtree::prune  (   int   tolerance )   {
    if(root == NULL) return;
    helpPrune(root, tolerance);
}

void Quadtree::helpPrune(QuadtreeNode * qroot, int tolerance){
    if(qroot->nwChild == NULL) return;
    if(ifPruned(qroot, tolerance, qroot->element)){
        clear(qroot->nwChild);
        clear(qroot->neChild);
        clear(qroot->swChild);
        clear(qroot->seChild);
        return;        
    }
    helpPrune(qroot->nwChild, tolerance);
    helpPrune(qroot->neChild, tolerance);
    helpPrune(qroot->swChild, tolerance);
    helpPrune(qroot->seChild, tolerance);
}

bool Quadtree::ifPruned(QuadtreeNode * qroot, int tolerance, RGBAPixel base) const{
    if(qroot->nwChild == NULL){
        bool diff = tolerance >= (qroot->element.red - base.red)*(qroot->element.red - base.red) 
                                + (qroot->element.green - base.green)*(qroot->element.green - base.green)
                                + (qroot->element.blue - base.blue)*(qroot->element.blue - base.blue);
        return diff;
    }
    return ifPruned(qroot->nwChild, tolerance, base) && ifPruned(qroot->neChild, tolerance, base)
            && ifPruned(qroot->swChild, tolerance, base) && ifPruned(qroot->seChild, tolerance, base);
}

int Quadtree::pruneSize( int tolerance )  const{
    if (root == NULL) return 0;
    return helpPruneSize(root, tolerance);
}

int Quadtree::helpPruneSize(QuadtreeNode * qroot, int tolerance) const{
    if(qroot->nwChild == NULL) return 1;
    if(ifPruned(qroot, tolerance, qroot->element)){
        return 1;        
    }
    return helpPruneSize(qroot->nwChild, tolerance) + helpPruneSize(qroot->neChild, tolerance)
        + helpPruneSize(qroot->swChild, tolerance) + helpPruneSize(qroot->seChild, tolerance);
}

int Quadtree::idealPrune  (   int   numLeaves )   const{
    int low = 0;
    int high = 3*255*255;
    int tolerance;
    while(low < high){
        tolerance = (high + low)/2;
        //cout<<low <<" "<<high<<" "<<pruneSize(tolerance)<<endl;
        if(pruneSize(tolerance) == numLeaves) {
            while(pruneSize(tolerance-1) == numLeaves)
            tolerance = tolerance-1;
            return tolerance;
        }
        if(pruneSize(tolerance) > numLeaves){
            low = tolerance+1;
        } 
        else{
            high = tolerance;
        }
    }
    if (pruneSize(tolerance)<numLeaves) return tolerance;
    else  return tolerance+1; 
}

