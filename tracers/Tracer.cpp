#include "Tracer.h"
#include "Ray.h"
#include "Color.h"
#include "Triangle.h"
#include "ShadeRec.h"
#include "World.h"
#include "constants.h"
#include "Material.h"

Tracer::Tracer(World *_world) :
world(_world)
{ }

//Color Tracer::trace_ray(const ShadeRec& sr) const
Color Tracer::trace_ray(const Ray& ray) const
{
    ShadeRec sr = world->hit_object(ray);
    if(sr.hit)
        return sr.triangle->c;
    return world->bg_color;
}

Color Tracer::trace_ray(const Ray ray, const int depth) const
{
    return color::black;
}

Color Tracer::trace_ray(const Ray ray, FLOAT& tmin, const int depth) const
{
    return color::black;
}