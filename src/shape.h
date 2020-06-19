#pragma once

#include "matrix.h"
#include "material.h"

class Shape
{
public:

    Shape()
    {
        world = Matrix<4, 4>::identity();
    }

    Shape(const Material& m)
    {
        world = Matrix<4, 4>::identity();
        material = m;
    }

    Matrix<4, 4> WorldInverse() const
    {
        return world.inverse();
    }

    virtual Tuple normalAt(const Tuple& p) const
    {
        return Tuple::Vector(0, 0, 0);
    };

    Material material;
    Matrix<4, 4> world;

protected:

   

};