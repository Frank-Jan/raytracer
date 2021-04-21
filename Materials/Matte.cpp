#include "Matte.h"
#include "Color.h"
#include "ShadeRec.h"
#include "Lambertian.h"
#include "Light.h"
#include "world/SimpleWorld.h"

#include <typeinfo>

Matte::Matte() :
Material(),
ambient_brdf(new Lambertian),
diffuse_brdf(new Lambertian)
{ }

Matte::~Matte() {
    delete ambient_brdf;
    delete diffuse_brdf;
}

void Matte::set_ka(FLOAT k)
{
    ambient_brdf->kd = k;
}

void Matte::set_kd(FLOAT k)
{
    diffuse_brdf->kd = k;
}

void Matte::set_cd(const Color& c)
{
    ambient_brdf->cd = c;
    diffuse_brdf->cd = c;
}

void Matte::set_cd(FLOAT r, FLOAT g, FLOAT b)
{
    Color c(r,g,b);
    ambient_brdf->cd = c;
    diffuse_brdf->cd = c;
}

Color Matte::shade(ShadeRec& sr) const{
    Vector3D wo = -sr.ray.d;
//    Color L = ambient_brdf->rho(sr, wo) * sr.world->ambient->L(sr);
    Color L;
    Vector3D wi;
    FLOAT ndotwi;
//    for(Light* l : sr.world.lights) {
//        wi = l->get_direction(sr);
//        ndotwi = sr.normal * wi;
//
//        if(ndotwi > 0.0) {
//            bool in_shadow = false;
//
//            if(l->casts_shadows()) {
//                Ray shadowRay(sr.hit_point, wi);
//                in_shadow = l->in_shadow(shadowRay, sr);
//            }
//
//            if(!in_shadow) {
//                L += diffuse_brdf->f(sr, wo, wi) * l->L(sr) * ndotwi;
//            }
//        }
//    }
    return L;
}

Color Matte::area_light_shade(ShadeRec &sr) const
{
    Vector3D wo = -sr.ray.d;
//    Color L = ambient_brdf->rho(sr, wo) * sr.world.ambient->L(sr);
    Color L;
    Vector3D wi;
    FLOAT ndotwi;
//    for(Light* l : sr.world.lights) {
//        wi = l->get_direction(sr);
//        ndotwi = sr.normal * wi;
//
//        if(ndotwi > 0.0) {
//            bool in_shadow = false;
//
//            if(l->casts_shadows()) {
//                Ray shadowRay(sr.hit_point, wi);
//                in_shadow = l->in_shadow(shadowRay, sr);
//            }
//
//            if(!in_shadow) {
//                L += diffuse_brdf->f(sr, wo, wi) * l->L(sr) * l->G(sr) * ndotwi / l->pdf(sr);
//            }
//        }
//    }
    return L;
}
