#include "cylinder.h"
#include "ray.h"

std::vector<Intersection> Cylinder::localIntersect(const Ray& r)
{
    std::vector<Intersection> xs{};

    float a = r.direction.x * r.direction.x + r.direction.z * r.direction.z;

    if (a < EPSILON)
    {
        intersectCaps(r, xs);
        return xs;
    }

    float b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
    float c = (r.origin.x * r.origin.x + r.origin.z * r.origin.z) - 1.0f;

    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0)
    {
        return {};
    }

    float t0 = (-b - std::sqrt(discriminant)) / (2.0f * a);
    float t1 = (-b + std::sqrt(discriminant)) / (2.0f * a);

    if (t0 > t1)
    {
        float t = t0;
        t0 = t1;
        t1 = t;
    }



    float y0 = r.origin.y + t0 * r.direction.y;

    if (minimum < y0 && y0 < maximum)
    {
        xs.push_back(Intersection(t0, this));
    }

    float y1 = r.origin.y + t1 * r.direction.y;

    if (minimum < y1 && y1 < maximum)
    {
        xs.push_back(Intersection(t1, this));
    }

    intersectCaps(r, xs);

    return xs;
}

Tuple Cylinder::localNormalAt(const Tuple& p) const
{
    float distance = p.x * p.x + p.z * p.z;

    if (distance < 1.0f && p.y >= (maximum - EPSILON))
    {
        return Tuple::Vector(0, 1, 0);
    }

    if (distance < 1.0f && p.y <= (minimum + EPSILON))
    {
        return Tuple::Vector(0, -1, 0);
    }

    return Tuple::Vector(p.x, 0, p.z);
}

bool Cylinder::checkCaps(const Ray& r, float t)
{
    float x = r.origin.x + t * r.direction.x;
    float z = r.origin.z + t * r.direction.z;

    return (x * x + z * z) <= 1.0f;
}

void Cylinder::intersectCaps(const Ray& r, std::vector<Intersection>& xs)
{

    if (!closed || (r.direction.y <= EPSILON && r.direction.y >= -EPSILON))
    {
        return;
    }

    float t = (minimum - r.origin.y) / r.direction.y;

    if (checkCaps(r, t))
    {
        xs.push_back(Intersection(t, this));
    }

    t = (maximum - r.origin.y) / r.direction.y;

    if (checkCaps(r, t))
    {
        xs.push_back(Intersection(t, this));
    }

}
