#include "export/bmp.h"
#include "Frame.h"
#include "Renderer.h"
#include "Scene.h"
#include "Timer.h"
#include <iostream>
#include "KDTreeB/Dot.h"
#include "KDTreeA/Dot.h"
#include "WorldFactory.h"
#include "Logger.h"


inline const bool printTree = false;
inline const bool MAKE_IMAGE = false;


int main() {
    /*
     * steps:
     * 1: load scene
     * 2: render scene
     * 3: save scene
     */

    std::string object_file_path = "../objects/";
    std::string obj_extension = ".obj";
    std::string bmp_file_path = "../pictures/";
    std::string bmp_extension = ".bmp";
    std::vector<std::string> file_names = {
//                                          "cube",
//                                          "icosahedron",
//                                          "bunny_low",
//                                           "bunny",
                                           "dragon"
                                           };

    std::string obj_file;
    std::string bmp_file;
    for(const std::string& str : file_names)
    {
        obj_file = object_file_path + str + obj_extension;
        bmp_file = bmp_file_path + str + bmp_extension;
        Timer timer;
        double elapsed_time;

        WorldFactory wf;
//        wf._type = WorldType::KDTREEA;
        wf._type = WorldType::KDTREEB;
//        wf._type = WorldType::SIMPLE;

        timer.start();

        std::cout << "Loading scene... \"" << obj_file << "\"" << std::endl;
        Scene scene;
//
//        std::string str = "load";
        scene.load_from_file(wf, obj_file);

//    scene.load(wf);

        elapsed_time = timer.elapsed();
        std::cout << "Done in " << elapsed_time << timer.units() << std::endl;
        LOGGER.preprocess_time = elapsed_time;
        if((wf._type == WorldType::KDTREEA) & printTree) {
            std::ofstream file;
            file.open("../pictures/kdtreea.dot", std::ios::trunc);

            if (!file.is_open()) {
                std::cerr << "Unable to open file\n";
                return 0;
            }
            std::cout << "Print tree for: " << str << "\n";
            KDTreeA::printKDTree(file, *((KDTreeA::KDTree *) scene.world));
            file.close();
        }
        else if((wf._type == WorldType::KDTREEB) && printTree) {
            std::ofstream file;
            file.open("../pictures/kdtreeb.dot", std::ios::trunc);

            if (!file.is_open()) {
                std::cerr << "Unable to open file\n";
                return 0;
            }
            std::cout << "Print tree for: " << str << "\n";
            KDTreeB::printKDTree(file, *((KDTreeB::KDTree *) scene.world));
            file.close();
        }


        if(!MAKE_IMAGE) {
            LOGGER(std::cout);
            LOGGER = Logger();
            continue;
        }

        std::cout << "Trace scene..." << std::endl;

        timer.start();
        Frame* frame = render(&scene);
        elapsed_time = timer.elapsed();
        std::cout << std::endl;
        std::cout << "Done in " << elapsed_time << timer.units() << std::endl;
        LOGGER.render_time = elapsed_time;

        std::cout << "Save file to... \"" << bmp_file << "\"" << std::endl;
        generateBitmapImage((unsigned char*) frame->image, frame->height,frame->width,  bmp_file.data());

        LOGGER(std::cout);

    }
    return 0;
}