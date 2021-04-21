#ifndef RAYTRACER_UNIFORMRANDOM_H
#define RAYTRACER_UNIFORMRANDOM_H

#include <random>
#include "Sampler.h"
#include "constants.h"

class UniformRandom : public Sampler
{
public:
    UniformRandom(FLOAT min=0.0, FLOAT max=1.0);

    void  inline sample_unit_square(Point2D&, const int& p, const int& q) final;

    FLOAT sample();

    void set_num_sampes_sqrt(int) {};
private:
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
};


#endif //RAYTRACER_UNIFORMRANDOM_H
