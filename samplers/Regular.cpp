#include "Regular.h"



Regular::Regular(int num_samples_sqrt) :
num_samples_sqrt(num_samples_sqrt)
{ }

void Regular::sample_unit_square(Point2D &pp, const int& p, const int& q)
{

    pp.x = (p + 0.5) / num_samples_sqrt;
    pp.y = (q + 0.5) / num_samples_sqrt;
}

FLOAT Regular::sample()
{
    return 0;
}

void Regular::set_num_sampes_sqrt(int n)
{
    num_samples_sqrt = n;
};