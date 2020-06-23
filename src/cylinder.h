#pragma once

#include "shape.h"

class Cylinder : public Shape
{
public:
    Cylinder() : Shape()
    {
    }
    Cylinder(const Material& m) : Shape(m) {}

    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p, const Intersection& i) const override;

    float minimum = -std::numeric_limits<float>::infinity();
    float maximum = std::numeric_limits<float>::infinity();
    bool closed = false;

private:
    bool checkCaps(const Ray& r, float t);
    void intersectCaps(const Ray& r, std::vector<Intersection>& xs);
};