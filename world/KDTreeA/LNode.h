#ifndef RAYTRACER_LNODE_H
#define RAYTRACER_LNODE_H

#include <vector>
#include "Node.h"

class TBBox;
class Triangle;
class BBox;
class World;

namespace KDTreeA
{
    // leaf node
    class LNode : public Node
    {
    public:
        explicit LNode(const std::vector<TBBox> &_tbboxes);

        ~LNode() = default;

        ShadeRec hit_object(const Ray &, const BBox& bbox, World* world);

    public:
        std::vector<Triangle*> triangles;
    };
}


#endif //RAYTRACER_LNODE_H
