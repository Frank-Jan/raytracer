#include "Scene.h"
#include "world/SimpleWorld.h"
#include "Camera.h"
#include "Triangle.h"
#include "Tracers.h"
#include "Samplers.h"
#include "Light.h"
#include <iostream>
#include <random>
#include "constants.h"
#include "BRDF_all.h"
#include "Ambient.h"
#include "PointLight.h"
#include "Directional.h"
#include "AmbientOccluder.h"
#include "Matte.h"
#include "Phong.h"
#include "Emissive.h"
#include "AreaLight.h"
#include "AreaLighting.h"
#include "Reader.h"
#include "WorldFactory.h"
#include "Logger.h"


Scene::Scene() :
camera(nullptr),
world(nullptr),
sampler(nullptr),
tracer(nullptr),
num_samples_sqrt(8)
{ }

Scene::~Scene()
{
    clear();
}

void Scene::set_num_samples(int n)
{
    num_samples_sqrt = n;
    if(!sampler)
        sampler->set_num_sampes_sqrt(n);
}

void Scene::load(WorldFactory& wf) {
    clear();

    LOGGER.filename = "buildfile";
    std::vector<Triangle> triangles;

    triangles.emplace_back(Vector3D(-0.5,-0.5,0),Vector3D(-0.5,0.5,0),Vector3D(0.5,-0.5,0));
    triangles.back().c = Color(1.0,0,0);

    triangles.emplace_back(Vector3D(1.0,-0.5,0),Vector3D(1.0,0.5,0),Vector3D(1.0,-0.5,0));
    triangles.back().c = Color(0,0,1.0);

    triangles.emplace_back(Vector3D(-1.0,-0.5,0),Vector3D(-1.0,0.5,0),Vector3D(-1.0,-0.5,0));
    triangles.back().c = Color(0,1.0,0.0);

    triangles.emplace_back(Vector3D(-2.0,-0.5,0),Vector3D(2.0,0.5,0),Vector3D(2.0,-0.5,0));
    triangles.back().c = Color(1.0,1.0,0.0);

    triangles.emplace_back(Vector3D(-2.0,-2.5,0),Vector3D(2.0,2.5,0),Vector3D(2.0,-2.5,0));
    triangles.back().c = Color(0,1.0,1.0);

    triangles.emplace_back(Vector3D(-0.5,-0.5,8),Vector3D(-0.5,0.5,8),Vector3D(0.5,-0.5,8));
    triangles.back().c = Color(0.0);

    triangles.emplace_back(Vector3D(1.0,-0.5,8),Vector3D(1.0,0.5,8),Vector3D(1.0,-0.5,8));
    triangles.back().c = Color(0);

    triangles.emplace_back(Vector3D(-1.0,-0.5,8),Vector3D(-1.0,0.5,8),Vector3D(-1.0,-0.5,8));
    triangles.back().c = Color(0);

    triangles.emplace_back(Vector3D(-2.0,-0.5,8),Vector3D(2.0,0.5,8),Vector3D(2.0,-0.5,8));
    triangles.back().c = Color(0);

    triangles.emplace_back(Vector3D(-2.0,-2.5,8),Vector3D(2.0,2.5,8),Vector3D(2.0,-2.5,8));
    triangles.back().c = Color(0);

    world = wf.get(triangles);

    int vres = 500;
    int hres = 500;
    FLOAT focal_point = 1.0;
    FLOAT camera_size = 1.0;
    FLOAT exposure = 1.0;
    num_samples_sqrt = 3;
    world->bg_color = Color(0.2);
    tracer = new RayCast(world);
    sampler = new Jittered(num_samples_sqrt);

    // SETUP CAMERA \\

    camera = new Camera(camera_size, hres, vres, focal_point);
    camera->translate(0,0,6);
    camera->lookat(0,0.5,0);

    // SETUP LIGHTS \\

}

void Scene::load_from_file(WorldFactory& wf, const std::string& filename)
{
    clear();
    int errcode = readFile(filename, wf, world);

    LOGGER.filename = filename;

    if(errcode != 1)
        throw "Error";
//
//    int vres = 2;
//    int hres = 2;

    int vres = 200;
    int hres = 200;

    FLOAT focal_point = 16;
//    FLOAT camera_size = 0.5;
    FLOAT camera_size = 2.0;
    FLOAT exposure = 1.0;
    num_samples_sqrt = 1;
    world->bg_color = Color(0.2);
    tracer = new RayCast(world);
    sampler = new Jittered(num_samples_sqrt);

    // SETUP CAMERA \\

    camera = new Camera(camera_size, hres, vres, focal_point);
//    camera->translate(1,2,1);
//    camera->lookat(0,0.5,-0.5);
    camera->translate(3,3.5,3);
    camera->lookat(0,0.5,0);

    // SETUP LIGHTS \\

}


void Scene::clear()
{
    delete camera;
    delete world;
    delete sampler;
    delete tracer;

    for(Material* m : materials)
        delete m;

    materials.resize(0);
    camera = nullptr;
    world = nullptr;
    sampler = nullptr;
    tracer = nullptr;
}

