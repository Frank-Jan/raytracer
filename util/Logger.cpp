#include "Logger.h"

void Logger::operator()(std::ostream& ostream)
{
    ostream << "Log info:\n";
    ostream << "\tfilename          | " << filename             << "\n";
    ostream << "\tResolution        | " << hres << 'x' << vres  << "\n";
    ostream << "\tPixels            | " << hres*vres            << "\n";
    ostream << "\tWorld type        | " << worldType            << "\n";
    ostream << "\tObjects           | " << objects              << "\n";
    ostream << "\tTotal time        | " << render_time+preprocess_time << "ms\n";
    ostream << "\tPreprocess time   | " << preprocess_time      << "ms\n";
    ostream << "\tRender time       | " << render_time          << "ms\n";
    ostream << "\tIntersections     | " << intersections        << "\n";
    ostream << "\tCheck leafs       | " << check_leafs          << "\n";
    ostream << "\tCheck nodes       | " << check_nodes          << "\n";
    ostream << "\tAverage triangles | " << average_triangles    << "\n";
    ostream << "\tLeafs             | " << nleafs               << "\n";
    ostream << "\tinternal nodes    | " << internal_nodes       << "\n";
    ostream << "\tSkipped objects   | " << triangles_skipped    << "\n";
    ostream << "\tDoubled objects   | " << triangles_doubled    << "\n";
    ostream << "\tcost travel       | " << cost_travel          << "\n";
    ostream << "\tcost intersect    | " << cost_intersect       << "\n";
    ostream << "\tbytes kdtree      | " << size_bytes           << "\n";
    ostream << "\tbytes triangles   | " << triangles_bytes      << "\n";
}