#include "Frame.h"
#include "Color.h"
#include <iostream>

Frame::Frame(int width, int height) : width(width), height(height)
{
    image = new unsigned char[height*width*BYTES_PER_PIXEL];
}


Frame::~Frame()
{
    if(!image)
        delete[] image;
}

void Frame::setPixel(unsigned int x, unsigned int y, const Color& c)
{
    if(x > width)
        return;
    if(y > height)
        return;
    unsigned int pixel = (y*width + x)*BYTES_PER_PIXEL;

    image[pixel+0] = (unsigned char) (c.blue*255);
    image[pixel+1] = (unsigned char) (c.green*255);
    image[pixel+2] = (unsigned char) (c.red*255);
}