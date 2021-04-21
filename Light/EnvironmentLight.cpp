#include "EnvironmentLight.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "world/SimpleWorld.h"
#include "Vector3D.h"
#include "Point2D.h"
#include "Sampler.h"
#include "Material.h"
#include "Triangle.h"


EnvironmentLight::EnvironmentLight() :
Light(),
sampler(nullptr),
material(nullptr)
{ }

Vector3D EnvironmentLight::get_direction(const ShadeRec &sr)
{
    w = sr.normal;
    v = Vector3D(0.0034, 1.0, 0.0071) ^ w;
    v._normalize();
    u = v ^ w;
    Vector3D sp = sampler->sample_hemisphere();
    wi = sp.x()*u + sp.y()*v + sp.z()*w;

    return wi;
}

Color EnvironmentLight::L(const ShadeRec &sr)
{
    return material->get_Le(sr);
}

bool EnvironmentLight::in_shadow(const Ray &ray, const ShadeRec &sr) const
{
    FLOAT t;
//    for(const Triangle* geo : sr.world.objects) {
//        if(geo->shadow_hit(ray, t))
//            return true;
//    }
    return false;
}

FLOAT EnvironmentLight::G(const ShadeRec &sr)
{
    return 1.0;
}

FLOAT EnvironmentLight::pdf(ShadeRec &sr)
{
    return M_1_PI;
}

void EnvironmentLight::set_sampler(Sampler *_sampler)
{
    delete sampler;
    sampler = _sampler;
}

void EnvironmentLight::set_material(Material *_material)
{
    delete material;
    material = _material;
}
