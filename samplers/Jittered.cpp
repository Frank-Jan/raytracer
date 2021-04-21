#include "Jittered.h"

Jittered::Jittered(int num_samples_sqrt) :
num_samples_sqrt(num_samples_sqrt),
dis(0.0, 1.0)
{
    std::random_device rd;
    gen.seed(rd());
}

void inline Jittered::sample_unit_square(Point2D &pp, const int &p, const int &q)
{
    pp.x = (p + dis(gen))/num_samples_sqrt;
    pp.y = (q + dis(gen))/num_samples_sqrt;
}

FLOAT Jittered::sample()
{
    return dis(gen);
}

void Jittered::set_num_sampes_sqrt(int n)
{
    num_samples_sqrt = n;
};