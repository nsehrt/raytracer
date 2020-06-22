#pragma once

#include "shape.h"

class Sphere : public Shape
{
public:
    Sphere() : Shape() {
    }
    Sphere(const Material& m) : Shape(m){}

    /*calculate the intersection(s) between this ray and a sphere*/
    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p) const override;

    static Sphere getGlassSphere();
private:

};