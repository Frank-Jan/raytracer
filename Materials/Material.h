#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "constants.h"

class Color;
class ShadeRec;

class Material
{
public:

    virtual ~Material() = default;

    virtual Color shade(ShadeRec& sr) const = 0;
//    Color whitted_shade(const ShadeRec& sr) const;
    virtual Color area_light_shade(ShadeRec& sr) const = 0;
//    Color path_shade(const ShadeRec& sr) const;

    virtual Color get_Le(const ShadeRec& sr) const;   // normal materials do not emit light -> return color::black
};


#endif //RAYTRACER_MATERIAL_H
