#include "KDTree.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "TBBox.h"
#include <algorithm>
#include "Logger.h"
#include "split.h"
#include <bitset>

namespace KDTreeB
{
    KDTree::KDTree(std::vector<Triangle> &_triangles)
    {
        std::vector<TBBox> boxes = setBBox(_triangles);
        build(boxes);

        LOGGER.size_bytes +=    sizeof(Triangle) * triangles.size();
        LOGGER.size_bytes +=    sizeof(UNode) * nodes.size();
        LOGGER.size_bytes +=    sizeof(KDTree);

        LOGGER.triangles_bytes = sizeof(Triangle) * triangles.size();
    }

    ShadeRec KDTree::hit_object(const Ray &ray)
    {
        struct StackItem
        {
            UNode const* node;
            FLOAT t_near;
            FLOAT t_far;
        };

        FLOAT t_near = kEpsilon;
        FLOAT t_far  = hugeValue;

        ShadeRec sr(this);

        if(not bbox.clipRay(ray, t_near, t_far))
            return sr;

        ShadeRec temp_sr(this);
        std::vector<StackItem> stack;
        UNode const* node = root;

        while(true)
        {
            while(node->isNode())
            {
                LOGGER.check_nodes++;
                FLOAT d = (node->node.split - ray.o[node->node.type()]) / ray.d[node->node.type()];

                if (d < 0 | d > t_far) {
                    // t_near <= t_far <= d -> cull back side
                    node = frontChild(node, ray);
                }
                else if (d < t_near) {
                    // d <= t_near <= t_far -> cull front side
                    node = backChild(node, ray);
                }
                else {
                    // traverse both sides in turn
                    stack.push_back({backChild(node, ray), d, t_far});
                    node = frontChild(node, ray);
                    t_far = d;
                }
            }
            if(hit_object(ray, sr, node->leaf.first, node->leaf.children()))
                if ((t_far >= sr.tmin))
                    return sr;
            if(stack.empty())
                return sr;

            node    = stack.back().node;
            t_near  = stack.back().t_near;
            t_far   = stack.back().t_far;
            stack.pop_back();
        }
    }

    inline bool KDTree::hit_object(const Ray &ray, ShadeRec& sr, unsigned tidx, unsigned num)
    {
        LOGGER.check_leafs++;
        bool hit = false;
        for(unsigned i = tidx; i < tidx+num; i++)
            if(triangles.at(i).hit_object(ray, sr))
                hit = true;
        return hit;
    }

    inline UNode const*const KDTree::frontChild(UNode const*const uNode, const Ray& ray) const
    {
        unsigned offset = uNode->node.first() + (uNode->node.split < ray.o[uNode->node.type()]);
        return uNode + offset;
    }

    inline UNode const* const KDTree::backChild(UNode const *const uNode, const Ray& ray) const
    {
        unsigned offset = uNode->node.first() + !(uNode->node.split < ray.o[uNode->node.type()]);
        return uNode + offset;
    }

