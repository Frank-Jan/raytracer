#include "Triangle.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "BBox.h"
#include "constants.h"
#include "Logger.h"
#include <cmath>

using std::min, std::max;

Triangle::Triangle(const Vector3D &_v0, const Vector3D &_v1, const Vector3D &_v2) :
v0(_v0), v1(_v1), v2(_v2), id(++idgen)
//material{nullptr}
{ }

Triangle::Triangle(const Triangle& rhs) :
v0(rhs.v0), v1(rhs.v1), v2(rhs.v2), id(rhs.id), c(rhs.c)
{ }

Triangle::Triangle(const Triangle&& rhs) :
v0(rhs.v0), v1(rhs.v1), v2(rhs.v2), id(rhs.id), c(rhs.c)
{ }

Triangle& Triangle::operator=(const Triangle& rhs)
{
    v0 = rhs.v0;
    v1 = rhs.v1;
    v2 = rhs.v2;
    id = rhs.id;
    return *this;
}

bool Triangle::hit_object(const Ray &ray, FLOAT &tmin, ShadeRec &sr)
{
//    if(ray.d == hitbyDir)
//        return false;
//    hitbyDir = ray.d;
    /*
     *      M*{beta,gamma,t} = Y
     *      M = [x1,x2,x3]
     *          [y1,y2,y3]
     *          [z1,z2,z3]
     *      Y = {Y1,Y2,Y3}
     *
     *      M and Y are known
     *      solve for beta, gamma, t
     */
    LOGGER.intersections++;

    FLOAT a = v0.x() - v1.x(), b = v0.x() - v2.x(), c = ray.d.x(), d = v0.x() - ray.o.x();
    FLOAT e = v0.y() - v1.y(), f = v0.y() - v2.y(), g = ray.d.y(), h = v0.y() - ray.o.y();
    FLOAT i = v0.z() - v1.z(), j = v0.z() - v2.z(), k = ray.d.z(), l = v0.z() - ray.o.z();

    FLOAT m = f*k - g*j, n = h*k - g*l, p = f*l - h*j;
    FLOAT q = g*i - e*k, s = e*j - f*i;

    FLOAT invD = 1.0 / (a*m + b*q + c*s); // inverted discriminant

    FLOAT e1 = d*m - b*n - c*p;
    FLOAT beta = e1 * invD;

    if(beta < 0.0)
        return false;

    FLOAT r = e*l - h*i;
    FLOAT e2 = a*n + d*q + c*r;
    FLOAT gamma = e2 * invD;

    if(gamma < 0.0)
        return false;

    if(gamma + beta > 1.0)
        return false;

    FLOAT e3 = a*p - b*r + d*s;
    FLOAT t = e3 * invD;

    if(t < kEpsilon or t > tmin)
        return false;

    tmin = t;
    sr.tmin = tmin;
    sr.triangle = this;
    return true;
}

bool Triangle::hit_object(const Ray &ray, ShadeRec &sr)
{
//    if(ray.d == hitbyDir)
//        return false;
//    hitbyDir = ray.d;
    /*
     *      M*{beta,gamma,t} = Y
     *      M = [x1,x2,x3]
     *          [y1,y2,y3]
     *          [z1,z2,z3]
     *      Y = {Y1,Y2,Y3}
     *
     *      M and Y are known
     *      solve for beta, gamma, t
     */
    LOGGER.intersections++;

    FLOAT a = v0.x() - v1.x(), b = v0.x() - v2.x(), c = ray.d.x(), d = v0.x() - ray.o.x();
    FLOAT e = v0.y() - v1.y(), f = v0.y() - v2.y(), g = ray.d.y(), h = v0.y() - ray.o.y();
    FLOAT i = v0.z() - v1.z(), j = v0.z() - v2.z(), k = ray.d.z(), l = v0.z() - ray.o.z();

    FLOAT m = f*k - g*j, n = h*k - g*l, p = f*l - h*j;
    FLOAT q = g*i - e*k, s = e*j - f*i;

    FLOAT invD = 1.0 / (a*m + b*q + c*s); // inverted discriminant

    FLOAT e1 = d*m - b*n - c*p;
    FLOAT beta = e1 * invD;

    if(beta < 0.0)
        return false;

    FLOAT r = e*l - h*i;
    FLOAT e2 = a*n + d*q + c*r;
    FLOAT gamma = e2 * invD;

    if(gamma < 0.0)
        return false;

    if(gamma + beta > 1.0)
        return false;

    FLOAT e3 = a*p - b*r + d*s;
    FLOAT t = e3 * invD;

    if(t < kEpsilon || t >= sr.tmin)
        return false;

    sr.hit = true;
    sr.tmin = t;
    sr.triangle = this;
    return true;
}

bool Triangle::shadow_hit(const Ray &ray, FLOAT &tmin) const {
//    hitby = &ray;

    LOGGER.intersections++;

    FLOAT a = v0.x() - v1.x(), b = v0.x() - v2.x(), c = ray.d.x(), d = v0.x() - ray.o.x();
    FLOAT e = v0.y() - v1.y(), f = v0.y() - v2.y(), g = ray.d.y(), h = v0.y() - ray.o.y();
    FLOAT i = v0.z() - v1.z(), j = v0.z() - v2.z(), k = ray.d.z(), l = v0.z() - ray.o.z();

    FLOAT m = f*k - g*j, n = h*k - g*l, p = f*l - h*j;
    FLOAT q = g*i - e*k, s = e*j - f*i;

    FLOAT invD = 1.0 / (a*m + b*q + c*s); // inverted discriminant

    FLOAT e1 = d*m - b*n - c*p;
    FLOAT beta = e1 * invD;

    if(beta < 0.0)
        return false;

    FLOAT r = e*l - h*i;
    FLOAT e2 = a*n + d*q + c*r;
    FLOAT gamma = e2 * invD;

    if(gamma < 0.0)
        return false;

    if(gamma + beta > 1.0)
        return false;

    FLOAT e3 = a*p - b*r + d*s;
    FLOAT t = e3 * invD;

    if(t < kEpsilon || t >= tmin)
        return false;
    tmin = t;
    return true;
}

BBox Triangle::get_BBox() const
{
    FLOAT xmin, ymin, zmin;
    FLOAT xmax, ymax, zmax;

    xmin = min(v0.x(), min(v1.x(), v2.x()));
    ymin = min(v0.y(), min(v1.y(), v2.y()));
    zmin = min(v0.z(), min(v1.z(), v2.z()));

    xmax = max(v0.x(), max(v1.x(), v2.x()));
    ymax = max(v0.y(), max(v1.y(), v2.y()));
    zmax = max(v0.z(), max(v1.z(), v2.z()));
    return BBox(xmin-kEpsilon, ymin-kEpsilon, zmin-kEpsilon,
                xmax+kEpsilon, ymax+kEpsilon, zmax+kEpsilon);
}
