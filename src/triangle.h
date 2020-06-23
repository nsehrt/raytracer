#pragma once

#include "shape.h"

class Triangle : public Shape
{
public:
    Triangle() = default;
    Triangle(const Tuple& _p1, const Tuple& _p2, const Tuple& _p3);

    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p, const Intersection& i) const override;


    Tuple p1, p2, p3;
    Tuple e1, e2;
    Tuple normal;

private:


};

class SmoothTriangle : public Triangle
{
public:
    SmoothTriangle(const Tuple& _p1, const Tuple& _p2, const Tuple& _p3, const Tuple& _n1, const Tuple& _n2, const Tuple& _n3) 
    {
        p1 = _p1;
        p2 = _p2;
        p3 = _p3;

        n1 = _n1;
        n2 = _n2;
        n3 = _n3;

        e1 = p2 - p1;
        e2 = p3 - p1;

        normal = e2.cross(e1).normalize();

    }

    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p, const Intersection& i) const override;

    Tuple n1, n2, n3;
private:

};