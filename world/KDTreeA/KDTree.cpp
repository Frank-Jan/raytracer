#include <algorithm>

#include "KDTree.h"
#include "Triangle.h"
#include "BBox.h"
#include "Vector3D.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "TBBox.h"
#include "LNode.h"
#include "INode.h"
#include "Logger.h"

namespace KDTreeA
{
    KDTree::~KDTree()
    {
        delete root;
        root = nullptr;
    }

    KDTree::KDTree(std::vector<Triangle> &_triangles)
    {
        delete root;

        LOGGER.worldType = "KD-Tree";
        LOGGER.objects = _triangles.size();
        LOGGER.cost_travel = cost_travel;
        LOGGER.cost_intersect = cost_intersect;
        triangles = _triangles;

        if (_triangles.empty()) {
            root = new LNode({});
            this->nodes.push_back(root);
            LOGGER.average_depth = 1;
            LOGGER.average_triangles = 0.0;
            return;
        }

        std::vector<TBBox> boxes;

        bbox = triangles[0].get_BBox();

        for (int i = 0; i < triangles.size(); i++) {
            boxes.emplace_back(TBBox(triangles[i]));
            bbox.getSmall(Plane::x) = std::min(boxes[i].getSmall(Plane::x), bbox.getSmall(Plane::x));
            bbox.getSmall(Plane::y) = std::min(boxes[i].getSmall(Plane::y), bbox.getSmall(Plane::y));
            bbox.getSmall(Plane::z) = std::min(boxes[i].getSmall(Plane::z), bbox.getSmall(Plane::z));
            bbox.getBig(Plane::x) = std::max(boxes[i].getBig(Plane::x), bbox.getBig(Plane::x));
            bbox.getBig(Plane::y) = std::max(boxes[i].getBig(Plane::y), bbox.getBig(Plane::y));
            bbox.getBig(Plane::z) = std::max(boxes[i].getBig(Plane::z), bbox.getBig(Plane::z));
        }

        root = makeNode(boxes, bbox, *this);

        int i = 0;
        int tr = 0;
        LNode* l;
        for(Node* n : nodes) {
            if (n->isLeaf) {
                i++;
                l = (LNode *) n;
                tr += l->triangles.size();
                LOGGER.size_bytes += sizeof(LNode);
                LOGGER.size_bytes += sizeof(Triangle*) * l->triangles.size();
            }
            else{
                LOGGER.size_bytes += sizeof(INode);
            }
        }
        LOGGER.average_triangles = ((FLOAT)tr)/FLOAT(i);

        LOGGER.size_bytes +=    sizeof(Triangle) * triangles.size();
        LOGGER.size_bytes +=    sizeof(Node*) * nodes.size();
        LOGGER.size_bytes +=    sizeof(KDTree);

        LOGGER.triangles_bytes = sizeof(Triangle) * triangles.size();
    }

    ShadeRec KDTree::hit_object(const Ray &r)
    {
        ShadeRec sr(this);
        if (!root)
            return sr;
        if(!bbox.hit(r))
            return sr;
        return root->hit_object(r, bbox, this);
    }
}