#ifndef RAYTRACER_VECTOR3D_H
#define RAYTRACER_VECTOR3D_H

#include <array>
#include "constants.h"


enum Plane
{
    x = 0,  // a split with the x-axis
    y = 1,  // a split with the y-axis
    z = 2   // a split with the z-axis
};

class Vector3D : public std::array<FLOAT, 3>{
public:
    Vector3D() :
            std::array<FLOAT, 3>({0,0,0})
    { }

    Vector3D(FLOAT x, FLOAT y, FLOAT z) :
            std::array<FLOAT, 3>({x,y,z})
    { }

    inline FLOAT& x() { return this->operator[](0); };
    inline FLOAT& y() { return this->operator[](1); };
    inline FLOAT& z() { return this->operator[](2); };

    inline const FLOAT& x() const { return this->operator[](0); };
    inline const FLOAT& y() const { return this->operator[](1); };
    inline const FLOAT& z() const { return this->operator[](2); };

    Vector3D operator-(const Vector3D& rhs) const {
        return Vector3D(x() - rhs.x(), y() - rhs.y(), z() - rhs.z()); };

    Vector3D operator+(const Vector3D& rhs) const {
        return Vector3D(x() + rhs.x(), y() + rhs.y(), z() + rhs.z()); };

    FLOAT operator*(const Vector3D& rhs) const {
        return (x()*rhs.x() + y()*rhs.y() + z()*rhs.z()); };

    Vector3D operator^(const Vector3D& rhs) const {
        return Vector3D(
                y()*rhs.z() - z()*rhs.y(),
                z()*rhs.x() - x()*rhs.z(),
                x()*rhs.y() - y()*rhs.x()); };

    Vector3D operator*(const FLOAT& rhs) const {
        return Vector3D(x()*rhs, y()*rhs, z()*rhs); };

    Vector3D operator/(const FLOAT& rhs) const {
        return Vector3D(x()/rhs, y()/rhs, z()/rhs); };

    Vector3D& operator*=(const FLOAT& rhs) {
        x() *= rhs;
        y() *= rhs;
        z() *= rhs;
        return *this;
    }

    Vector3D& operator/=(const FLOAT& rhs) {
        x() /= rhs;
        y() /= rhs;
        z() /= rhs;
        return *this;
    }

    Vector3D normalize() const {
        FLOAT L = this->length();
        return Vector3D(x()/L, y()/L, z()/L);
    }
    Vector3D& _normalize() {
        FLOAT L = this->length();
        x()/=L;
        y()/=L;
        z()/=L;
        return *this;
    }

    FLOAT length() const;
    FLOAT length_sqr() const;

    friend Vector3D operator-(const Vector3D&);
    friend Vector3D operator*(const FLOAT&, const Vector3D&);
};

inline Vector3D operator-(const Vector3D& rhs)
{
    return Vector3D(-rhs.x(), -rhs.y(), -rhs.z());
}

inline Vector3D operator*(const FLOAT& d, const Vector3D& v)
{
    return Vector3D(v.x()*d, v.y()*d, v.z()*d);
}

#endif //RAYTRACER_VECTOR3D_H
