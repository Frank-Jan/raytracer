#include "Sampler.h"
#include <cmath>

inline void map_samples_to_unit_disk(Point2D&);    // redistributes units from the unit square (x,y) : [-1,1]^2 to the unit disk (x,y) : [-1,1]^2 x^2 + y^2 < 1
inline Vector3D map_samples_to_hemisphere(const Point2D&, const FLOAT e);

void Sampler::sample_unit_disk(Point2D& sp, const int& p, const int& q)
{
    sample_unit_square(sp, p, q);
    map_samples_to_unit_disk(sp);
}

Vector3D Sampler::sample_hemisphere(const Point2D& sp, const FLOAT e)
{
    return map_samples_to_hemisphere(sp, e);
}

Vector3D Sampler::sample_hemisphere(const FLOAT e)
{
    Point2D sp(0,0);
     sample_unit_square(sp, 0,0);
    return map_samples_to_hemisphere(sp, e);
}

Vector3D map_samples_to_hemisphere(const Point2D& sp, const FLOAT e)
{
    FLOAT cos_phi = cos(2 * M_PI * sp.x);
    FLOAT sin_phi = sin(2 * M_PI * sp.y);
    FLOAT cos_theta = pow(1.0 - sp.y, 1.0 / (e + 1.0));
    FLOAT sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    FLOAT pu = sin_theta * cos_phi;
    FLOAT pv = sin_theta * sin_phi;
    FLOAT pw = cos_theta;

    return Vector3D(pu, pv, pw);
}

void map_samples_to_unit_disk(Point2D& sp)
{
    FLOAT r, phi;
    sp.x = 2*sp.x - 1.0;
    sp.y = 2*sp.y - 1.0;

    if(sp.x > -sp.y) {
        if(sp.x > sp.y) {
            r = sp.x;
            phi = sp.y/sp.x;
        }
        else {
            r = sp.y;
            phi = 2 - sp.x/sp.y;
        }
    }
    else {
        if(sp.x < sp.y) {
            r = -sp.x;
            phi = 4 + sp.y/sp.x;
        }
        else {
            r = -sp.y;
            if(sp.y != 0.0)
                phi = 6-sp.x/sp.y;
            else
                phi = 0;
        }
    }

    phi *=  M_PI_4; // pi/4 hardcoded from cmath
    sp.x = r * cos(phi);
    sp.y = r * sin(phi);
}



