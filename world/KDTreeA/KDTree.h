#ifndef RAYTRACER_KDTREE_H
#define RAYTRACER_KDTREE_H

#include <vector>
#include <array>
#include "World.h"
#include "BBox.h"
#include <Triangle.h>
#include "Node.h"
#include "LNode.h"
#include "INode.h"

class Ray;
class Vector3D;
struct ShadeRec;

namespace KDTreeA
{
    void printKDTree(std::ostream &ostream, const KDTree &tree);

    class Node;
//    class LNode;
//    class INode;
//
//    union N {
//        LNode l;
//        INode i;
//    };

    class KDTree : public World
    {
    public:
        KDTree(std::vector<Triangle> &triangles);

        KDTree(const KDTree &) = delete;

        KDTree(KDTree &&) = delete;

        ~KDTree();

        KDTree &operator=(const KDTree &) = delete;

        ShadeRec hit_object(const Ray &);

    public:
        std::vector<Triangle> triangles;
        std::vector<Node*> nodes;
//        std::vector<INode> inodes;
//        std::vector<LNode> leaves;
//        std::vector<N> node;
        Node *root{nullptr};
        BBox bbox;
    };
}


#endif //RAYTRACER_KDTREE_H
