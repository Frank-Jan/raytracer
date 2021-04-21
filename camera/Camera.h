#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Point2D.h"
#include "Vector3D.h"
#include "Ray.h"
#include "constants.h"

class Frame;

/*

                   /|
                  / |
 focal point --> *  * <--plane
                  \ |
                   \|

 */



class Camera
{
private:
    // pos + w = focal point
    Vector3D pos, focal;
    Vector3D u,v,w;
public:
    explicit Camera(FLOAT size, int hres, int vres, FLOAT focal_point);
//    void rotate(const Matrix3D& rot);

    Frame* getFrame();

    void transform(const Point2D& p2d, Ray& ray) const;
    void transform(const Point2D& p2d, Vector3D& p3d) const;   // transforms the 2d point of the frame to a 3d point on the viewplane

    void translate(const Vector3D&);
    void translate(FLOAT x, FLOAT y, FLOAT z);

    // rotate over w axis
    void roll(FLOAT theta);

    // rotate over v axis
    void yaw(FLOAT theta);

    // rotate over u axis
    void pitch(FLOAT theta);

    // aim the camera towards point p
    void lookat(const Vector3D& p);
    void lookat(FLOAT x, FLOAT y, FLOAT z);

    void up();

public:
    int vres;
    int hres;
    FLOAT exposure = 1.0;

};


#endif //RAYTRACER_CAMERA_H
