#ifndef RAYTRACER_AMBIENTOCCLUDER_H
#define RAYTRACER_AMBIENTOCCLUDER_H

#include "Light.h"
#include "Color.h"
#include "Vector3D.h"

class Sampler;


class AmbientOccluder : public Light
{
public:
    explicit AmbientOccluder(const Color& c, FLOAT ls);
    AmbientOccluder(FLOAT r, FLOAT g, FLOAT b, FLOAT ls);

    ~AmbientOccluder();

    void set_sampler(Sampler* sampler);

    virtual Vector3D get_direction(const ShadeRec& sr);

    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

    virtual Color L(const ShadeRec& sr);

private:
    Vector3D u,v,w;
    Sampler* sampler;
    FLOAT min_amount;
    FLOAT ls;
    Color color;
};


#endif //RAYTRACER_AMBIENTOCCLUDER_H
