#include "Color.h"
#include "cmath"

Color& Color::operator=(const Color &rhs)
{
    red = rhs.red;
    green = rhs.green;
    blue = rhs.blue;
    return *this;
}

Color Color::operator+(const Color &rhs) const
{
    return Color(red+rhs.red, green+rhs.green, blue+rhs.blue);
}

Color Color::operator*(const Color &rhs) const
{
    return Color(red*rhs.red, green*rhs.green, blue*rhs.blue);
}

Color Color::operator^(FLOAT p) const
{
    return Color(pow(red,p), pow(green, p), pow(blue,p));
}

Color Color::operator*(FLOAT d) const
{
    return Color(red*d, green*d, blue*d);
}

Color Color::operator/(FLOAT d) const
{
    return Color(red/d, green/d, blue/d);
}

Color& Color::operator+=(const Color &rhs)
{
    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;
    return *this;
}

Color& Color::operator*=(FLOAT d)
{
    red *= d;
    green *= d;
    blue *= d;
    return *this;
}

Color& Color::operator/=(FLOAT d)
{
    red /= d;
    green /=d;
    blue /=d;
    return *this;
}

Color operator*(FLOAT d, const Color& c)
{
    return Color(c.red*d, c.green*d, c.blue*d);
}

Color max_to_one(const Color& c)
{
    FLOAT max_value = std::max(c.red, std::max(c.green, c.blue));
    if(max_value > 1.0)
        return c/max_value;
    return c;
}

Color clamp_to_color(const Color& c)
{
    if(c.red > 1.0 || c.green > 1.0 || c.blue > 1.0)
        return Color(1,0,0);
    return c;
}

Color shift_to_white(const Color& c)
{
    FLOAT max_value = std::max(c.red, std::max(c.green, c.blue));
    if(max_value > 1.0) {
        FLOAT total = c.red + c.green + c.blue;
        if(total >= 3.0)
            return Color(1.0);
        Color L = c;
        FLOAT overflow = 0;
        FLOAT n = 0;
        if(L.red > 1.0) {
            overflow += c.red - 1.0;
            L.red = 1.0;
            n+=1;
        }
        if(L.green > 1.0) {
            overflow += c.green - 1.0;
            L.green = 1.0;
            n+=1;
        }
        if(L.blue > 1.0) {
            overflow += c.blue - 1.0;
            L.blue = 1.0;
            n+=1;
        }
        overflow /= (3-n);
        if(L.red < 1.0) {
            L.red += overflow;
            if(L.red > 1.0)
                L.red = 1.0;
        }
        if(L.green < 1.0) {
            L.green += overflow;
            if(L.green > 1.0)
                L.green = 1.0;
        }
        if(L.blue < 1.0) {
            L.blue += overflow;
            if(L.blue > 1.0)
                L.blue = 1.0;
        }

        return L;
    }
    return c;
}