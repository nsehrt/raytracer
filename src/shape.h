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

    Matrix<4, 4> WorldInverse() const
    {
        return world.inverse();
    }

    virtual Tuple normalAt(const Tuple& p) const = 0;

    Material material;
    Matrix<4, 4> world;

protected:

   

};