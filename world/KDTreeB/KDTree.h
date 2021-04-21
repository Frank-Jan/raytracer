#ifndef RAYTRACER_KDTREEB_H
#define RAYTRACER_KDTREEB_H

#include <vector>
#include <array>
#include "World.h"
#include "BBox.h"
#include "Nodes.h"
#include <Triangle.h>
#include <iostream>
#include <TBBox.h>


class Ray;
class Vector3D;
struct ShadeRec;

namespace KDTreeB
{
    class KDTree : public World
    {
    public:
        explicit
        KDTree(std::vector<Triangle> &triangles);

        KDTree(const KDTree &) = delete;

        KDTree(KDTree &&) = delete;

        ~KDTree() = default;

        KDTree &operator=(const KDTree &) = delete;

        ShadeRec hit_object(const Ray &);

    public:
        std::vector<Triangle> triangles;
        std::vector<UNode> nodes;
        UNode *root{nullptr};
        BBox bbox;

    private:
        std::vector<TBBox> setBBox(std::vector<Triangle>&);
        void build(const std::vector<TBBox>&);
        void buildB(const std::vector<TBBox>&);

        unsigned insertTriangles(std::vector<TBBox>&);
        unsigned insertTriangles(const std::vector<TBBox>&, const std::vector<bool>& active);

        inline bool hit_object(const Ray&, ShadeRec&, unsigned tidx, unsigned num);
        inline UNode const* const frontChild(UNode const *, const Ray& ray) const;
        inline UNode const* const backChild(UNode const *, const Ray& ray) const;
    };
}


#endif //RAYTRACER_KDTREEB_H
