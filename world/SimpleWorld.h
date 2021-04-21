#ifndef RAYTRACER_SIMPLEWORLD_H
#define RAYTRACER_SIMPLEWORLD_H

#include <vector>
#include "Color.h"
#include "Vector3D.h"
#include "World.h"

class Camera;
class Ray;
class ShadeRec;
class Triangle;
class Light;

class SimpleWorld : public World
{
public:
    explicit SimpleWorld(std::vector<Triangle> &triangles);

    SimpleWorld(const SimpleWorld&) = delete;

    SimpleWorld(SimpleWorld&&) = delete;

    ~SimpleWorld() = default;

    SimpleWorld& operator=(const SimpleWorld&) = delete;

    ShadeRec hit_object(const Ray& ray);

//    // Visibility and geometry term
//    inline double V(const Vector3D& p0, const Vector3D& p1);
//
//    void set_ambient(Light* _ambient);
//
//    void add_object(Triangle*);

private:
    std::vector<Triangle> objects;
};



#endif //RAYTRACER_SIMPLEWORLD_H
