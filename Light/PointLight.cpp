#include "PointLight.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "world/SimpleWorld.h"
#include "Triangle.h"

PointLight::PointLight(const Vector3D& location, const Color &c, FLOAT ls) :
color(c), ls(ls), o(location)
{ }

PointLight::PointLight(const Vector3D& location, FLOAT r, FLOAT g, FLOAT b, FLOAT ls) :
color(r,g,b), ls(ls), o(location)
{ }

Vector3D PointLight::get_direction(const ShadeRec &sr)
{
    return (o - sr.hit_point).normalize();  // towards the light
}

Color PointLight::L(const ShadeRec &sr)
{
    return ls*color;
}

bool PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
    FLOAT t;
    FLOAT d = (o-ray.o).length();

//    for(Triangle* const obj : sr.world.objects)
//    {
//        if(obj->shadow_hit(ray, t) && t < d)
//            return true;
//    }
    return false;
}
