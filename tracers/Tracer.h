#ifndef RAYTRACER_TRACER_H
#define RAYTRACER_TRACER_H

#include "constants.h"

class Color;
class World;
class Ray;
class ShadeRec;

class Tracer
{
public:
    World* world;
public:
    explicit Tracer(World* w);

    virtual Color trace_ray(const Ray& ray) const;

    virtual Color trace_ray(const Ray ray, const int depth) const;

    virtual Color trace_ray(const Ray ray, FLOAT& tmin, const int depth) const;

};

#endif //RAYTRACER_TRACER_H
