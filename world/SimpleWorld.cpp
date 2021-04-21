#include "Triangle.h"
#include "Light.h"
#include "SimpleWorld.h"
#include "constants.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "Ambient.h"
#include <iostream>
#include "Logger.h"


SimpleWorld::SimpleWorld(std::vector<Triangle>& triangles) :
objects(triangles)
{
    LOGGER.worldType = "Simple World";
    LOGGER.objects = triangles.size();
}


ShadeRec SimpleWorld::hit_object(const Ray& ray){
    ShadeRec sr(this);
    FLOAT t = hugeValue;
    FLOAT tmin = hugeValue;
    Vector3D normal;
    Material* material;
    Triangle* tr = nullptr;

    for(Triangle& obj : objects)
    {
        if(obj.hit_object(ray, t, sr) && t < tmin && t > kEpsilon)
        {
            tr = &obj;
            tmin = t;
            normal = sr.normal;
            sr.hit = true;
            material = sr.material;
        }
    }

    if(sr.hit) {
//        sr.obj = _obj;
        sr.material = material;
        sr.tmin = tmin;
        sr.normal = normal;
        sr.hit_point = ray.o + tmin * ray.d;
        sr.triangle = tr;
    }

    return sr;
}
//
//// are points p0 and p1 visible to eachother
//inline FLOAT SimpleWorld::V(const Vector3D& p0, const Vector3D& p1)
//{
//    Vector3D v = (p1-p0);
//    FLOAT d = v.length_sqr();
//    Ray ray(p0, v/d);
//    ShadeRec sr = hit(ray);
//
//    if(sr.hit) {
//        if(sr.tmin*sr.tmin < d)
//            return 0.0; // invisible
//    }
//
//    return 1.0; // visible
//}
//
//void SimpleWorld::set_ambient(Light *_ambient)
//{
//    delete ambient;
//    ambient = _ambient;
//}
//
//void SimpleWorld::add_object(Triangle* geo) {
//    // check if geometric is already present
//    for(Triangle* g : objects) {
//        if(g == geo)
//            return;
//    }
//
//    // add geometric
//    objects.push_back(geo);
//}