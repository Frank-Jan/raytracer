#include "Directional.h"
#include "world/SimpleWorld.h"
#include "Triangle.h"
#include "ShadeRec.h"

Directional::Directional(const Vector3D &direction, const Color &c, FLOAT ls) :
d(direction), color(c), ls(ls)
{
    d._normalize();
}

Directional::Directional(const Vector3D &direction, FLOAT r, FLOAT g, FLOAT b, FLOAT ls) :
d(direction), color(r,g,b), ls(ls)
{
    d._normalize();
}

Vector3D Directional::get_direction(const ShadeRec &sr) const
{
    return -d;
}

Color Directional::L(const ShadeRec &sr) const
{
    return ls*color;
}

bool Directional::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
    FLOAT t;
//    for(Triangle* const obj : sr.world.objects)
//    {
//        if(obj->shadow_hit(ray, t))
//            return true;
//    }
    return false;
}