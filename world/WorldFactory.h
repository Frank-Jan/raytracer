#ifndef RAYTRACER_WORLDFACTORY_H
#define RAYTRACER_WORLDFACTORY_H

#include "World.h"
#include "SimpleWorld.h"
#include "world/KDTreeA/KDTree.h"
#include "world/KDTreeB/KDTree.h"

enum class WorldType
{
    SIMPLE = 0,
    KDTREEA,
    KDTREEB
};

struct WorldFactory
{
    WorldType _type = WorldType::SIMPLE;
    World* get(std::vector<Triangle>& objects) const {
        switch (_type)
        {
            case WorldType::KDTREEA:
                return new KDTreeA::KDTree(objects);
            case WorldType::KDTREEB:
                return new KDTreeB::KDTree(objects);
//            case WorldType::SIMPLE:
//                return new SimpleWorld(objects);
            default:
                return new SimpleWorld(objects);
        }
    }
};


#endif //RAYTRACER_WORLDFACTORY_H