    std::vector<TBBox> KDTree::setBBox(std::vector<Triangle> &_triangles) {
        std::vector<TBBox> boxes;
        boxes.reserve(_triangles.size());
        bbox = BBox(0,0,0,0,0,0);

        for (int i = 0; i < _triangles.size(); i++) {
            boxes.emplace_back(TBBox(_triangles.at(i)));
            bbox.getSmall(Plane::x) = std::min(boxes[i].getSmall(Plane::x), bbox.getSmall(Plane::x));
            bbox.getSmall(Plane::y) = std::min(boxes[i].getSmall(Plane::y), bbox.getSmall(Plane::y));
            bbox.getSmall(Plane::z) = std::min(boxes[i].getSmall(Plane::z), bbox.getSmall(Plane::z));
            bbox.getBig(Plane::x) = std::max(boxes[i].getBig(Plane::x), bbox.getBig(Plane::x));
            bbox.getBig(Plane::y) = std::max(boxes[i].getBig(Plane::y), bbox.getBig(Plane::y));
            bbox.getBig(Plane::z) = std::max(boxes[i].getBig(Plane::z), bbox.getBig(Plane::z));
        }

        return boxes;
    }

//    void countSplit(int& left, int& right, const std::vector<TBBox> &boxes, const Plane& p, const FLOAT& split)
//    {
//        left = 0;
//        right = 0;
//
//        for(const TBBox& box : boxes)
//        {
//            if(box.getSmall(p) > split)
//                right++;
//            else if(box.getBig(p) < split)
//                left++;
//            else {
//                right++;
//                left++;
//            }
//        }
//    }
//
//    inline FLOAT surface_area(const BBox &bbox)
//    {
//        FLOAT width = bbox.getBig(Plane::x) - bbox.getSmall(Plane::x);
//        FLOAT height = bbox.getBig(Plane::y) - bbox.getSmall(Plane::y);
//        FLOAT depth = bbox.getBig(Plane::z) - bbox.getSmall(Plane::z);
//        return 2 * (width * height + width * depth + depth * height);
//    }
//
//    inline FLOAT costSplit(int countL, int countR, const BBox& bbox, Plane split_plane, FLOAT split)
//    {
//        FLOAT SA = surface_area(bbox);
//
//        Plane p[] = {Plane::x, Plane::y, Plane::z, Plane::x, Plane::y};
//        FLOAT du_right = bbox.getBig(split_plane) - split;
//        FLOAT dv = bbox.getBig(p[split_plane+1]) - bbox.getSmall(p[split_plane+1]);
//        FLOAT dw = bbox.getBig(p[split_plane+2]) - bbox.getSmall(p[split_plane+2]);
//
//        FLOAT surface_area_right = 2*(du_right*dv + dv*dw + du_right*dw);
//
//        FLOAT du_left = split - bbox.getSmall(split_plane);
//
//        FLOAT surface_area_left = 2*(du_left*dv + dv*dw + du_left*dw);
//
//        FLOAT chance_hit_left = surface_area_left;
//        FLOAT chance_hit_right = surface_area_right;
//
//        FLOAT cost = cost_travel + cost_intersect * (chance_hit_left * countL + chance_hit_right * countR) / SA;
//        return cost;
//    }
//
    FLOAT costNoSplit(unsigned count)
    {
        FLOAT cost = FLOAT(count) * cost_intersect;
        return cost;
    }
//
//    FLOAT bestSplit(const std::vector<TBBox>& boxes, Plane& tsplit, FLOAT& split, const BBox& bbox)
//    {
//        FLOAT cost = hugeValue;
//        std::vector<FLOAT> points;
//        points.reserve(boxes.size()*2);
//        for(Plane p : {Plane::x, Plane::y, Plane::z})
//        {
//            points.resize(0);
//            for(const TBBox& box : boxes)
//            {
//                points.push_back(box.getSmall(p));
//                points.push_back(box.getBig(p));
//            }
//
//            points.erase(std::unique(points.begin(), points.end()), points.end());
//
//            int countLeft = 0;
//            int countRight = 0;
//
//            FLOAT s = bbox.getSmall(p);
//
//            countSplit(countLeft, countRight, boxes, p, s);
//            FLOAT costS = costSplit(countLeft, countRight, bbox, p, s);
//            FLOAT new_cost;
//            FLOAT prevX = s;
//            for(FLOAT x : points)
//            {
//                if(prevX >= x)
//                    continue;
//                if(x > bbox.getBig(p))
//                    break;
//                prevX = x;
//
//                for(FLOAT i : {-kEpsilon, kEpsilon}) {
//                    countSplit(countLeft, countRight, boxes, p, x+i);
//                    new_cost = costSplit(countLeft, countRight, bbox, p, x+i);
//                    if (new_cost < costS) {
//                        costS = new_cost;
//                        s = x+i;
//                    }
//                }
//            }
//            countSplit(countLeft, countRight, boxes, p, s);
//            if(costS < cost) {
//                cost = costS;
//                split = s;
//                tsplit = p;
//            }
//        }
//
//        return cost;
//    }

