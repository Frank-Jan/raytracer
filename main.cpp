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
#include "CLI.h"

//inline const bool printTree = false;
//inline const bool MAKE_IMAGE = false;

void printTree(WorldType wt, World* w, const std::string& path, const std::string& filename) {
    if(not (wt == WorldType::KDTREEA | wt == WorldType::KDTREEB))
        return;
    std::ofstream file;
    file.open(path + filename + ".dot", std::ios::trunc);

    if(!file.is_open()) {
        std::cerr   << "Unable to open file " << filename << ".dot" << "for printing a tree" << std::endl
                    << "Skipping printing the tree" << std::endl;
        return;
    }

    if(wt == WorldType::KDTREEA)
        KDTreeA::printKDTree(file, *((KDTreeA::KDTree *) w));
    if(wt == WorldType::KDTREEB)
        KDTreeB::printKDTree(file, *((KDTreeB::KDTree *) w));
    file.close();
}


int main(int argc, char * argv[]) {
    CLI cli(argc, argv, std::cerr);

    if(not cli.run)
        return 0;

    cli.printArgs(std::cout);

    /*
     * steps:
     * 1: load scene
     * 2: render scene
     * 3: save scene
     */

    std::string object_file_path    = "../objects/";
    std::string bmp_file_path       = "../pictures/";
    std::string tree_file_path      = "../pictures/";

    std::string obj_file = object_file_path + cli.infile;
    std::string bmp_file = bmp_file_path + cli.outfile;

    Timer timer;
    long pin_time;
    long preprocess_time;
    long render_time;
    timer.start();
    Scene scene;

    if(cli.repeat == 0) {
        // just run everything once

        std::cout << "Preprocessing scene" << std::endl;
        pin_time = timer.elapsed();
        scene.load_from_file(cli.wf, obj_file);

        LOGGER.preprocess_time = timer.elapsed() - pin_time;

        std::cout << "Rendering scene" << std::endl;
        pin_time = timer.elapsed();
        Frame* frame = render(&scene);
        LOGGER.render_time = timer.elapsed() - pin_time;

        if(cli.printImage) {
            std::cout << std::endl;
            std::cout << "Saving image to: " << bmp_file << std::endl;
            generateBitmapImage((unsigned char *) frame->image, frame->height, frame->width, bmp_file.data());
        }
        delete frame;
    }
    else if(cli.renderImage) {
        // benchmark rendering engine
        unsigned runs = cli.repeat;
        std::cout << "Benchmark rendering scene: \"" << obj_file << "\"" << std::endl;

        std::cout << "Preprocessing scene: \"" << obj_file << "\"" << std::endl;

        scene.load_from_file(cli.wf, obj_file);

        do {
            std::cout << "Rendering scene: " << runs << "/" << cli.repeat << std::endl;
            pin_time = timer.elapsed();

            Frame* frame = render(&scene);

            render_time = timer.elapsed() - pin_time;
            LOGGER.render_time += render_time;
            std::cout << "\t" << render_time << timer.units() << std::endl << std::endl;
            delete frame;
            runs--;
        }while( runs > 0 );

        std::cout << std::endl;

        cli.printArgs(std::cout);

        std::cout << std::endl;

        std::cout << "Results------------------------------" << std::endl;
        std::cout << "Number of runs    | " << cli.repeat                                           << std::endl;
        std::cout << "Total time        | " << LOGGER.render_time << timer.units()              << std::endl;
        std::cout << "Average time      | " << double(LOGGER.render_time)/double(cli.repeat)    << std::endl;
    }
    else {
        // benchmark preprocessor
        unsigned runs = cli.repeat;
        std::cout << "Benchmark: Preprocessing scene: \"" << obj_file << "\"" << cli.repeat << " times" << std::endl;
        do {
            scene.clear();
            std::cout << " run: " << runs << " / " << cli.repeat << std::endl;
            pin_time = timer.elapsed();
            scene.load_from_file(cli.wf, obj_file);
            preprocess_time = timer.elapsed() - pin_time;
            LOGGER.preprocess_time += preprocess_time;
            std::cout << "\t" << preprocess_time << timer.units() << std::endl << std::endl;
            runs--;
        } while( runs > 0 );

        std::cout << std::endl;

        cli.printArgs(std::cout);

        std::cout << std::endl;

        std::cout << "Results------------------------------" << std::endl;
        std::cout << "Number of runs    | " << cli.repeat                                           << std::endl;
        std::cout << "Total time        | " << LOGGER.preprocess_time << timer.units()              << std::endl;
        std::cout << "Average time      | " << double(LOGGER.preprocess_time)/double(cli.repeat)    << std::endl;
    }
    std::cout << std::endl;
//    LOGGER(std::cout);
    return 0;
}