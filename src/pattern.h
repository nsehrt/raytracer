#pragma once

#include "matrix.h"
#include "color.h"

class Shape;

class Pattern
{
public:

    Pattern()
    {
        a = Color::White();
        b = Color::Black();

        transform = Matrix<4, 4>::identity();
    }

    Pattern(const Color& _a, const Color& _b)
    {
        a = _a;
        b = _b;

        transform = Matrix<4, 4>::identity();
    }

    Color patternAtShape(const Shape* shape, const Tuple& point) const;

    Color a, b;
    Matrix<4, 4> transform;


    virtual Color patternAt(const Tuple& point) const = 0;
   

};


class StripePattern : public Pattern
{

public:
    StripePattern() : Pattern(){}
    StripePattern(const Color& a, const Color& b) : Pattern(a,b){}

    Color patternAt(const Tuple& point) const override
    {
        int fl = (int)std::floor(point.x);

        if (fl % 2 == 0)
        {
            return a;
        }
        else
        {
            return b;
        }
    }

};

class GradientPattern : public Pattern
{

public:
    GradientPattern() : Pattern() {}
    GradientPattern(const Color& a, const Color& b) : Pattern(a, b) {}

    Color patternAt(const Tuple& point) const override
    {
        auto distance = b - a;
        auto fraction = point.x - std::floor(point.x);
        return a + distance * fraction;
    }

};

class RingPattern : public Pattern
{

public:
    RingPattern() : Pattern() {}
    RingPattern(const Color& a, const Color& b) : Pattern(a, b) {}

    Color patternAt(const Tuple& point) const override
    {
        int fl = (int)std::floor(std::sqrt(point.x * point.x + point.z * point.z));

        if (fl % 2 == 0)
        {
            return a;
        }
        else
        {
            return b;
        }

    }

};


class CheckerPattern : public Pattern
{

public:
    CheckerPattern() : Pattern() {}
    CheckerPattern(const Color& a, const Color& b) : Pattern(a, b) {}

    Color patternAt(const Tuple& point) const override
    {
        int fl = (int)std::floor(point.x) + (int)std::floor(point.y) + (int)std::floor(point.z);

        if (fl % 2 == 0)
        {
            return a;
        }
        else
        {
            return b;
        }

    }

};