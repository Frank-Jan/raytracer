#include "ConstantTracer.h"
#include "Color.h"
#include "constants.h"
#include "Triangle.h"
#include "World.h"
#include "ShadeRec.h"

//Color Tracer::trace_ray(const ShadeRec& sr) const
Color ConstantTracer::trace_ray(const Ray& ray) const
{
//    ShadeRec sr = world->hit(ray);
//    if(sr.hit)
//        return sr.obj->color;
    return world->bg_color;
}