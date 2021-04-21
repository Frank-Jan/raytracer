#ifndef RAYTRACER_CONSTANTTRACER_H
#define RAYTRACER_CONSTANTTRACER_H

#include "Tracer.h"


class ConstantTracer : public Tracer
{
public:
    ConstantTracer(World* w) : Tracer(w)
    { }

     virtual Color trace_ray(const Ray& ray) const;
};


#endif //RAYTRACER_CONSTANTTRACER_H
