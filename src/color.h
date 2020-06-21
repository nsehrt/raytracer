#pragma once
#include "tuple.h"
#include <sstream>
#include <algorithm> 

class Color : public Tuple
{
public:
    /*constructors*/
    Color() : Tuple(0.0f, 0.0f, 0.0f, 0.0f){}
    Color(const Tuple& t) : Tuple(t.x, t.y, t.z, t.w){}
    Color(float r, float g, float b) : Tuple(r,g,b,0.0f){}

    float r() const
    {
        return x;
    }

    float g() const
    {
        return y;
    }

    float b() const
    {
        return z;
    }

    /*operator overload*/
    Color operator* (const Color& a) const
    {
        return Color(x * a.x, y * a.y, z * a.z);
    }

    Color operator* (const float& scalar) const
    {
        return Color(scalar * x, scalar * y, scalar * z);
    }

    friend Color operator* (const float& scalar, const Color& a)
    {
        return Color(scalar * a.x, scalar * a.y, scalar * a.z);
    }

    /*constant colors*/
    static Color const& White() { static Color color(1.0f, 1.0f, 1.0f); return color; }
    static Color const& Black() { static Color color(0.0f, 0.0f, 0.0f); return color; }

    std::string toString()
    {
        std::stringstream ss;
        ss << std::clamp((int)(x / 1.0f * 255), 0, 255) << " " << std::clamp((int)(y / 1.0f * 255), 0, 255) << " " << std::clamp((int)(z / 1.0f * 255), 0, 255);
        return ss.str();
    }

private:


};