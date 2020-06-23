#include "shape.h"
#include "ray.h"

std::vector<Intersection> Shape::intersect(const Ray& r)
{
        Ray localRay = transform.inverse() * r;
        return localIntersect(localRay);
}

Tuple Shape::normalAt(const Tuple& p, const Intersection& i) const
{
    auto localPoint = worldToObject(p);
    auto localNormal = localNormalAt(localPoint, i);

    return normalToWorld(localNormal);
}

Tuple Shape::worldToObject(const Tuple& point) const
{
    auto p = (parent == nullptr) ? point : parent->worldToObject(point);
    return transform.inverse() * p;
}

Tuple Shape::normalToWorld(const Tuple& point) const
{
    auto n = transform.inverse().transpose() * point;
    n.w = 0.0f;
    n = n.normalize();

    return (parent == nullptr) ? n : parent->normalToWorld(n);
}

Material Shape::getMaterial()
{
    if (parent == nullptr)
    {
        return material;
    }
    else
    {
        return parent->getMaterial();
    }

}
