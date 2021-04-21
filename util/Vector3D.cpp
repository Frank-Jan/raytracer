#include "Vector3D.h"
#include <cmath>


FLOAT Vector3D::length() const
{
    return std::sqrt((*this)[Plane::x]*(*this)[Plane::x] +
                        (*this)[Plane::y]*(*this)[Plane::y] +
                        (*this)[Plane::z]*(*this)[Plane::z]);
}

FLOAT Vector3D::length_sqr() const
{
    return (*this)[Plane::x]*(*this)[Plane::x] +
           (*this)[Plane::y]*(*this)[Plane::y] +
           (*this)[Plane::z]*(*this)[Plane::z];
}