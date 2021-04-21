#include <algorithm>
#include "CLI.h"
#include "WorldFactory.h"

enum token{
    f_repeat,
    f_world,
    f_outputfile,
    f_inputfile,
    f_print_tree,
    f_print_image,
    f_render,
    f_help,
    unknown
};

token getToken(std::string_view& sv)
{
    if(sv == "-r")
        return f_repeat;
    if(sv == "-i")
        return f_inputfile;
    if(sv == "-o")
        return f_outputfile;
    if(sv == "-p")
        return f_print_tree;
    if(sv == "-I")
        return f_print_image;
    if(sv == "-w")
        return f_world;
    if(sv == "-rend")
        return f_render;
    if(sv == "-h")
        return f_help;
    if(sv == "--help")
        return f_help;
    return unknown;
}

std::string convert2bmp(std::string_view sv)
{
    if(sv.ends_with(".bmp"))
        return std::string(sv);
    std::string str(sv);
    str.append(".bmp");
    return str;
}

std::string convert2obj(std::string_view sv)
{
    if(sv.ends_with(".obj"))
        return std::string(sv);
    std::string str(sv);
    str.append(".obj");
    return str;
}

WorldType getWorld(std::string_view sv) {
    if(sv == "s")
        return WorldType::SIMPLE;
    if(sv == "simple")
        return WorldType::SIMPLE;
    if(sv == "kdtree")
        return WorldType::KDTREEB;
    if(sv == "A" | sv == "a")
        return WorldType::KDTREEA;
    if(sv == "B" || sv == "b" || sv == "k" || sv == "kd")
        return WorldType::KDTREEB;
    return WorldType::SIMPLE;
}

std::string getWorld(WorldType wt) {
    switch(wt)
    {
        case WorldType::SIMPLE:
            return "Simple world";
        case WorldType::KDTREEA:
            return "KDTree A";
        case WorldType::KDTREEB:
            return "KDTree B";
    }
    return "Unknown";
}

CLI::CLI(int argc, char * argv[], std::ostream& o)
{
    wf._type    = WorldType::SIMPLE;
    infile      = "current.bmp";
    outfile     = "cube.obj";
    printTree   = false;
    printImage  = true;
    repeat      = 0;
    renderImage = true;
    run         = false;

    if(argc <= 0) {
        printHelp(o);
        return;
    }
    run = true;

    std::string_view sv;
    for(int i = 1; i < (argc); i++)
    {
        sv = argv[i];
        o << sv << std::endl;
        switch(getToken(sv))
        {
            case f_repeat: {
                if(i < (argc - 1)) {
                    repeat = atoi(argv[i+1]);
                    i++;
                }
                break;
            }
            case f_world: {
                if(i < (argc - 1)) {
                    wf._type = getWorld(argv[i+1]);
                    i++;
                }
                break;
            }
            case f_outputfile: {
                if(i < (argc - 1)) {
                    outfile = convert2bmp(argv[i + 1]);
                    i++;
                }
                break;
            }
            case f_inputfile: {
                if(i < (argc - 1)) {
                    infile = convert2obj(argv[i+1]);
                    i++;
                }
                break;
            }
            case f_print_tree: {
                if(i < (argc - 1)) {
                    printTree = atoi(argv[i+1]);
                    i++;
                }
                break;
            }
            case f_print_image: {
                if(i < (argc - 1)) {
                    printImage = atoi(argv[i+1]);
                    i++;
                }
                break;
            }
            case f_render: {
                if(i < (argc - 1)) {
                    renderImage = atoi(argv[i+1]);
                    if(not renderImage)
                        printImage = false;
                    i++;
                }
                break;
            }
            case f_help: {
                printHelp(o);
                run = false;
                i = argc;
                break;
            }
            default: {
                std::cerr << "Unknown flag: " << argv[i] << std::endl;
                printHelp(o);
                run = false;
                i = argc;
                break;
            }
        }
    }

    if(not (wf._type == WorldType::KDTREEA | wf._type == WorldType::KDTREEB) & printTree) {
        printTree = false;
        o << "Cannot print a tree for non-tree world types" << std::endl;
        run = false;
    }

    if(printImage)
        renderImage = true;
}

void CLI::printArgs(std::ostream& o)
{
    o << "CLI-------------------------------------------"   << std::endl;
    o << "  input file:  " << infile                        << std::endl;
    o << "  output file: " << outfile                       << std::endl;
    o << "  world type:  " << getWorld(wf._type)            << std::endl;
    o << "  print tree:  " << (printTree?  "yes" : "no")    << std::endl;
    o << "  render       " << (renderImage? "yes" : "no")  << std::endl;
    o << "  print image: " << (printImage? "yes" : "no")    << std::endl;
    o << "CLI END---------------------------------------"   << std::endl;
}

void CLI::printHelp(std::ostream& o)
{
    o <<  "How to use the raytracer: \n"
      <<  " -i  [filename]  add an input filename, .obj will be added/ignored. \n"
      <<  " -o  [filename]  add an output filename, .dot and .bmp will be added. \n"
      <<  " -p  [0|1]       if you want to get a dot file: defaults to 0, doesn't work with SIMPLE world \n"
      <<  " -I  [0|1]       if you want a .bmp file, add -o filename otherwise filename will default to 'current.bmp' \n"
      <<  " -w  [s|A|B|KDTreeA|KDTreeB]  The type of world you want, default: s \n"
      <<  " -rend [0|1]     if you wish to render an image, default: true \n"
      <<  " -r: [n]         if you want to repeat certain actions for benchmarking:  \n"
      <<  "                 if -rend = 0:  benchmark the preprocessing \n"
      <<  "                 if -rend = 1:  benchmark the rendering \n"
      << std::endl;
}