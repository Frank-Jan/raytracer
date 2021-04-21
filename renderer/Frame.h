//
// Created by FJ on 26-2-2021.
//

#ifndef RAYTRACER_FRAME_H
#define RAYTRACER_FRAME_H

#include "../export/bmp.h"
#include <iterator>
#include <algorithm>
#include <array>
#include "Point2D.h"

class Color;
class Frame;

class Frame
{
public:
    unsigned char* image = nullptr;
    const int height;
    const int width;

    Frame(int width, int height);

    ~Frame();

    void setPixel(unsigned int x, unsigned int y, const Color& c);
};

#endif //RAYTRACER_FRAME_H
