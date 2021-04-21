#include <cmath>
#include "Camera.h"
#include "Matrix3D.h"
#include "Frame.h"
#include "Logger.h"
#include <iostream>

Camera::Camera(FLOAT size, int hres, int vres, FLOAT focal) :
pos(0,0,0),
u(size/vres,0,0),
v(0,size/vres,0),
w(0,0, focal),
vres(vres),
hres(hres)
{
    LOGGER.hres = hres;
    LOGGER.vres = vres;
}

Frame* Camera::getFrame()
{
    return new Frame(hres, vres);
}

void Camera::transform(const Point2D& pp, Ray& ray) const
{
    ray.o = pos + (u*pp.x + v*pp.y);
    ray.d = ((u*pp.x + v*pp.y) - w)._normalize();
}

void Camera::transform(const Point2D& pp, Vector3D& p3) const
{
    p3 = pos + (u*pp.x + v*pp.y);
}

void Camera::translate(const Vector3D& distance)
{
    pos = pos + distance;
}

void Camera::translate(FLOAT x, FLOAT y, FLOAT z)
{
    pos.x() += x;
    pos.y() += y;
    pos.z() += z;
}

// rotate over w axis
void Camera::roll(FLOAT theta)

{
    // convert to radians

    theta *= M_PI / 180;
    Matrix3D rot = rotation(w, M_PI);

    u = rot*u;
    v = rot*v;
    w =  rot*w;
}

// rotate over v axis
void Camera::yaw(FLOAT theta)
{
    // convert to radians

    theta *= M_PI / 180;
    Matrix3D rot = rotation(v, M_PI);

    u = rot*u;
    v = rot*v;
    w =  rot*w;
}

// rotate over u axis
void Camera::pitch(FLOAT theta)
{
    // convert to radians

    theta *= M_PI / 180;
    Matrix3D rot = rotation(u, M_PI);

    u = rot*u;
    v = rot*v;
    w =  rot*w;
}

void Camera::lookat(const Vector3D& p)
{
    if((pos-p).length_sqr() < 1.0) {
//        std::cout << pos.print() << " " << p.print() << std::endl;
//        std::cout << pos.distance(p) << std::endl;
//        std::cout << "Camera distance to small to change" << std::endl;
        return;
    }

    Vector3D dir = (pos-p)._normalize();
    Vector3D nw,nv,nu;  // new base

    nw = dir;
    nu = w^nw;
    nv = nw^nu;

    if(nu.length_sqr() < 1e-2 || nv.length_sqr() < 1e-2)
        return; // already looking to the correct direction

    nw._normalize();
    nu._normalize();
    nv._normalize();


    // resize
    nw *= w.length();
    nu *= u.length();
    nv *= v.length();

    w = nw;
    u = nu;
    v = nv;

    up();
}

void Camera::lookat(FLOAT x, FLOAT y, FLOAT z)
{
    lookat(Vector3D(x,y,z));
}

void Camera::up()
{
    Vector3D n(0,1,0);
//    Vector3D nv = v.normalize();
//    Vector3D nu = v.normalize();
//    if(v*n <= 0.1)
//        return;
    FLOAT lw = w.length();
    FLOAT angle = (n*w)/lw;
    if(angle > .95 || angle < -.95)
        return;

    FLOAT lu = u.length();
    FLOAT lv = v.length();

    u._normalize();
    v._normalize();
    w._normalize();


    if(angle > 0) {
        u = n^w;
        v = w^u;
    }
    else{
        u = w^n;
        v = w^u;
    }

    u._normalize();
    v._normalize();
    w._normalize();

    u *= lu;
    v *= lv;
    w *= lw;
}

