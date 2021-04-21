#ifndef RAYTRACER_REGULAR_H
#define RAYTRACER_REGULAR_H

#include "Sampler.h"
#include <vector>

class Regular : public Sampler
{
public:
    Regular(int num_samples_sqrt = 1);

    void  inline sample_unit_square(Point2D&, const int& p, const int& q) final;

    FLOAT sample();

    void set_num_sampes_sqrt(int);

private:
    int num_samples_sqrt;
};


#endif //RAYTRACER_REGULAR_H
