#pragma once

#include "shape.h"

class Ray;

class TestShape : public Shape
{
public:
    TestShape() : Shape() {}
    TestShape(const Material& m) : Shape(m) {}

    std::unique_ptr<Ray> savedRay;


    /*calculate the intersection(s) between this ray and a sphere*/
    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p, const Intersection& i) const override;


};