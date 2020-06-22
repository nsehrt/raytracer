#include "cube.h"
#include "ray.h"

std::vector<Intersection> Cube::localIntersect(const Ray& r)
{
    auto xMax = checkAxis(r.origin.x, r.direction.x);
    auto yMax = checkAxis(r.origin.y, r.direction.y);
    auto zMax = checkAxis(r.origin.z, r.direction.z);

    float tMin = std::max(xMax.first, std::max(yMax.first, zMax.first));
    float tMax = std::min(xMax.second, std::min(yMax.second, zMax.second));

    if (tMin > tMax) return {};

    return Intersection::intersections(Intersection(tMin, this), Intersection(tMax, this));
}

Tuple Cube::localNormalAt(const Tuple& p) const
{
    float maxC = std::max(std::abs(p.x), std::max(std::abs(p.y), std::abs(p.z)));

    if (maxC == std::abs(p.x))
    {
        return Tuple::Vector(p.x, 0, 0);
    }
    else if (maxC == std::abs(p.y))
    {
        return Tuple::Vector(0, p.y, 0);
    }

    return Tuple::Vector(0, 0, p.z);
}

std::pair<float, float> Cube::checkAxis(const float origin, const float direction) const
{
    float tMin, tMax;

    float tMinNum = (-1 - origin);
    float tMaxNum = (1 - origin);

    if (std::abs(direction) >= EPSILON)
    {
        tMin = tMinNum / direction;
        tMax = tMaxNum / direction;
    }
    else
    {
        tMin = tMinNum * std::numeric_limits<float>::infinity();
        tMax = tMaxNum * std::numeric_limits<float>::infinity();
    }

    if (tMin > tMax)
    {
        float t = tMin;
        tMin = tMax;
        tMax = t;
    }

    return std::pair<float, float>(tMin, tMax);
}
