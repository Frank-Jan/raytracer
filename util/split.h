#ifndef RAYTRACER_SPLIT_H
#define RAYTRACER_SPLIT_H

#include <vector>
#include "Vector3D.h"
#include "TBBox.h"
#include "constants.h"


FLOAT bestSplit(const std::vector<TBBox>& boxes, Plane& tsplit, FLOAT& split, const BBox& bbox);

#endif //RAYTRACER_SPLIT_H
