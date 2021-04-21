#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <string>
#include <vector>

class Renderer;
class Camera;
class World;
class Sampler;
class Tracer;
class Frame;
class Material;
struct WorldFactory;

class Scene
{
public:
    Scene();
    ~Scene();

    void load(WorldFactory& wf);

//    void two_spheres();
//    void three_lights(int num_samples=8);
//    void ambient_test();
//    void compound_test();
    void set_num_samples(int n);
    void load_from_file(WorldFactory& wf, const std::string& str = "../objects/bunny_low.obj");

public:
    Camera* camera;
    World* world;
    Sampler* sampler;
    Tracer* tracer;

    int num_samples_sqrt;
    std::vector<Material*> materials;

public:
    // Deletes all objects
    void clear();
};


#endif //RAYTRACER_SCENE_H
