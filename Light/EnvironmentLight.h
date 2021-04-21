#ifndef RAYTRACER_ENVIRONMENTLIGHT_H
#define RAYTRACER_ENVIRONMENTLIGHT_H

#include "Light.h"
#include "Vector3D.h"

class Sampler;
class Material;
class Ray;
class ShadeRec;
class Color;

class EnvironmentLight : public Light
{
public:
EnvironmentLight();

virtual ~EnvironmentLight() = default;

virtual Vector3D get_direction(const ShadeRec& sr);

virtual Color L(const ShadeRec& sr);

virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const ;

virtual FLOAT G(const ShadeRec& sr);

virtual FLOAT pdf(ShadeRec& sr);

void set_sampler(Sampler* sampler);

void set_material(Material* material);

private:
    Sampler* sampler;
    Material* material;
    Vector3D u,v,w;
    Vector3D wi;
};


#endif //RAYTRACER_ENVIRONMENTLIGHT_H
