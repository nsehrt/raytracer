#include "sphere.h"
#include "ray.h"

std::vector<Intersection> Sphere::localIntersect(const Ray& r)
{
    std::vector<Intersection> intersection(0);

    //Ray rTrf = WorldInverse() * r;

    Tuple sphereToRay = r.origin - Tuple::Point(0, 0, 0);

    float a = r.direction.dot(r.direction);
    float b = 2 * r.direction.dot(sphereToRay);
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

Tuple Sphere::localNormalAt(const Tuple& p) const
{
    return Tuple::Vector(p.x, p.y, p.z);
}
