#pragma once

#include "shape.h"

class Triangle : public Shape
{
public:
    Triangle(const Tuple& _p1, const Tuple& _p2, const Tuple& _p3);

    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p) const override;


    Tuple p1, p2, p3;
    Tuple e1, e2;
    Tuple normal;

private:


};