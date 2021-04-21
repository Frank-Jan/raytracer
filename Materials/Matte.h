#ifndef RAYTRACER_MATTE_H
#define RAYTRACER_MATTE_H

#include "Material.h"


class Color;
class ShadeRec;
class Lambertian;

class Matte : public Material
{
public:
    Matte();

    ~Matte();

    void set_ka(FLOAT k);

    void set_kd(FLOAT k);

    void set_cd(const Color& c);
    void set_cd(FLOAT r, FLOAT g, FLOAT b);

    Color shade(ShadeRec& sr) const;

    Color area_light_shade(ShadeRec& sr) const;

private:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;
};



#endif //RAYTRACER_MATTE_H
