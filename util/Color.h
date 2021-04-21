#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <math.h>
#include "constants.h"


struct Color {
    FLOAT red   = 0;
    FLOAT green = 0;
    FLOAT blue  = 0;

    Color() : red(0), green(0), blue(0) {}
    Color(FLOAT grey) : red(grey), green(grey), blue(grey) {}
    Color(FLOAT red, FLOAT green, FLOAT blue) :
    red(red), green(green), blue(blue) {}

    Color& operator=(const Color &rhs);

    Color operator+(const Color &rhs) const;

    Color operator*(const Color &rhs) const;

    Color operator^(FLOAT p) const;

    Color operator*(FLOAT d) const;

    Color operator/(FLOAT d) const;

    Color& operator+=(const Color &rhs);

    Color& operator*=(FLOAT d);

    Color& operator/=(FLOAT d);

    friend Color operator*(FLOAT d, const Color& c);
};

Color max_to_one(const Color&);
Color clamp_to_color(const Color&);
Color shift_to_white(const Color&);

namespace color
{
    inline const Color black(0);
    inline const Color white(1.0);
    inline const Color red(1.0, 0.0, 0.0);
    inline const Color green(0.0, 1.0, 0.0);
    inline const Color blue(0.0, 0.0, 1.0);
}

#endif //RAYTRACER_COLOR_H
