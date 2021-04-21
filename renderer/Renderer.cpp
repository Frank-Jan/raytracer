#include <iostream>
#include "constants.h"
#include "Renderer.h"
#include "Frame.h"
#include "Scene.h"
#include "world/SimpleWorld.h"
#include "Camera.h"

#include "Tracers.h"
#include "Triangle.h"
#include "Samplers.h"

#include "Color.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Point2D.h"


Frame* render(Scene* scene)
{
    Camera* camera      = scene->camera;
    Sampler* sampler    = scene->sampler;
    Tracer* tracer      = scene->tracer;

    Frame* frame = camera->getFrame();
    unsigned int num_samples = scene->num_samples_sqrt*scene->num_samples_sqrt;

    Point2D pp;
    Color L;
    Color black(0,0,0);
    Ray ray;

    for (int r =  - frame->height/2; r < frame->height/2; r++) {        // top  -> bottom
        for (int c =  - frame->width/2; c < frame->width/2; c++) {    // left -> right
            L = black;

            for(int p = 0; p < scene->num_samples_sqrt; ++p) {
                for(int q = 0; q < scene->num_samples_sqrt; ++q) {
                    sampler->sample_unit_square(pp, p, q);
                    pp.x += c;
                    pp.y += r;
                    camera->transform(pp, ray);
                    L += tracer->trace_ray(ray);
                }
            }

            L /= FLOAT(num_samples);
            L *= camera->exposure;

//            L = max_to_one(L);
//            L = clamp_to_color(L);
            L = shift_to_white(L);

            frame->setPixel(c + frame->width/2,r + frame->height/2, L);
            if(CONSOLE_OUTPUT) {
                if (c == 0) {
                    printf("\rProgress: %d%%", int((r+ frame->height/2) * 100 / frame->height));
                    fflush(stdout);
                }
            }
        }
    }
    if(CONSOLE_OUTPUT) {
        printf("\rProgress: 100%%");
        fflush(stdout);
    }
    return frame;
}