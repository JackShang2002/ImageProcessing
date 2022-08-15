/*
*  File: imageTileColorPicker.cpp
*  Implements the image tile color picker for CPSC 221 PA2.
*
*/

#include "imageTileColorPicker.h"

ImageTileColorPicker::ImageTileColorPicker(PNG& otherimage) {
  // complete your implementation below
  img_other = otherimage;
  
}

HSLAPixel ImageTileColorPicker::operator()(PixelPoint p) {
  // complete your implementation below
  HSLAPixel NewPix = HSLAPixel();
  unsigned int width = img_other.width();
  unsigned int height = img_other.height();
  int NewX = p.x % width;
  int NewY = p.y % height;

  NewPix.s = img_other.getPixel(NewX, NewY)->s;
  NewPix.a = img_other.getPixel(NewX, NewY)->a;
  NewPix.h = img_other.getPixel(NewX, NewY)->h;
  NewPix.l = img_other.getPixel(NewX, NewY)->l;

  
  return NewPix; // REPLACE THIS STUB
}