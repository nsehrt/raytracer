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

    Tuple normalAt(const Tuple& p, const Intersection& i) const;

    Tuple worldToObject(const Tuple& point)const;
    Tuple normalToWorld(const Tuple& point)const;


    Material getMaterial();

    bool operator==(const Shape& s) const
    {
        return material == s.material && transform == s.transform;
    }

    bool operator!=(const Shape& s) const
    {
        return !operator==(s);
    }

    Material material;
    Matrix<4, 4> transform;
    Shape* parent = nullptr;

    virtual std::vector<Intersection> localIntersect(const Ray& r) = 0;
    virtual Tuple localNormalAt(const Tuple& p, const Intersection& i) const = 0;

protected:


};