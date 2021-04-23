#include "INode.h"
#include "ShadeRec.h"
#include "Ray.h"
#include <algorithm>
#include "LNode.h"
#include "KDTree.h"
#include <iostream>
#include <set>
#include "Logger.h"
#include "constants.h"
#include "split.h"


namespace KDTreeA
{
    struct Split;
    struct SplitVector;

    const unsigned max_triangles = 4;
    const FLOAT cost_no_split = 2;

    struct SplitVector
    {
        std::vector<TBBox> left;
        std::vector<TBBox> right;
    };

    SplitVector splitNode(const std::vector<TBBox> &, Split split);
    Split scoreSplit(const std::vector<TBBox> &boxes, Plane p, const BBox &bbox_node);
    Node *makeNode(const std::vector<TBBox>& boxes, const BBox &bbox, KDTree& parent);

    ShadeRec INode::hit_object(const Ray &r, const BBox& bbox, World* world)
    {
        LOGGER.check_nodes++;
        // determine far and close node
        Node *farChild;
        Node *closeChild;

        bool closeIsLeft = true;
        closeChild = lChild;
        farChild = rChild;
        BBox rchild_bbox = bbox;
        BBox lchild_bbox = bbox;
        rchild_bbox.getSmall(tsplit) = txyz;
        lchild_bbox.getBig(tsplit) = txyz;

        if (r.o[tsplit] > txyz) {
            closeChild = rChild;
            farChild = lChild;
            closeIsLeft = false;
        }

        BBox* bbox_close;
        BBox* bbox_far;
        if(closeIsLeft)
        {
            bbox_close = &lchild_bbox;
            bbox_far = &rchild_bbox;
        }
        else {
            bbox_close = &rchild_bbox;
            bbox_far = &lchild_bbox;
        }

        ShadeRec sr(world);
        if(bbox_close->hit(r))
            sr = closeChild->hit_object(r, *bbox_close, world);

        // check if we need to hit the far child
        // calculate intersection with split
        FLOAT t = (txyz - r.o[tsplit]) / r.d[tsplit];

        if (t > 0 && ((!sr.hit) || (sr.hit && t < sr.tmin)) && bbox_far->hit(r)) {
            LOGGER.triangles_doubled += shared;
            ShadeRec temp_sr = farChild->hit_object(r, *bbox_far, world);
            if (sr.tmin > temp_sr.tmin)
                return temp_sr;
            return sr;
        }
        if(closeIsLeft)
            LOGGER.triangles_skipped += unique_right;
        else
            LOGGER.triangles_skipped += unique_left;
        return sr;
    }

    INode::INode(const std::vector<TBBox>& boxes, const BBox &bbox_node, const Split& split, KDTree& parent) :
    Node(false)
    {
        LOGGER.internal_nodes++;
        txyz = split.txyz;
        tsplit = split.typeSplit;

        SplitVector spv = splitNode(boxes, split);

        BBox bbox_node_lchild = bbox_node;
        bbox_node_lchild.getBig(split.typeSplit) = split.txyz;

        BBox bbox_node_rchild = bbox_node;
        bbox_node_rchild.getSmall(split.typeSplit) = split.txyz;

        unique_left  = boxes.size() - spv.right.size();
        unique_right = boxes.size() - spv.left.size();
        shared       = spv.right.size() + spv.left.size() - boxes.size();

        lChild = makeNode(spv.left, bbox_node_lchild, parent);
        rChild = makeNode(spv.right, bbox_node_rchild, parent);
    }

    FLOAT surface_area(const BBox &bbox)
    {
        FLOAT width = bbox.getBig(Plane::x) - bbox.getSmall(Plane::x);
        FLOAT height = bbox.getBig(Plane::y) - bbox.getSmall(Plane::y);
        FLOAT depth = bbox.getBig(Plane::z) - bbox.getSmall(Plane::z);
        return 2 * (width * height + width * depth + depth * height);
    }

