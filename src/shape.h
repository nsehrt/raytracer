#pragma once

#include "material.h"
#include "matrix.h"
#include "intersection.h"

class Ray;

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

    std::vector<Intersection> intersect(const Ray& r);

    Tuple normalAt(const Tuple& p) const;

    Material material;
    Matrix<4, 4> transform;

    virtual std::vector<Intersection> localIntersect(const Ray& r) = 0;
    virtual Tuple localNormalAt(const Tuple& p) const = 0;

protected:


};