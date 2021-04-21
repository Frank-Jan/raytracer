#ifndef RAYTRACER_CONSTANTS_H
#define RAYTRACER_CONSTANTS_H

#include <limits>

using FLOAT = float;

inline const bool CONSOLE_OUTPUT = true;

inline const FLOAT kEpsilon = 1e-6;

inline const FLOAT hugeValue = std::numeric_limits<FLOAT>::max();

inline const bool ASSERTIONS = true;

//inline const FLOAT cost_travel = 32;

inline const FLOAT cost_travel = 1;

inline const FLOAT cost_intersect = 2;

#endif //RAYTRACER_CONSTANTS_H
