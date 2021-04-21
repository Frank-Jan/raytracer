#ifndef RAYTRACER_LOGGER_H
#define RAYTRACER_LOGGER_H

#include <ostream>
#include <string>
#include "constants.h"

struct Logger
{
    unsigned long   intersections       = 0;
    unsigned        vres                = 0;
    unsigned        hres                = 0;
    unsigned        objects             = 0;
    double          average_triangles   = 0;
    unsigned        average_depth       = 0;
    std::string     worldType           = "not set";
    std::string     filename            = "not set";
    unsigned        nleafs              = 0;
    unsigned        internal_nodes      = 0;
    unsigned        triangles_skipped   = 0;
    unsigned        triangles_doubled   = 0;
    long            preprocess_time     = 0;
    long            render_time         = 0;
    FLOAT           cost_travel         = 0;
    FLOAT           cost_intersect      = 0;
    long            check_leafs         = 0;
    long            check_nodes         = 0;
    long            size_bytes          = 0;
    long            triangles_bytes     = 0;
    void operator()(std::ostream& ostream);
};

inline Logger LOGGER;


#endif //RAYTRACER_LOGGER_H
