#ifndef RAYTRACER_DOT_H
#define RAYTRACER_DOT_H

#include <fstream>
#include "KDTreeB/KDTree.h"

namespace KDTreeB
{
    void printKDTree(std::ostream &ostream, const KDTreeB::KDTree &tree);
}

#endif //RAYTRACER_DOT_H
