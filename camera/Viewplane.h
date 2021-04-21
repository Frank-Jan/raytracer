#ifndef RAYTRACER_VIEWPLANE_H
#define RAYTRACER_VIEWPLANE_H

#include "constants.h"

class Viewplane {
public:
    int hres;   // Horizontal resolution
    int vres;   // Vertical resolution
    FLOAT s;   // Pixel size
    int num_samples_sqrt;
    int num_samples;

    Viewplane(int hres, int vres, FLOAT s, unsigned int num_samples=1);
};


#endif //RAYTRACER_VIEWPLANE_H
