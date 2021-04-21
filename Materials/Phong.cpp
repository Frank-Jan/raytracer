#include "Phong.h"
#include "Lambertian.h"
#include "GlossySpecular.h"
#include "ShadeRec.h"
#include "world/SimpleWorld.h"
#include "Ambient.h"

Phong::Phong() :
diffuse_brdf(new Lambertian()),
ambient_brdf(new Lambertian()),
specular_brdf(new GlossySpecular())
{
    diffuse_brdf->kd = 0.6;
    specular_brdf->ks = 0.25;
}

Phong::~Phong()
{
    delete diffuse_brdf;
    delete ambient_brdf;
    delete specular_brdf;
}

void Phong::set_ka(FLOAT k)
{
    ambient_brdf->kd = k;
}

void Phong::set_kd(FLOAT k)
{
    if(k > diffuse_brdf->kd) {
        if(k+specular_brdf->ks > 1.0) {
            specular_brdf->ks = 1 - k;
        }
    }
    diffuse_brdf->kd = k;
}

void Phong::set_ks(FLOAT k)
{
    if(k > specular_brdf->ks) {
        if(k+diffuse_brdf->kd > 1.0) {
            diffuse_brdf->kd = 1 - k;
        }
    }
    specular_brdf->ks = k;
}

void Phong::set_exp(FLOAT e)
{
    if(e >= 1.0)
        specular_brdf->exp = e;
}

void Phong::set_cd(const Color &c)
{
    specular_brdf->cd = c;
    diffuse_brdf->cd = c;
    ambient_brdf->cd = c;
}

void Phong::set_cd(FLOAT r, FLOAT g, FLOAT b)
{
    set_cd(Color(r,g,b));
}

Color Phong::shade(ShadeRec &sr) const
{
    Vector3D wo = -sr.ray.d;
//    Color L = ambient_brdf->rho(sr, wo) * sr.world.ambient->L(sr);
    Color L;
    Vector3D wi;
    FLOAT ndotwi;
//    for(Light* const l : sr.world.lights) {
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
//                L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * l->L(sr) * ndotwi;
//            }
//        }
//    }
    return L;
}

Color Phong::area_light_shade(ShadeRec &sr) const
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
//                L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * l->L(sr) * l->G(sr) * ndotwi / l->pdf(sr);
//            }
//        }
//    }
    return L;
}