#pragma once

#include "matrix.h"

class Shape
{
public:

    Shape()
    {
        world = Matrix<4, 4>::identity();
    }

    void setWorld(const Matrix<4, 4>& w)
    {
        world = w;
    }


    Matrix<4,4> world;

private:



};