#pragma once

#include "intersection.h"
#include "matrix.h"

class Ray
{
public:

    /*constructors*/
    Ray()
    {
        origin = Tuple::Point();
        direction = Tuple::Vector();
    }

    Ray(const Tuple& _origin, const Tuple& _direction)
    {
        origin = _origin;
        direction = _direction;
    }

    /*basic functionality*/
    Tuple position(float t) const
    {
        return origin + direction * t;
    }

    IntersectionData precompute(const Intersection& i, const std::vector<Intersection>& xs = {}) const;

    /*transform with matrix*/
    Ray transform(const Matrix<4,4>& m) const
    {
        Ray res;

        res.origin = m * origin;
        res.direction = m * direction;

        return res;
    }

    friend Ray operator*(const Matrix<4, 4>& m, const Ray& r)
    {
        return r.transform(m);
    }

    /*member variables*/
    Tuple origin;
    Tuple direction;

private:

};