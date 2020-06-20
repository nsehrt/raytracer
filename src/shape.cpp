#include "shape.h"
#include "ray.h"

std::vector<Intersection> Shape::intersect(const Ray& r)
{
        Ray localRay = transform.inverse() * r;
        return localIntersect(localRay);
}

Tuple Shape::normalAt(const Tuple& p) const
{
        auto localPoint = transform.inverse() * p;
        auto localNormal = localNormalAt(localPoint);
        auto worldNormal = transform.inverse().transpose() * localNormal;
        worldNormal.w = 0.0f;

        return worldNormal.normalize();
}
