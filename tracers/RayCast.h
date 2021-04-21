#ifndef RAYTRACER_RAYCAST_H
#define RAYTRACER_RAYCAST_H

#include "Tracer.h"
#include "constants.h"

class RayCast : public Tracer
{
public:
    explicit RayCast(World* w) :
    Tracer(w) { };

    Color trace_ray(const Ray& ray) const;

    Color trace_ray(const Ray ray, const int depth) const;

    Color trace_ray(const Ray ray, FLOAT& tmin, const int depth) const;
};


#endif //RAYTRACER_RAYCAST_H
