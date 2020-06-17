#pragma once
#include "tuple.h"

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
    Color operator* (const Color& a)
    {
        return Color(x * a.x, y * a.y, z * a.z);
    }

    Color operator* (const float& scalar)
    {
        return Color(scalar * x, scalar * y, scalar * z);
    }

    friend Color operator* (const float& scalar, const Color& a)
    {
        return Color(scalar * a.x, scalar * a.y, scalar * a.z);
    }

private:


};