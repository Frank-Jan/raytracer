#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H

#include "Color.h"

class ShadeRec;
class Ray;
class Vector3D;
class Light;
class Triangle;

class World
{
public:

    // Visibility and geometry term
//    virtual
//    double V(const Vector3D& p0, const Vector3D& p1)
//    {return false;};

    virtual
    ShadeRec hit_object(const Ray&) = 0;

//    virtual
//    void set_ambient(Light* ambient) = 0;

//    virtual
//    void add_object(Triangle*) = 0;

public:
    Color bg_color;
//    Light* ambient;
//
//protected:
//    std::vector<Triangle*> objects;
//    std::vector<Light*> lights;
};


#endif //RAYTRACER_WORLD_H
