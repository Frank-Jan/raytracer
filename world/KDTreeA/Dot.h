#ifndef RAYTRACER_DOT_H
#define RAYTRACER_DOT_H

#include <fstream>
#include "world/KDTreeA/KDTree.h"

namespace KDTreeA
{
    void printKDTree(std::ostream &ostream, const KDTree &tree);
}
#endif //RAYTRACER_DOT_H
