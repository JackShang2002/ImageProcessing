/*
*  File: negativeColorPicker.cpp
*  Implements the negative color picker for CPSC 221 PA2.
*
*/

#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg)
{
  img = inputimg;
  
}

HSLAPixel NegativeColorPicker::operator()(PixelPoint p)
{
  HSLAPixel NewPix = HSLAPixel();
  NewPix.s = img.getPixel(p.x, p.y)->s;
  NewPix.a = img.getPixel(p.x, p.y)->a;
  NewPix.h = img.getPixel(p.x, p.y)->h;
  NewPix.l = img.getPixel(p.x, p.y)->l;
  if (NewPix.h < 180){
    NewPix.h += 180;
  }else{
    NewPix.h = NewPix.h + 180 - 360;
  }
  if (NewPix.l > 0.5){
    NewPix.l = 0.5 - (NewPix.l - 0.5);
  }else if (NewPix.l < 0.5){
    NewPix.l = 0.5 + (0.5 - NewPix.l);
  }


  return NewPix; // REPLACE THIS STUB
}
