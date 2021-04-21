#ifndef RAYTRACER_JITTERED_H
#define RAYTRACER_JITTERED_H

#include "Sampler.h"
#include <random>

class Jittered : public Sampler
{
public:
    Jittered(int num_samples_sqrt = 1);

    void  inline sample_unit_square(Point2D&, const int& p, const int& q) final;

    FLOAT sample();

    void set_num_sampes_sqrt(int);

private:
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
    int num_samples_sqrt;
};


#endif //RAYTRACER_JITTERED_H
