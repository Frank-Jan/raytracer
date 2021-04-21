//#ifndef RAYTRACER_EMISSIVE_H
//#define RAYTRACER_EMISSIVE_H
//
//#include "Material.h"
//#include "Color.h"
//
//class Emissive : public Material
//{
//public:
//    Emissive() = default;
//    ~Emissive() = default;
//
//    void set_radiance(FLOAT _ls) { ls = _ls; }
//    void set_color(const Color& c) { ce = c; }
//    void set_color(FLOAT r, FLOAT g, FLOAT b) { ce = Color(r,g,b); }
//
//    virtual Color get_Le(const ShadeRec& sr) const;
//
//    Color shade(ShadeRec& sr) const;
//
//    Color area_light_shade(ShadeRec& sr) const;
//
//private:
//    FLOAT ls;      // radiance scaling factor
//    Color ce;       // emitted color
//};
//
//
//#endif //RAYTRACER_EMISSIVE_H
