/*
*  File: censorColorPicker.cpp
*  Implements the censor color picker for CPSC 221 PA2.
*
*/

#include "censorColorPicker.h"

#include <math.h> // gives access to sqrt function

/*
*  Useful function for computing the Euclidean distance between two PixelPoints
*/
double PointDistance(PixelPoint a, PixelPoint b) {
  unsigned int diff_x, diff_y;
  if (a.x > b.x)
    diff_x = a.x - b.x;
  else
    diff_x = b.x - a.x;
  if (a.y > b.y)
    diff_y = a.y - b.y;
  else
    diff_y = b.y - a.y;
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}

CensorColorPicker::CensorColorPicker(unsigned int b_width, PixelPoint ctr, unsigned int rad, PNG& inputimage)
{
  // complete your implementation below
  blockwidth = b_width;
  center = ctr;
  radius = rad;
  img = inputimage;
  blockyimg = img;

  //blockify the whole image
  for (unsigned int x = 0; x < img.width(); x = x + b_width){
    for (unsigned int y = 0; y < img.height(); y = y + b_width){
      //Calculate average h,s,l,a for the block
      double avgH = 0.0;
      double avgL = 0.0;
      double avgS = 0.0;
      double avgA = 0.0;
      double total = b_width * b_width;

      for (unsigned int j = 0; j < b_width; j++){
        for (unsigned int k = 0; k < b_width; k++){
          avgH += img.getPixel(x+j,y+k)->h;
          avgS += img.getPixel(x+j,y+k)->s;
          avgL += img.getPixel(x+j,y+k)->l;
          avgA += img.getPixel(x+j,y+k)->a;
        }
      }
      avgH = avgH / total;
      avgL = avgL / total;
      avgS = avgS / total;
      avgA = avgA / total;

      //distribute these values over the block
      for (unsigned int a = 0; a < b_width; a++){
        for (unsigned int b = 0; b < b_width; b++){
          blockyimg.getPixel(x+a,y+b)->h = avgH;
          blockyimg.getPixel(x+a,y+b)->s = avgS;
          blockyimg.getPixel(x+a,y+b)->l = avgL;
          blockyimg.getPixel(x+a,y+b)->a = avgA;
        }
      }
    }    
  }

  //restore original colors for pixels outside the circle
  for (unsigned int x = 0; x < img.width(); x++){
    for (unsigned int y = 0; y < img.height(); y++){
      double distance = PointDistance(PixelPoint(x,y,HSLAPixel(0,0,0)), center);
      if (distance > rad){
        blockyimg.getPixel(x,y)->s = img.getPixel(x,y)->s;
        blockyimg.getPixel(x,y)->h = img.getPixel(x,y)->h;
        blockyimg.getPixel(x,y)->l = img.getPixel(x,y)->l;
        blockyimg.getPixel(x,y)->a = img.getPixel(x,y)->a;
      }
    }
  }
  
}

HSLAPixel CensorColorPicker::operator()(PixelPoint p)
{
  // complete your implementation below

  HSLAPixel NewPix = HSLAPixel();
  NewPix.s = blockyimg.getPixel(p.x, p.y)->s;
  NewPix.a = blockyimg.getPixel(p.x, p.y)->a;
  NewPix.h = blockyimg.getPixel(p.x, p.y)->h;
  NewPix.l = blockyimg.getPixel(p.x, p.y)->l;
  
  return NewPix; // REPLACE THIS STUB
}
