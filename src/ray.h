#pragma once

#include "matrix.h"
#include "intersection.h"
#include "sphere.h"

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

    /*calculate the intersection(s) between this ray and a sphere*/
    std::vector<Intersection> intersects(std::shared_ptr<Shape> shape) const
    {
        std::vector<Intersection> intersection(0);

        Ray rTrf = shape->WorldInverse() * *this;

        Tuple sphereToRay = rTrf.origin - Tuple::Point(0, 0, 0);

        float a = rTrf.direction.dot(rTrf.direction);
        float b = 2 * rTrf.direction.dot(sphereToRay);
        float c = sphereToRay.dot(sphereToRay) - 1.0f;

        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
        {
            return intersection;
        }

        float t0 = (-b - std::sqrt(discriminant)) / (2 * a);
        float t1 = (-b + std::sqrt(discriminant)) / (2 * a);

        intersection.push_back(Intersection(t0, shape.get()));
        intersection.push_back(Intersection(t1, shape.get()));

        std::sort(intersection.begin(), intersection.end(), [](const Intersection& a, const Intersection& b)
                  {
                      return a.time < b.time;
                  });

        return intersection;
    }

    IntersectionData precompute(const Intersection& i) const
    {
        IntersectionData comps;

        comps.time = i.time;
        comps.object = i.object;
        comps.point = position(comps.time);
        comps.eyeV = -direction;
        comps.normalV = comps.object->normalAt(comps.point);

        if (comps.normalV.dot(comps.eyeV) < 0.0f)
        {
            comps.inside = true;
            comps.normalV *= -1.0f;
        }

        return comps;
    }

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