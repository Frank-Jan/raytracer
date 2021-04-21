#include "GaussianRandom.h"
#include <random>


GaussianRandom::GaussianRandom() :
dis(0.5, 0.5)
{
    std::random_device rd;
    gen.seed(rd());
}

void GaussianRandom::sample_unit_square(Point2D& pp, const int& p, const int& q)
{
    pp.x = dis(gen);
    pp.y = dis(gen);
}

FLOAT GaussianRandom::sample()
{
    return dis(gen);
}
