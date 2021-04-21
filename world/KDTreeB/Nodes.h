#ifndef RAYTRACER_NODES_H
#define RAYTRACER_NODES_H

#include <iostream>
#include "Vector3D.h"

namespace KDTreeB
{

    struct LNode
    {
        unsigned int flags = 0;  // is children too
        size_t first = 0;  // first triangle
        unsigned int children() const { return flags; }
    };

    struct INode
    {
        unsigned int flags = 0x80000000;   // [flag | typeSplit | first_child]
        float split = 0;

        Plane type() const {
            Plane p[] = {Plane::x, Plane::y, Plane::z};
            unsigned idx = ((flags & 0x60000000)>>29);
            return p[idx];
        }

        unsigned int first() const { return flags & 0x00ffffff; }
    };

    union UNode
    {
        INode node;
        LNode leaf;

        explicit
        UNode(Plane tsplit, unsigned first_child, float split) :
                node({(unsigned)0x80000000 + ((unsigned)tsplit << 29) + (unsigned)first_child, split})
        {
            if(first_child >= 0x20000000)
                std::cerr << "Error: Internal node created with too big offset" << std::endl;
        };

        UNode(size_t first, size_t number_of_children) :
                leaf({(unsigned) number_of_children, first})
        {
            if (number_of_children >= 0x80000000)
                std::cerr << "Error: Leaf node created with too many children" << std::endl;
        };

        bool isNode() const
        {
            return 0x80000000 & node.flags;
        }
    };
}

#endif //RAYTRACER_NODES_H
