#include "Matrix3D.h"
#include <cmath>


Matrix3D::Matrix3D(FLOAT d)
{
    m[0][0] = d;
    m[1][1] = d;
    m[2][2] = d;
}

Matrix3D::Matrix3D(const Vector3D &v)
{
    m[0][0] = v.x();
    m[1][1] = v.y();
    m[2][2] = v.z();
}

Matrix3D::Matrix3D(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3)
{
    m[0][0] = v1.x();
    m[0][1] = v1.y();
    m[0][2] = v1.z();
    m[1][0] = v2.x();
    m[1][1] = v2.y();
    m[1][2] = v2.z();
    m[2][0] = v3.x();
    m[2][1] = v3.y();
    m[2][2] = v3.z();
}

Matrix3D Matrix3D::operator*(const Matrix3D &rhs) const
{
    Matrix3D lhs{};
    FLOAT e;
    for(char c = 0; c < 3; c++)
    {
        for(char r = 0; r < 3; r++)
        {
            lhs.m[r][c] = m[r][0] * rhs.m[0][c] +
                          m[r][1] * rhs.m[1][c] +
                          m[r][2] * rhs.m[2][c];
        }
    }
    return lhs;
}

Vector3D Matrix3D::operator*(const Vector3D &v) const
{
    Vector3D ret{};
    ret.x() = v.x()*m[0][0] + v.y()*m[0][1] + v.z()*m[0][2];
    ret.y() = v.x()*m[1][0] + v.y()*m[1][1] + v.z()*m[1][2];
    ret.z() = v.x()*m[2][0] + v.y()*m[2][1] + v.z()*m[2][2];
    return ret;
}

Matrix3D rotationX(FLOAT theta)
{
    using std::sin, std::cos;
    Matrix3D rot{};
    rot.m[0][0] = 1.0;
    rot.m[1][1] = cos(theta);
    rot.m[1][2] = -sin(theta);
    rot.m[2][1] = sin(theta);
    rot.m[2][2] = cos(theta);
    return rot;
}

Matrix3D rotationY(FLOAT theta)
{
    using std::sin, std::cos;
    Matrix3D rot{};
    rot.m[0][0] = cos(theta);
    rot.m[0][2] = sin(theta);
    rot.m[1][1] = 1.0;
    rot.m[2][0] = -sin(theta);
    rot.m[2][2] = cos(theta);
    return rot;
}

Matrix3D rotationZ(FLOAT theta)
{
    using std::sin, std::cos;
    Matrix3D rot{};
    rot.m[0][0] = cos(theta);
    rot.m[0][1] = -sin(theta);
    rot.m[1][0] = sin(theta);
    rot.m[1][1] = cos(theta);
    rot.m[2][2] = 1.0;
    return rot;
}

Matrix3D rotation(FLOAT x, FLOAT y, FLOAT z, FLOAT a) {
    using std::sin, std::cos;

    Matrix3D rot;
    // normalize x,y,z
    FLOAT l = sqrt(x*x+y*y+z*z);
    x /= l;
    y /= l;
    z /= l;

    FLOAT one_cos_a = 1 - cos(a);
    FLOAT sin_a = sin(a);

    rot.m[0][0] = 1 + one_cos_a*(x*x - 1);
    rot.m[1][1] = 1 + one_cos_a*(y*y - 1);
    rot.m[2][2] = 1+one_cos_a*(z*z-1);

    rot.m[0][1] =  z*sin_a + x*y*one_cos_a;
    rot.m[0][2] = -y*sin_a + x*z*one_cos_a;
    rot.m[1][0] = -z*sin_a + x*y*one_cos_a;
    rot.m[1][2] =  x*sin_a + y*z*one_cos_a;
    rot.m[2][0] =  y*sin_a + x*z*one_cos_a;
    rot.m[2][1] = -x*sin_a + y*z*one_cos_a;

    return rot;
}
Matrix3D rotation(const Vector3D& ax, FLOAT angle) {
    return rotation(ax.x(), ax.y(), ax.z(), angle);
}