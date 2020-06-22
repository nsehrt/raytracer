#pragma once

#include "shape.h"

class Cone : public Shape
{
public:
    Cone() : Shape()
    {
    }
    Cone(const Material& m) : Shape(m) {}

    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p) const override;

    float minimum = -std::numeric_limits<float>::infinity();
    float maximum = std::numeric_limits<float>::infinity();
    bool closed = false;

private:
    bool checkCaps(const Ray& r, float t, float y);
    void intersectCaps(const Ray& r, std::vector<Intersection>& xs);
};