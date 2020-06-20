#include "testshape.h"
#include "ray.h"

std::vector<Intersection> TestShape::localIntersect(const Ray& r)
{
    savedRay = std::make_unique<Ray>();
    savedRay->origin = r.origin;
    savedRay->direction = r.direction;
    return std::vector<Intersection>();
}

Tuple TestShape::localNormalAt(const Tuple& p) const
{
    return Tuple(p.x,p.y,p.z,0.0f);
}