    unsigned KDTree::insertTriangles(std::vector<TBBox>& boxes)
    {
        unsigned first = triangles.size();
        for(TBBox& b : boxes)
            triangles.insert(triangles.end(), *b.t);
        return first;
    }

    std::vector<TBBox> splitBoxes(const Plane& tsplit, const FLOAT& split, std::vector<TBBox>& boxes)
    {
        std::vector<TBBox> right_boxes;
        right_boxes.reserve(boxes.size()/2);

        for(auto & boxe : boxes) {
            if(boxe.getBig(tsplit) > split)
                right_boxes.push_back(boxe);
        }

        boxes.erase(std::remove_if(boxes.begin(), boxes.end(), [tsplit, split](const BBox& a)->bool { return (a.getSmall(tsplit) > split); }), boxes.end());
        return right_boxes;
    }

    void KDTree::build(const std::vector<TBBox> &boxes) {
        LOGGER.objects        = boxes.size();
        LOGGER.worldType      = "KDTreeB";
        LOGGER.cost_intersect = cost_intersect;
        LOGGER.cost_travel    = cost_travel;
        root = nullptr;

        nodes.emplace_back(0,0);

        struct StackItem{
            StackItem(unsigned _idx, std::vector<TBBox> _items, const BBox& _bb) :
                    idx(_idx), items(std::move(_items)), bb(_bb) { };
            unsigned idx;   // position of node
            std::vector<TBBox> items;
            BBox bb;
        };

        std::vector<StackItem> todo;
        std::vector<StackItem> leaves;

        std::vector<TBBox> cboxes;
        cboxes.insert(cboxes.begin(), boxes.begin(), boxes.end());

        unsigned cNode = 0;
        BBox bba = bbox;
        BBox bbb = bbox;
        FLOAT cost_split;
        FLOAT cost_no_split;
        Plane tsplit;
        FLOAT split;

        do {
            cost_split = bestSplit(cboxes, tsplit, split, bba);
            cost_no_split = costNoSplit(cboxes.size());
            char c[] = {'x', 'y', 'z'};
//            std::cout << "tSplit: " << c[tsplit] << " split: " << split << std::endl;
//            std::cout << cost_no_split << " " << cost_split << std::endl << std::endl;
            if(cost_no_split > cost_split) {

                nodes.at(cNode) = UNode(tsplit, nodes.size()-cNode, split);

                bbb = bba;
                bba.getBig(tsplit)      = split;
                bbb.getSmall(tsplit)    = split;

                cNode = nodes.size();
                std::vector<TBBox> right = splitBoxes(tsplit, split, cboxes);

                todo.emplace_back(nodes.size()+1, right, bbb);
                nodes.emplace_back(0,0);
                nodes.emplace_back(0,0);

                continue;
            }
            // create leaf
            leaves.emplace_back(cNode, cboxes, bba);
            nodes.at(cNode) = UNode(0,0);  // push_back empty node to insert later

            if(not todo.empty())
            {
                cNode   = todo.back().idx;
                cboxes  = std::move(todo.back().items);
                bba     = todo.back().bb;
                todo.pop_back();
                continue;
            }
            break;
        }while(true);

        // fix the leaves
        unsigned c = 0;
        unsigned first;
        LOGGER.nleafs = leaves.size();
        for(StackItem& s : leaves) {
            c += s.items.size();
            first = insertTriangles(s.items);
            nodes.at(s.idx) = UNode(first, s.items.size());
        }
        LOGGER.average_triangles = FLOAT(c) / FLOAT(LOGGER.nleafs);
        LOGGER.internal_nodes = nodes.size() - LOGGER.nleafs;
        root = nodes.begin().base();
    }


}
