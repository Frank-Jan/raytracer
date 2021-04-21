#ifndef RAYTRACER_MATRIX3D_H
#define RAYTRACER_MATRIX3D_H

#include "Vector3D.h"
#include <stdexcept>

// a 3x3 matrix
class Matrix3D
{
public:
    Matrix3D() = default;
    Matrix3D(const Matrix3D&) = default;
    Matrix3D(Matrix3D&&) = default;

    Matrix3D(FLOAT d);   // d on the diagonal
    Matrix3D(const Vector3D&); // places vector on diagonal
    Matrix3D(const Vector3D&, const Vector3D&, const Vector3D&); // the rows of the matrix if row = false: columns instead

    Matrix3D& operator=(const Matrix3D&) = default;

    Matrix3D operator*(const Matrix3D&) const;
    Vector3D operator*(const Vector3D&) const;

public:
    FLOAT m[3][3]{};              // the matrix

public:
    friend Vector3D;
};

Matrix3D rotationX(FLOAT theta);
Matrix3D rotationY(FLOAT theta);
Matrix3D rotationZ(FLOAT theta);

Matrix3D rotation(FLOAT x, FLOAT y, FLOAT z, FLOAT angle);
Matrix3D rotation(const Vector3D& axis, FLOAT angle);

#endif //RAYTRACER_MATRIX3D_H
