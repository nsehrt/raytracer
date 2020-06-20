#pragma once

#include "material.h"
#include "matrix.h"
#include "intersection.h"

class Shape
{
public:

    Shape()
    {
        transform = Matrix<4, 4>::identity();
    }

    Shape(const Material& m)
    {
        transform = Matrix<4, 4>::identity();
        material = m;
    }

    Matrix<4, 4> WorldInverse() const
    {
        return transform.inverse();
    }

    virtual Tuple normalAt(const Tuple& p) const = 0;

    Material material;
    Matrix<4, 4> transform;

protected:

   

};