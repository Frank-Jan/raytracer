#include "UniformRandom.h"
#include <random>


UniformRandom::UniformRandom(FLOAT min, FLOAT max) :
dis(min, max)
{
    std::random_device rd;
    gen.seed(rd());
}

void UniformRandom::sample_unit_square(Point2D& pp, const int& p, const int& q)
{
    pp.x = dis(gen);
    pp.y = dis(gen);
}

FLOAT UniformRandom::sample()
{
    return dis(gen);
}
