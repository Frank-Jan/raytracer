#ifndef RAYTRACER_INODE_H
#define RAYTRACER_INODE_H

#include "Vector3D.h"
#include "Node.h"
#include "TBBox.h"
#include <vector>

class World;

namespace KDTreeA
{
    class KDTree;

    // internal node
    class INode : public Node
    {
    public:
        INode(const std::vector<TBBox>& tbbox, const BBox &, const Split& split, KDTree& parent);

        ~INode()
        {
            delete lChild;
            delete rChild;
        };

        ShadeRec hit_object(const Ray &, const BBox& bbox, World* parent);

    public:
        Plane tsplit;           // on which axis
        FLOAT txyz;            // where on the axis
        unsigned unique_left;
        unsigned unique_right;
        unsigned shared;
//        Node *lChild{nullptr};  // left child
//        Node *rChild{nullptr};  // right child
        Node *lChild{nullptr};  // left child
        Node *rChild{nullptr};  // right child
    };

    Node * makeNode(const std::vector<TBBox>& boxes, const BBox &bbox, KDTree& parent);
//    size_t makeNode(const std::vector<TBBox>& boxes, const BBox &bbox, KDTree& parent);
}


#endif //RAYTRACER_INODE_H
