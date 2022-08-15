Implemented an image processing class with several functions by manipulating HSLA pixels in a PNG class. Constructed a queue, stack and priority queue class to build functions.



List of functions below:

CensorColorPicker: given a radius and center and a PNG image, average the color of all pixels within such circle and apply it to the image evenly over that circle. Can be done over a PNG animation.

Filler: given the color and fill pattern and a PNG image, flood fill the image with a specific color over a PNG animation by adjusting the HSLA values of pixels. Can choose between DFS or BFS fill algorithm.

NegativeColorPicker: given a PNG image, convert all the pixels to its negative hue.

ImageTileColorPicker: given two PNG images of the same dimensions, determine the color needed for one pixel of image A to replicate the pixel of the same location in image B.
