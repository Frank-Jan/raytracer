#ifndef RAYTRACER_CLI_H
#define RAYTRACER_CLI_H

#include <string>
#include "WorldFactory.h"

class CLI
{
public:
    CLI(int argc, char * argv[], std::ostream& o = std::cout);

    void printArgs(std::ostream&);

    void printHelp(std::ostream&);

    WorldFactory wf;
    std::string infile;
    std::string outfile;
    std::string outfileT;
    bool printTree;
    bool printImage;
    bool renderImage;
    unsigned repeat;
    bool run;

};

#endif //RAYTRACER_CLI_H
