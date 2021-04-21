//#include "AreaLight.h"
//#include "ShadeRec.h"
//#include "SimpleWorld.h"
//
//
//AreaLight::AreaLight() :
//Light(),
//obj(nullptr),
//material(nullptr)
//{
//
//}
//
//AreaLight::AreaLight(Geometric *geo)
//{
//    obj = geo;
//    if(obj != nullptr) {
//        material = obj->mat;
//    }
//}
//
//AreaLight::~AreaLight()
//{ }
//
//Vector3D AreaLight::get_direction(const ShadeRec &sr)
//{
//    sample_point = obj->sample();
//    normal = obj->get_normal(sample_point);
//    wi = sample_point - sr.hit_point;
//    wi._normalize();
//    return wi;
//}
//
//Color AreaLight::L(const ShadeRec &sr)
//{
//    FLOAT ndotd = -normal * sr.ray.d;
//
//    if(ndotd > 0.0) // check if hitting the correct side of the light
//        return material->get_Le(sr);
//    return color::black;
//}
//
//bool AreaLight::in_shadow(const Ray &ray, const ShadeRec &sr) const
//{
//    FLOAT t;
//    FLOAT ts = (sample_point - ray.o) * ray.d;
//
//    for(const Geometric *geo : sr.world.objects) {
//        if(geo->shadow_hit(ray, t) && t < ts)
//            return true;
//    }
//    return false;
//}
//
//// calculates G without n*wij which is done in the matte::area_light_shade
//FLOAT AreaLight::G(const ShadeRec &sr)
//{
//    FLOAT ndotd = -normal * sr.ray.d;
//    FLOAT d2 = sample_point.distance_sqr(sr.hit_point);
//
//    return ndotd/d2;
//}
//
//FLOAT AreaLight::pdf(ShadeRec &sr)
//{
//    return obj->pdf(sr);
//}
