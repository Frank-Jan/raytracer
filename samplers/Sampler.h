#ifndef RAYTRACER_SAMPLER_H
#define RAYTRACER_SAMPLER_H

#include "Point2D.h"
#include "Vector3D.h"
#include "constants.h"

class Sampler
{
public:
    virtual ~Sampler() = default;

    virtual void sample_unit_square(Point2D&, const int& p=0, const int& q=0) = 0;   // get next sample on unit square

    void sample_unit_disk(Point2D&, const int& p=0, const int& q=0);     // get next sample on unit disk

    Vector3D sample_hemisphere(const Point2D&, const FLOAT e = 1.0);

    Vector3D sample_hemisphere(const FLOAT e = 1.0);

    virtual FLOAT sample() = 0;

    virtual void set_num_sampes_sqrt(int) = 0;
};


#endif //RAYTRACER_SAMPLER_H
