#pragma once

#include "shape.h"

class Plane : public Shape
{
public:
    Plane() : Shape() {}
    Plane(const Material& m) : Shape(m) {}

    Ray* savedRay = nullptr;

    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p, const Intersection& i) const override;

private:

};