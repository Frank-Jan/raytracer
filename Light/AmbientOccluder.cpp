#include "AmbientOccluder.h"
#include "Sampler.h"
#include "ShadeRec.h"
#include "world/SimpleWorld.h"
#include "Triangle.h"


AmbientOccluder::AmbientOccluder(const Color& c, FLOAT _ls) :
sampler(nullptr), color(c), ls(_ls)
{ }

AmbientOccluder::AmbientOccluder(FLOAT r, FLOAT g, FLOAT b, FLOAT _ls) :
sampler(nullptr), color(r,g,b), ls(_ls)
{ }

AmbientOccluder::~AmbientOccluder()
{
    delete sampler;
}

void AmbientOccluder::set_sampler(Sampler *_sampler)
{
    delete sampler;
    sampler = _sampler;
}

Vector3D AmbientOccluder::get_direction(const ShadeRec &sr)
{
    Vector3D sp = sampler->sample_hemisphere(1);
    return sp.x() * u + sp.y() * v + sp.z() * w;
}

bool AmbientOccluder::in_shadow(const Ray &ray, const ShadeRec &sr) const
{
    FLOAT t;
//    for(const Triangle* geo : sr.world.objects) {
//        if(geo->shadow_hit(ray, t))
//            return true;
//    }
    return false;
}

Color AmbientOccluder::L(const ShadeRec &sr)
{
    w = sr.normal;
    // jitter up vector in case the normal is vertical
    v = w^Vector3D(0.0072, 1.0, 0.0034);
    v._normalize();
    u = v^w;

    Ray shadowRay;
    shadowRay.o = sr.hit_point;
    shadowRay.d = get_direction(sr);
    if(in_shadow(shadowRay, sr))
        return (min_amount * ls * color);
    return ls * color;
}
