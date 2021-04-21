#ifndef RAYTRACER_TIMER_H
#define RAYTRACER_TIMER_H

#include <chrono>

class Timer
{
public:
    Timer() {
        start();
    }
    void start() {
        m_StartTime = std::chrono::high_resolution_clock::now();
    }

    double elapsed() {
        return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - m_StartTime).count());
    }

    const char* units() {
        return u;
    }



private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    const char* u = "ms";
};



#endif //RAYTRACER_TIMER_H
