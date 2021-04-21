#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H

class Scene;
class Color;
class Viewplane;
class SimpleWorld;
class Tracer;
class Sampler;
class Camera;
class Frame;

Frame* render(Scene*);

#endif //RAYTRACER_RENDERER_H
