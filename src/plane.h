#pragma once

#include "shape.h"

class Plane : public Shape
{
public:
    Plane() : Shape() {}
    Plane(const Material& m) : Shape(m) {}

    Ray* savedRay = nullptr;

    /*calculate the intersection(s) between this ray and a sphere*/
    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p) const override;

private:

};