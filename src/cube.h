#pragma once

#include "shape.h"

class Cube : public Shape
{
public:
    Cube() : Shape()
    {
    }
    Cube(const Material& m) : Shape(m) {}

    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p, const Intersection& i) const override;

private:
    std::pair<float, float> checkAxis(const float origin, const float direction) const;
};