    inline FLOAT relative_cost_split(int countL, int countR, const BBox& bbox, Plane split_plane, FLOAT split)
    {
        FLOAT SA = surface_area(bbox);

        Plane p[] = {Plane::x, Plane::y, Plane::z, Plane::x, Plane::y};
        FLOAT du_right = bbox.getBig(split_plane) - split;
        FLOAT dv = bbox.getBig(p[split_plane+1]) - bbox.getSmall(p[split_plane+1]);
        FLOAT dw = bbox.getBig(p[split_plane+2]) - bbox.getSmall(p[split_plane+2]);

        FLOAT surface_area_right = 2*(du_right*dv + dv*dw + du_right*dw);

        FLOAT du_left = split - bbox.getSmall(split_plane);

        FLOAT surface_area_left = 2*(du_left*dv + dv*dw + du_left*dw);

        FLOAT chance_hit_left = surface_area_left;
        FLOAT chance_hit_right = surface_area_right;

        FLOAT cost = cost_travel + cost_intersect * (chance_hit_left * countL + chance_hit_right * countR) / SA;
        return cost;
    }

    inline FLOAT relative_no_cost_split(int count)
    {
        FLOAT cost = count*cost_intersect;
//        if(count > max_triangles)
//            return 2*cost;
        return cost;
    }

    Node * makeNode(const std::vector<TBBox>& boxes, const BBox &bbox, KDTree& parent)
    {
        if(boxes.empty()) {
            LNode* n = new LNode(boxes);
            parent.nodes.push_back(n);
            return n;
//            parent.leaves.emplace_back(boxes);
//            return parent.leaves.size() - 1;
        }

        // test a number of splits
        Split xSplit = scoreSplit(boxes, Plane::x, bbox);
        Split ySplit = scoreSplit(boxes, Plane::y, bbox);
        Split zSplit = scoreSplit(boxes, Plane::z, bbox);

        Split bestSplit = xSplit;
        if (bestSplit.cost > ySplit.cost)
            bestSplit = ySplit;
        if (bestSplit.cost > zSplit.cost)
            bestSplit = zSplit;

        FLOAT splitCost = bestSplit.cost;
        FLOAT nosplitCost = relative_no_cost_split(boxes.size());

        // no split cost

        if (splitCost < nosplitCost) {
            INode* n = new INode(boxes, bbox, bestSplit, parent);
            parent.nodes.push_back(n);
            return n;
        }

        LNode* n = new LNode(boxes);
        parent.nodes.push_back(n);
        return n;
    }

    inline void countSplit(int& left, int& right, const std::vector<TBBox> &boxes, const Plane& p, const FLOAT& split)
    {
        left = 0;
        right = 0;

        for(const TBBox& box : boxes)
        {
            if(box.getSmall(p) > split)
                right++;
            else if(box.getBig(p) < split)
                left++;
            else {
                right++;
                left++;
            }
        }
    }

    Split scoreSplit(const std::vector<TBBox> &boxes, Plane p, const BBox &bbox_node)
    {
        std::vector<FLOAT> points;

        points.reserve(boxes.size()*2);

        for(const TBBox& box : boxes)
        {
            points.push_back(box.getSmall(p));
            points.push_back(box.getBig(p));
        }
        points.erase(std::unique(points.begin(), points.end()), points.end());

        int countLeft = 0;
        int countRight = 0;

        FLOAT s = bbox_node.getSmall(p);

        countSplit(countLeft, countRight, boxes, p, s);
        FLOAT costS = relative_cost_split(countLeft, countRight, bbox_node, p, s);
        FLOAT new_cost;
        FLOAT prevX = s;
        for(FLOAT x : points)
        {
            if(prevX >= x)
                continue;
            if(x > bbox_node.getBig(p))
                break;
            prevX = x;

            for(FLOAT i : {-kEpsilon, kEpsilon}) {
                countSplit(countLeft, countRight, boxes, p, x+i);
                new_cost = relative_cost_split(countLeft, countRight, bbox_node, p, x+i);
                if (new_cost < costS) {
                    costS = new_cost;
                    s = x+i;
                }
            }
        }

        countSplit(countLeft, countRight, boxes, p, s);
        Split split{};
        split.txyz = s;
        split.cost = costS;
        split.typeSplit = p;
        split.number_left = countLeft;
        split.number_right = countRight;

        return split;
    }

    SplitVector splitNode(const std::vector<TBBox> &boxes, Split split)
    {
        std::vector<TBBox> left;
        std::vector<TBBox> right;
        left.reserve(split.number_left);
        right.reserve(split.number_right);
        const Plane p = split.typeSplit;
        const FLOAT txyz = split.txyz;

        for (int i = 0; i < boxes.size(); ++i) {
            if (boxes[i].getSmall(p) <= txyz)
                left.push_back(boxes[i]);
            if (boxes[i].getBig(p) > txyz)
                right.push_back(boxes[i]);
        }

        SplitVector sv;
        sv.left = left;
        sv.right = right;

        return sv;
    }
}