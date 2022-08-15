/*
*  File:        filler.cpp
*  Description: Implementation of functions in the filler namespace.
*
*/

/*
*  Performs a flood fill using breadth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillBFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.

  return Fill<Queue>(config); // REPLACE THIS STUB
}

/*
*  Performs a flood fill using depth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillDFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  return Fill<Stack>(config); // REPLACE THIS STUB
}

/*
*  Run a flood fill on an image starting at the seed point
*
*  PARAM:  config - FillerConfig struct with data for flood fill of image
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
template <template <class T> class OrderingStructure> animation filler::Fill(FillerConfig& config)
{
  /*
  * You need to implement this function!
  *
  * This is the basic description of a flood-fill algorithm: Every fill
  * algorithm requires an ordering structure, which is passed to this
  * function via its template parameter. For a breadth-first-search
  * fill, that structure is a Queue, for a depth-first-search, that
  * structure is a Stack. To begin the algorithm, you simply place the
  * given point in the ordering structure, marking it processed
  * (the way you mark it is a design decision you'll make yourself).
  * We have a choice to either change the color, if appropriate, when we
  * add the point to the OS, or when we take it off. In our test cases,
  * we have assumed that you will change the color when a point is added
  * to the structure.
  * Until the structure is empty, you do the following:
  *
  * 1.     Remove a point from the ordering structure, and then...
  *
  *        1.    add its unprocessed neighbors (up/down/left/right) whose color values are
  *              within (or equal to) tolerance distance from the seed point,
  *              to the ordering structure, and
  *              mark them as processed.
  *        2.    if it is an appropriate frame, send the current PNG to the
  *              animation (as described below).
  *
  * 2.     When implementing your breadth-first-search and
  *        depth-first-search fills, you will need to explore neighboring
  *        pixels (up/down/left/right) in some order.
  *
  *        While the order in which you examine neighbors does not matter
  *        for a proper fill, you must use the same order as we do for
  *        your animations to come out like ours! The order you should put
  *        neighboring pixels **ONTO** the queue or stack is based on the
  *        following priority condition:
  *        ** MINIMUM COLOR DISTANCE FROM THE CURRENT PIXEL **
  *        Ties are broken first by minimum y-coordinate, then by minimum x-coordinate.
  *        The HSLAPixel.dist() function will be useful, and you should
  *        take advantage of the functionality in your PriorityNeighbours class.
  * 
  *        If you process the neighbours in a different order, your fill may
  *        still work correctly, but your animations will be different
  *        from the grading scripts!
  *
  * 3.     For every k pixels filled, **starting at the kth pixel**, you
  *        must add a frame to the animation, where k = frameFreq.
  *
  *        For example, if frameFreq is 4, then after the 4th pixel has
  *        been filled you should add a frame to the animation, then again
  *        after the 8th pixel, etc.  You must only add frames for the
  *        number of pixels that have been filled, not the number that
  *        have been checked. So if frameFreq is set to 1, a pixel should
  *        be filled every frame.
  *
  * 4.     Finally, as you leave the function, send one last frame to the
  *        animation. This frame will be the final result of the fill, and
  *        it will be the one we test against.
  *
  */

  int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
  animation anim;
  OrderingStructure<PixelPoint> os;
  

  // complete your implementation below
  // HINT: you will likely want to declare some kind of structure to track
  //       which pixels have already been visited
  


  //Map that contains visited points, 0 for not visited and 1 for visited
  std::map<std::pair<unsigned int, unsigned>, int> VisitedMap;
  

  //Add first point and mark it as visited
  os.Add(config.seedpoint);
  std::pair<unsigned int, unsigned int> location1;
  location1 = std::make_pair(config.seedpoint.x, config.seedpoint.y);
  std::pair<std::pair<unsigned int, unsigned int>, int> locoConfirm;
  locoConfirm = std::make_pair(location1, 1);
  VisitedMap.insert(locoConfirm);
  HSLAPixel PickedPix1 = (*config.picker)(config.seedpoint);
  //Give picked color to that pixel in the img
  config.img.getPixel(config.seedpoint.x, config.seedpoint.y)->h = PickedPix1.h;
  config.img.getPixel(config.seedpoint.x, config.seedpoint.y)->s = PickedPix1.s;
  config.img.getPixel(config.seedpoint.x, config.seedpoint.y)->l = PickedPix1.l;
  config.img.getPixel(config.seedpoint.x, config.seedpoint.y)->a = PickedPix1.a;
  framecount++;
  if (framecount % config.frameFreq == 0){
      anim.addFrame(config.img);
  }


  //Main loop to loop through all candidate pixels
  while (!os.IsEmpty()){

    //Remove pixel from os
    PixelPoint toBePicked = os.Remove();

    //Set reference color to the color of this pixel
    config.neighbourorder.SetReferenceColor(toBePicked.color);

    //Create PriorityList with neighbouring pixels(might have boundary issues with calling pixels outside of the boundary)
    
      
          //Left Pixel
          if ((int)toBePicked.x-1 >= 0){

            //std::cout << "got inside first if" << " ";

            std::pair<unsigned int,unsigned int> locGame;
            locGame = std::make_pair(toBePicked.x-1,toBePicked.y);
            std::map<std::pair<unsigned int, unsigned int>,int>::iterator it;
            it = VisitedMap.find(locGame);

            if (it == VisitedMap.end()){

              //std::cout << "got inside second if" << " ";

              PixelPoint PixelDummy = PixelPoint(toBePicked.x-1,toBePicked.y,HSLAPixel(0,0,0));
              PixelDummy.color.h = config.img.getPixel(toBePicked.x-1, toBePicked.y)->h;
              PixelDummy.color.s = config.img.getPixel(toBePicked.x-1, toBePicked.y)->s;
              PixelDummy.color.l = config.img.getPixel(toBePicked.x-1, toBePicked.y)->l;
              PixelDummy.color.a = config.img.getPixel(toBePicked.x-1, toBePicked.y)->a;
              if (PixelDummy.color.dist(config.seedpoint.color) <= config.tolerance){
                config.neighbourorder.Insert(PixelDummy);

                //std::cout << "Inserted!" << " ";
              }
            }
          } 

          //Down Pixel
          if ((int)toBePicked.y-1 >= 0){

            //std::cout << "got inside first if" << " ";

            std::pair<unsigned int,unsigned int> locGame;
            locGame = std::make_pair(toBePicked.x,toBePicked.y-1);
            std::map<std::pair<unsigned int, unsigned int>,int>::iterator it;
            it = VisitedMap.find(locGame);

            if (it == VisitedMap.end()){

              //std::cout << "got inside second if" << " ";

              PixelPoint PixelDummy = PixelPoint(toBePicked.x,toBePicked.y-1,HSLAPixel(0,0,0));
              PixelDummy.color.h = config.img.getPixel(toBePicked.x, toBePicked.y-1)->h;
              PixelDummy.color.s = config.img.getPixel(toBePicked.x, toBePicked.y-1)->s;
              PixelDummy.color.l = config.img.getPixel(toBePicked.x, toBePicked.y-1)->l;
              PixelDummy.color.a = config.img.getPixel(toBePicked.x, toBePicked.y-1)->a;
              if (PixelDummy.color.dist(config.seedpoint.color) <= config.tolerance){
                config.neighbourorder.Insert(PixelDummy);

                //std::cout << "Inserted!" << " ";
              }
            }
          }

          //Right Pixel
          if (toBePicked.x+1 < config.img.width()){

            //std::cout << "got inside first if" << " ";

            std::pair<unsigned int,unsigned int> locGame;
            locGame = std::make_pair(toBePicked.x+1,toBePicked.y);
            std::map<std::pair<unsigned int, unsigned int>,int>::iterator it;
            it = VisitedMap.find(locGame);

            if (it == VisitedMap.end()){

              //std::cout << "got inside second if" << " ";

              PixelPoint PixelDummy = PixelPoint(toBePicked.x+1,toBePicked.y,HSLAPixel(0,0,0));
              PixelDummy.color.h = config.img.getPixel(toBePicked.x+1, toBePicked.y)->h;
              PixelDummy.color.s = config.img.getPixel(toBePicked.x+1, toBePicked.y)->s;
              PixelDummy.color.l = config.img.getPixel(toBePicked.x+1, toBePicked.y)->l;
              PixelDummy.color.a = config.img.getPixel(toBePicked.x+1, toBePicked.y)->a;
              if (PixelDummy.color.dist(config.seedpoint.color) <= config.tolerance){
                config.neighbourorder.Insert(PixelDummy);

                //std::cout << "Inserted!" << " ";
              }
            }
          }

          //Up Pixel
          if (toBePicked.y+1 < config.img.height()){

            //std::cout << "got inside first if" << " ";

            std::pair<unsigned int,unsigned int> locGame;
            locGame = std::make_pair(toBePicked.x+1,toBePicked.y+1);
            std::map<std::pair<unsigned int, unsigned int>,int>::iterator it;
            it = VisitedMap.find(locGame);

            if (it == VisitedMap.end()){

              //std::cout << "got inside second if" << " ";

              PixelPoint PixelDummy = PixelPoint(toBePicked.x,toBePicked.y+1,HSLAPixel(0,0,0));
              PixelDummy.color.h = config.img.getPixel(toBePicked.x, toBePicked.y+1)->h;
              PixelDummy.color.s = config.img.getPixel(toBePicked.x, toBePicked.y+1)->s;
              PixelDummy.color.l = config.img.getPixel(toBePicked.x, toBePicked.y+1)->l;
              PixelDummy.color.a = config.img.getPixel(toBePicked.x, toBePicked.y+1)->a;
              if (PixelDummy.color.dist(config.seedpoint.color) <= config.tolerance){
                config.neighbourorder.Insert(PixelDummy);

                //std::cout << "Inserted!" << " ";
              }
            }
          }

          
        
      

      
    
    

    //Add all neighbourorder pixels to os
    while (!config.neighbourorder.IsEmpty()){

      PixelPoint toBePicked1 = config.neighbourorder.Remove();

      //Add to os
      os.Add(toBePicked1);

      //std::cout << "Added!" << " ";

      HSLAPixel PickedPix = (*config.picker)(toBePicked1);

      //Give picked color to that pixel in the img
      config.img.getPixel(toBePicked1.x, toBePicked1.y)->h = PickedPix.h;
      config.img.getPixel(toBePicked1.x, toBePicked1.y)->s = PickedPix.s;
      config.img.getPixel(toBePicked1.x, toBePicked1.y)->l = PickedPix.l;
      config.img.getPixel(toBePicked1.x, toBePicked1.y)->a = PickedPix.a;

      //Mark added points as visited
      std::pair<unsigned int, unsigned int> located;
      located = std::make_pair(toBePicked1.x, toBePicked1.y);
      std::pair<std::pair<unsigned int, unsigned int>, int> visited;
      visited = std::make_pair(located, 1);
      VisitedMap.insert(visited);


      //Increment numPixels and add frame to anim if needed
      framecount++;
      if (framecount % config.frameFreq == 0){
        anim.addFrame(config.img);
      }
    }


  }

  //Add one last frame
  anim.addFrame(config.img); 

  return anim;
}

