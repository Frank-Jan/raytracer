#ifndef RAYTRACER_POINT2D_H
#define RAYTRACER_POINT2D_H

#include "constants.h"

class Point2D
{
public:
    FLOAT x;
    FLOAT y;
public:
    Point2D() = default;
    Point2D(FLOAT x, FLOAT y) :
    x(x), y(y) { };
};


#endif //RAYTRACER_POINT2D_H
