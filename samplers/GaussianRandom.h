#ifndef RAYTRACER_GAUSSIANRANDOM_H
#define RAYTRACER_GAUSSIANRANDOM_H

#include <random>
#include "Sampler.h"

class GaussianRandom : public Sampler
{
public:
    GaussianRandom();

    void inline sample_unit_square(Point2D&, const int& p, const int& q) final;

    FLOAT sample();

    void set_num_sampes_sqrt(int) {};
private:
    std::mt19937 gen;
    std::normal_distribution<> dis;

};


#endif //RAYTRACER_GAUSSIANRANDOM_H
