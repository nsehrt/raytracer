#pragma once

#include "shape.h"

class Sphere : public Shape
{
public:
    Sphere() : Shape() {}
    Sphere(const Material& m) : Shape(m){}

private:
    /*calculate the intersection(s) between this ray and a sphere*/
    std::vector<Intersection> localIntersect(const Ray& r) const
    {
        std::vector<Intersection> intersection(0);

        Ray rTrf = WorldInverse() * r;

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

        intersection.push_back(Intersection(t0, (Shape*)this));
        intersection.push_back(Intersection(t1, (Shape*)this));

        std::sort(intersection.begin(), intersection.end(), [](const Intersection& a, const Intersection& b)
                  {
                      return a.time < b.time;
                  });

        return intersection;
    }


    Tuple localNormalAt(const Tuple& p) const override
    {
        Tuple objPoint = transform.inverse() * p;
        Tuple objNormal = objPoint - Tuple::Point(0, 0, 0);
        Tuple worldNormal = transform.inverse().transpose() * objNormal;
        worldNormal.w = 0.0f;
        return worldNormal.normalize();
    }

};