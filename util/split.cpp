#include "split.h"


FLOAT bestSplitA(const std::vector<TBBox>& boxes, Plane& tsplit, FLOAT& split, const BBox& bbox);
FLOAT bestSplitB(const std::vector<TBBox>& boxes, Plane& tsplit, FLOAT& split, const BBox& bbox);
FLOAT bestSplit(const std::vector<TBBox>& boxes, Plane& tsplit, FLOAT& split, const BBox& bbox)
{

    if(boxes.size() > 20)
        return bestSplitB(boxes, tsplit, split, bbox);
    return bestSplitA(boxes, tsplit, split, bbox);
}


// VERSION A

void countSplit(int& left, int& right, const std::vector<TBBox> &boxes, const Plane& p, const FLOAT& split)
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

FLOAT surface_area(const BBox &bbox)
{
    FLOAT width = bbox.getBig(Plane::x) - bbox.getSmall(Plane::x);
    FLOAT height = bbox.getBig(Plane::y) - bbox.getSmall(Plane::y);
    FLOAT depth = bbox.getBig(Plane::z) - bbox.getSmall(Plane::z);
    return 2 * (width * height + width * depth + depth * height);
}

FLOAT costSplit(unsigned countL, unsigned countR, const BBox& bbox, Plane split_plane, FLOAT split)
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

FLOAT bestSplitA(const std::vector<TBBox>& boxes, Plane& tsplit, FLOAT& split, const BBox& bbox)
{
    FLOAT cost = hugeValue;
    std::vector<FLOAT> points;
    points.reserve(boxes.size()*2);
    for(Plane p : {Plane::x, Plane::y, Plane::z})
    {
        points.resize(0);
        for(const TBBox& box : boxes)
        {
            points.push_back(box.getSmall(p));
            points.push_back(box.getBig(p));
        }

        points.erase(std::unique(points.begin(), points.end()), points.end());

        int countLeft = 0;
        int countRight = 0;

        FLOAT s = bbox.getSmall(p);

        countSplit(countLeft, countRight, boxes, p, s);
        FLOAT costS = costSplit(countLeft, countRight, bbox, p, s);
        FLOAT new_cost;
        FLOAT prevX = s;
        for(FLOAT x : points)
        {
            if(prevX >= x)
                continue;
            if(x > bbox.getBig(p))
                break;
            prevX = x;

            for(FLOAT i : {-kEpsilon, kEpsilon}) {
                countSplit(countLeft, countRight, boxes, p, x+i);
                new_cost = costSplit(countLeft, countRight, bbox, p, x+i);
                if (new_cost < costS) {
                    costS = new_cost;
                    s = x+i;
                }
            }
        }
        countSplit(countLeft, countRight, boxes, p, s);
        if(costS < cost) {
            cost = costS;
            split = s;
            tsplit = p;
        }
    }

    return cost;
}



// VERSION B

static const char nBuckets = 13;    // buckets to test

struct Ret {
    FLOAT cost;
    FLOAT split;
};

Ret calculateCost(const std::vector<TBBox>& boxes, const BBox& bbox, const Plane& p)
{
    Ret ret = {hugeValue, 0};
    FLOAT step = (bbox.getBig(p) - bbox.getSmall(p)) / (nBuckets + 2);
    FLOAT beg = bbox.getSmall(p);

    FLOAT splits[nBuckets];
    splits[0] = beg + step;

    for(int i = 1; i < nBuckets; ++i)
        splits[i] = splits[i-1] + step;

    unsigned lbuckets[nBuckets] = {0};
    unsigned rbuckets[nBuckets] = {0};
    for(auto& box : boxes) {
        int i = 0;
        FLOAT s = box.getSmall(p);
        FLOAT b = box.getBig(p);
        FLOAT sp = splits[i];
        while(i < nBuckets) {
            lbuckets[i] += (s < sp);
            rbuckets[i] += (b > sp);
            i++;
        }
    }

    ret = {costSplit(lbuckets[0],  rbuckets[0], bbox, p,splits[0]), splits[0]};
    for(int i = 1; i < nBuckets; i++) {
        FLOAT cost = costSplit(lbuckets[i], rbuckets[i], bbox, p,splits[i]);
        if(cost < ret.cost) {
            ret.cost  = cost;
            ret.split = splits[i];
        }
    }
    return ret;
}

FLOAT bestSplitB(const std::vector<TBBox>& boxes, Plane& tsplit, FLOAT& split, const BBox& bbox)
{
    FLOAT cost = hugeValue;

    for(Plane p : {Plane::x, Plane::y, Plane::z})
    {
        Ret r = calculateCost(boxes, bbox, p);
        if(r.cost < cost) {
            cost    = r.cost;
            split   = r.split;
            tsplit  = p;
        }
    }

    return cost;
}
