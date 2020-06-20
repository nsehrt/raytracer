#include "plane.h"
#include "ray.h"

std::vector<Intersection> Plane::localIntersect(const Ray& r)
{
    std::vector<Intersection> intersection(0);

    if (std::abs(r.direction.y) < EPSILON)
    {
        return intersection;
    }

    float t = -r.origin.y / r.direction.y;
    intersection.push_back(Intersection(t, this));

    return intersection;
}

Tuple Plane::localNormalAt(const Tuple& p) const
{
    return Tuple::Vector(0,1,0);
}
