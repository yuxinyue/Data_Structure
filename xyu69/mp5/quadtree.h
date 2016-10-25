/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:


    Quadtree ();
    Quadtree (PNG const &source, int resolution);
    Quadtree (Quadtree const &other);
    ~Quadtree();

 
    Quadtree const & operator= (Quadtree const &other);
    void buildTree (PNG const &source, int resolution);
    RGBAPixel getPixel (int x, int y) const;
    PNG decompress () const;
    int pruneSize( int tolerance )  const;
    int idealPrune  (   int   numLeaves )   const;
    void clockwiseRotate  (     )   ;
    void prune  (   int   tolerance )   ;
  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
        int resolution;
        int x;
        int y;
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    //helper fns
    QuadtreeNode* copy( QuadtreeNode*  otherRoot );
    void clear(QuadtreeNode* & qroot);
    QuadtreeNode* helpBuildTree (PNG const &source , int x, int y, int resolution);
    RGBAPixel calAve(QuadtreeNode* qroot);
    RGBAPixel helpGetPixel(QuadtreeNode* qroot, int x, int y)const;
    void helpDecompress (QuadtreeNode* qroot, PNG & image) const;


/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
