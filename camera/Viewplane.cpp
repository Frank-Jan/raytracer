#include "Viewplane.h"
#include <cmath>

Viewplane::Viewplane(int hres, int vres, FLOAT s, unsigned int num_samples) :
hres(hres), vres(vres), s(s)
{
    this->num_samples_sqrt = (int)sqrt(num_samples);
    this->num_samples = num_samples_sqrt * num_samples_sqrt;
}
