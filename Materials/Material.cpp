#include "Material.h"
#include "constants.h"
#include "Color.h"


Color Material::get_Le(const ShadeRec& sr) const {
    return color::black;
}