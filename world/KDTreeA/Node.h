#ifndef RAYTRACER_NODE_H
#define RAYTRACER_NODE_H

#include "Vector3D.h"

class ShadeRec;
class Ray;
class BBox;
class World;

namespace KDTreeA
{

    struct Node
    {
        explicit Node(bool _isLeaf) : isLeaf(_isLeaf) {};

        virtual ~Node() = default;

        virtual ShadeRec hit_object(const Ray &, const BBox&, World* world) = 0;

        const bool isLeaf;
    };

    struct Split
    {
        Plane typeSplit;
        FLOAT txyz;
        FLOAT cost;
        int number_left;
        int number_right;
    };
}

#endif //RAYTRACER_NODE_H
