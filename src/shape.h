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

    std::vector<Intersection> intersect(const Ray& r)
    {
        Ray localRay = transform.inverse() * r;
        return localIntersect(localRay);
    }

    Tuple normalAt(const Tuple& p)
    {
        auto localPoint = transform.inverse() * p;
        auto localNormal = localNormalAt(localPoint);
        auto worldNormal = transform.inverse().transpose() * localNormal;
        worldNormal.w = 0.0f;

        return worldNormal.normalize();
    }

    Material material;
    Matrix<4, 4> transform;

protected:
    virtual std::vector<Intersection> localIntersect(const Ray& r) const = 0;
    virtual Tuple localNormalAt(const Tuple& p) const = 0;

};