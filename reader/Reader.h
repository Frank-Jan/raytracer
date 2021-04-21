#ifndef RAYTRACER_READER_H
#define RAYTRACER_READER_H

#include <string>

class World;
class WorldFactory;

int readFile(const std::string& filename, WorldFactory&, World*&);

#endif //RAYTRACER_READER_H