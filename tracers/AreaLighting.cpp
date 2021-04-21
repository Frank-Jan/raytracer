//#include "AreaLighting.h"
//#include "Color.h"
//#include "Ray.h"
//#include "ShadeRec.h"
//#include "constants.h"
//#include "SimpleWorld.h"
//#include "Material.h"
//
//
//Color AreaLighting::trace_ray(const Ray &ray) const
//{
//
//    return trace_ray(ray, 0);
//}
//
//Color AreaLighting::trace_ray(const Ray ray, const int depth) const
//{
//    ShadeRec sr = world->hit(ray);
//
//    if(sr.hit) {
//        sr.ray = ray;
//        return sr.material->area_light_shade(sr);
//    }
//
//    return sr.world.bg_color;
//}
//
//Color AreaLighting::trace_ray(const Ray ray, float &tmin, const int depth) const
//{
//    return color::black;
//}
