#pragma once

#include "shape.h"

class Sphere : public Shape
{
public:
    Sphere() : Shape() {}
    Sphere(const Material& m) : Shape(m){}

    Tuple normalAt(const Tuple& p) const override
    {
        Tuple objPoint = world.inverse() * p;
        Tuple objNormal = objPoint - Tuple::Point(0, 0, 0);
        Tuple worldNormal = world.inverse().transpose() * objNormal;
        worldNormal.w = 0.0f;
        return worldNormal.normalize();
    }

private:



};