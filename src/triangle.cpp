#include "triangle.h"
#include "ray.h"

Triangle::Triangle(const Tuple& _p1, const Tuple& _p2, const Tuple& _p3)
{
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;

    e1 = p2 - p1;
    e2 = p3 - p1;

    normal = e2.cross(e1).normalize();

}

std::vector<Intersection> Triangle::localIntersect(const Ray& r)
{
    auto dirCrossE2 = r.direction.cross(e2);

    float det = e1.dot(dirCrossE2);

    if (std::abs(det) < EPSILON)
    {
        return {};
    }

    float f = 1.0f / det;

    auto p1ToOrigin = r.origin - p1;
    float u = f * p1ToOrigin.dot(dirCrossE2);

    if (u < 0.0f || u > 1.0f)
    {
        return {};
    }

    auto originCrossE1 = p1ToOrigin.cross(e1);
    float v = f * r.direction.dot(originCrossE1);

    if (v < 0.0f || (u + v) > 1.0f)
    {
        return {};
    }

    float t = f * e2.dot(originCrossE1);

    return { Intersection(t, this) };
}

Tuple Triangle::localNormalAt(const Tuple& p, const Intersection& i) const
{
    return normal;
}



/*smooth triangle*/

std::vector<Intersection> SmoothTriangle::localIntersect(const Ray& r)
{
    auto dirCrossE2 = r.direction.cross(e2);

    float det = e1.dot(dirCrossE2);

    if (std::abs(det) < EPSILON)
    {
        return {};
    }

    float f = 1.0f / det;

    auto p1ToOrigin = r.origin - p1;
    float u = f * p1ToOrigin.dot(dirCrossE2);

    if (u < 0.0f || u > 1.0f)
    {
        return {};
    }

    auto originCrossE1 = p1ToOrigin.cross(e1);
    float v = f * r.direction.dot(originCrossE1);

    if (v < 0.0f || (u + v) > 1.0f)
    {
        return {};
    }

    float t = f * e2.dot(originCrossE1);

    return { Intersection(t, this, u, v) };
}

Tuple SmoothTriangle::localNormalAt(const Tuple& p, const Intersection& i) const
{
    return n2 * i.u + n3 * i.v + n1 * (1 - i.u - i.v);
}
