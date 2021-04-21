#ifndef RAYTRACER_PHONG_H
#define RAYTRACER_PHONG_H

#include "Material.h"
#include "constants.h"

class Color;
class ShadeRec;
class Lambertian;
class GlossySpecular;


class Phong : public Material
{
public:
    Phong();

    ~Phong();

    void set_ka(FLOAT k);

    void set_kd(FLOAT k);

    void set_ks(FLOAT k);

    void set_exp(FLOAT e);

    void set_cd(const Color& c);

    void set_cd(FLOAT r, FLOAT g, FLOAT b);

    virtual Color shade(ShadeRec& sr) const;

    virtual Color area_light_shade(ShadeRec& sr) const;

private:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;
    GlossySpecular* specular_brdf;
};


#endif //RAYTRACER_PHONG_H
