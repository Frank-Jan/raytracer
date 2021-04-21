#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Vector3D.h"

class Ray
{
public:
    Vector3D o;  // Origin
    Vector3D d; // Direction

    Ray() = default;
    Ray(const Vector3D& _o, const Vector3D& _d) : o(_o), d(_d)
    {};
};


#endif //RAYTRACER_RAY_H
