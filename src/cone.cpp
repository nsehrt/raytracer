#include "cone.h"
#include "ray.h"

std::vector<Intersection> Cone::localIntersect(const Ray& r)
{
    std::vector<Intersection> xs{};

    auto rN = Ray(r.origin, r.direction.normalize());

    float a = rN.direction.x * rN.direction.x - rN.direction.y * rN.direction.y + rN.direction.z * rN.direction.z;
    float b = 2 * rN.origin.x * rN.direction.x - 2 * rN.origin.y * rN.direction.y + 2 * rN.origin.z * rN.direction.z;
    float c = rN.origin.x * rN.origin.x - rN.origin.y * rN.origin.y + rN.origin.z * rN.origin.z;

    if (std::abs(a) < EPSILON)
    {
        if (std::abs(b) >= EPSILON)
        {
            xs.push_back(Intersection(-c / (2.0f * b), this));
        }

        intersectCaps(rN, xs);
        return xs;
    }

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



    float y0 = rN.origin.y + t0 * rN.direction.y;

    if (minimum < y0 && y0 < maximum)
    {
        xs.push_back(Intersection(t0, this));
    }

    float y1 = rN.origin.y + t1 * rN.direction.y;

    if (minimum < y1 && y1 < maximum)
    {
        xs.push_back(Intersection(t1, this));
    }

    intersectCaps(rN, xs);

    return xs;
}

Tuple Cone::localNormalAt(const Tuple& p, const Intersection& i) const
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

    float y = std::sqrt(distance);
    if (p.y > 0.0f) y = -y;

    return Tuple::Vector(p.x, y, p.z);
}

bool Cone::checkCaps(const Ray& r, float t, float y)
{
    float x = r.origin.x + t * r.direction.x;
    float z = r.origin.z + t * r.direction.z;

    return (x * x + z * z) <= (y+EPSILON);
}

void Cone::intersectCaps(const Ray& r, std::vector<Intersection>& xs)
{

    if (!closed || (std::abs(r.direction.y) < EPSILON))
    {
        return;
    }

    float t = (minimum - r.origin.y) / r.direction.y;

    if (checkCaps(r, t, minimum))
    {
        xs.push_back(Intersection(t, this));
    }

    t = (maximum - r.origin.y) / r.direction.y;

    if (checkCaps(r, t, maximum))
    {
        xs.push_back(Intersection(t, this));
    }

}
