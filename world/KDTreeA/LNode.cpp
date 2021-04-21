#include "LNode.h"
#include "TBBox.h"
#include "ShadeRec.h"
#include "Logger.h"


namespace KDTreeA
{
    LNode::LNode(const std::vector<TBBox> &_tbboxes) :
    Node(true)
    {
        LOGGER.nleafs++;
        for (const TBBox &b : _tbboxes)
            triangles.emplace_back(b.t);
    }

    ShadeRec LNode::hit_object(const Ray &r, const BBox& bbox, World* world)
    {
        LOGGER.check_leafs++;
        ShadeRec sr(world);
        FLOAT tmin = hugeValue;
        Triangle *object_hit = nullptr;
        bool hit = false;
        for (Triangle* t : triangles) {
            if (t->hit_object(r, tmin, sr)) {
                object_hit = sr.triangle;
                hit = true;
                tmin = sr.tmin;
            }
        }
        sr.hit = hit;
        sr.tmin = tmin;
        sr.triangle = object_hit;
        return sr;
    }
}
