#include "cmath"
#include "BBox.h"
#include "Vector3D.h"
#include "Ray.h"
#include "constants.h"


using std::max, std::min;

BBox::BBox(const Vector3D &p, const Vector3D &P)
{
    x0 = min(p.x(), P.x());
    y0 = min(p.y(), P.y());
    z0 = min(p.z(), P.z());

    x1 = max(p.x(), P.x());
    y1 = max(p.y(), P.y());
    z1 = max(p.z(), P.z());
}

BBox::BBox(FLOAT _x0, FLOAT _y0, FLOAT _z0, FLOAT _x1, FLOAT _y1, FLOAT _z1)
{
    x0 = min(_x0, _x1);
    y0 = min(_y0, _y1);
    z0 = min(_z0, _z1);

    x1 = max(_x0, _x1);
    y1 = max(_y0, _y1);
    z1 = max(_z0, _z1);
}

bool BBox::hit(const Ray &ray) const
{
    FLOAT ox = ray.o.x(); FLOAT oy = ray.o.y(); FLOAT oz = ray.o.z();
    FLOAT dx = ray.d.x(); FLOAT dy = ray.d.y(); FLOAT dz = ray.d.z();

    FLOAT tx_min, ty_min, tz_min;
    FLOAT tx_max, ty_max, tz_max;

    FLOAT a = 1/dx;
    if(a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
    }
    else {
        tx_max = (x0 - ox) * a;
        tx_min = (x1 - ox) * a;
    }

    FLOAT b = 1/dy;
    if(b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
    }
    else {
        ty_max = (y0 - oy) * b;
        ty_min = (y1 - oy) * b;
    }

    FLOAT c = 1/dz;
    if(c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
    }
    else {
        tz_max = (z0 - oz) * c;
        tz_min = (z1 - oz) * c;
    }

    FLOAT t0; // highest of t min
    FLOAT t1; // lowest of t max

    t0 = max(tx_min, max(ty_min, tz_min));
    t1 = min(tx_max, min(ty_max, tz_max));

    return t0 < t1 && t1 > kEpsilon;
}

bool BBox::clipRay(const Ray& ray, FLOAT& t_near, FLOAT& t_far) const
{
    FLOAT ox = ray.o.x(); FLOAT oy = ray.o.y(); FLOAT oz = ray.o.z();
    FLOAT dx = ray.d.x(); FLOAT dy = ray.d.y(); FLOAT dz = ray.d.z();

    FLOAT tx_min, ty_min, tz_min;
    FLOAT tx_max, ty_max, tz_max;

    FLOAT a = 1/dx;
    if(a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
    }
    else {
        tx_max = (x0 - ox) * a;
        tx_min = (x1 - ox) * a;
    }

    FLOAT b = 1/dy;
    if(b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
    }
    else {
        ty_max = (y0 - oy) * b;
        ty_min = (y1 - oy) * b;
    }

    FLOAT c = 1/dz;
    if(c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
    }
    else {
        tz_max = (z0 - oz) * c;
        tz_min = (z1 - oz) * c;
    }

    FLOAT t0; // highest of t min
    FLOAT t1; // lowest of t max

    t0 = max(tx_min, max(ty_min, tz_min));
    t1 = min(tx_max, min(ty_max, tz_max));

    bool hit = t0 < t1 && t1 > kEpsilon;
    if(hit) {
        if (t_near < t0)
            t_near = t0;
        if (t_far > t1)
            t_far = t1;
        return true;
    }
    return false;
}

bool overlapping(const BBox& a, const BBox& b)
{
    return  (a.getSmall(Plane::x) > b.getBig(Plane::x) |
            a.getSmall(Plane::y) > b.getBig(Plane::y) |
            a.getSmall(Plane::z) > b.getBig(Plane::z)) ||

            (b.getSmall(Plane::x) > a.getBig(Plane::x) |
            b.getSmall(Plane::y) > a.getBig(Plane::y) |
            b.getSmall(Plane::z) > a.getBig(Plane::z));
}
