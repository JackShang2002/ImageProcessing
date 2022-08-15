/*
* File:        priority.cpp
* Description: Implements a priority ordering structure specially made for determining the
*              order of neighbours visited in PA2's filler::fill function.
*              Note that this does NOT serve the same purpose as the stack/queue
*              ordering structure which you have also been asked to implement.
*
*              Ignoring resize costs, any single insertion or removal operation
*              should cost at most O(n), where n is the number of PixelPoints
*              stored in the collection.
*
* Date:        2022-02-10 02:04
*
*/

#include "priority.h"
#include <assert.h>

using namespace cs221util;
using namespace std;

/*
*  Default constructor
*  Initializes refcolor to the default color according to the HSLAPixel implementation.
*/
PriorityNeighbours::PriorityNeighbours() {
  // complete your implementation below
  
  vector<PixelPoint> pixVec;
  points = pixVec;
  refcolor = HSLAPixel();
}

/*
*  Parameterized constructor
*  Initializes refcolor to the supplied value.
*/
PriorityNeighbours::PriorityNeighbours(HSLAPixel ref) {
  // complete your implementation below
  vector<PixelPoint> pixVec;
  points = pixVec;
  refcolor = ref;
}

/*
*  Inserts an item into the collection
*  PARAM: p - item to be inserted
*  POST:  the collection contains p, along with all previously existing items.
*/
void PriorityNeighbours::Insert(PixelPoint p) {
  if (points.empty()){
    points.push_back(p);
  }else{
   
  size_t temp = 0;
  for (size_t n = 0; n < points.size(); n++){
    //if n.color is greater than p.color, p gets inserted infront of n
    if (refcolor.dist(points[n].color) > refcolor.dist(p.color)){
      points.insert(points.begin() + n, p);
      std::cout << "n.color is greater than p.color: " << points.front().x << " ";
      break;
    }
    //if n.color is same as p.color, then compare y value
    if (refcolor.dist(points[n].color) == refcolor.dist(p.color)){
      //if n.y is greater than p.y, p gets inserted infront of n
      if (points[n].y > p.y){
        points.insert(points.begin() + n,p);
        std::cout << "n.y is greater than p.y: " << points.front().x << " ";
        break;
      }
      //if n.y is same as p.y, then compare x value
      if (points[n].y == p.y){
        //if n.x is greater than p.x, p gets inserted infront of n
        if (points[n].x > p.x){
          points.insert(points.begin() + n,p);
          std::cout << "n.x is greater than p.x: " << points.front().x << " ";
          break;
        }
      }
    }
    temp++;
    //std::cout << "X coord for first element" << points.front().x << " ";
  }
  if (temp == points.size()){
    points.push_back(p);
  }
  }
  
}

/*
*  Removes and returns an item from the collection satisfying the priority condition
*  PRE:    the collection is not empty (but it would be good to check anyway!).
*  POST:   the item satisfying the priority condition is removed from the collection.
*  RETURN: the item satisfying the priority condition
*
*  Priority condition:
*    The PixelPoint in the collection whose color is the minimum distance away
*    from the reference color is the priority item to be returned.
*
*    In case of multiple items with the same priority value (i.e. minimal distance
*    away from the reference color), the one with the minimal y-coordinate will be
*    selected.
*    In case of multiple items with the same priority value and the same y-coordinate,
*    the one with the minimal x-coordinate will be selected.
*
*    ***ATTENTION*** The dist() function in HSLAPixel.h will be very helpful!
*
*  Combined with Insert(), think about the time complexity of maintaining the
*  priority order and/or accessing the priority element in this specific application!
*/
PixelPoint PriorityNeighbours::Remove() {
  // complete your implementation below


  PixelPoint tempPix = points.front();
  points.erase(points.begin());
  

  
  return tempPix; // REPLACE THIS STUB
}

/*
*  Checks if the collection is empty
*  RETURN: true, if the collection is empty
*          false, otherwise
*/
bool PriorityNeighbours::IsEmpty() const {
  // complete your implementation below
  if (points.empty()){
    return true;
  }

  return false; // REPLACE THIS STUB
}

/*
*  Returns the value of the reference color
*/
HSLAPixel PriorityNeighbours::GetReferenceColor() const {
  // complete your implementation below
  
  return refcolor; // REPLACE THIS STUB
}

/*
*  Sets the reference color attribute
*  POST: refcolor is set to the supplied value
*/
void PriorityNeighbours::SetReferenceColor(HSLAPixel ref) {
  
  refcolor = ref;
  
}