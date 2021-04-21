#include "RayCast.h"
#include "Color.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "World.h"
#include "Materials/Matte.h"
#include "Triangle.h"


Color RayCast::trace_ray(const Ray& ray) const
{
    ShadeRec sr = world->hit_object(ray);

    if(sr.hit) {
//        sr.ray = ray;
//        return sr.material->shade(sr);
        return sr.triangle->c;
    }
    return world->bg_color;
}

Color RayCast::trace_ray(const Ray ray, const int depth) const
{
    ShadeRec sr = world->hit_object(ray);

    if(sr.hit) {
        sr.ray = ray;
        return sr.material->shade(sr);
    }
    return world->bg_color;
}

Color RayCast::trace_ray(const Ray ray, FLOAT& tmin, const int depth) const
{
    return color::black;
}