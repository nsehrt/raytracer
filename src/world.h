#pragma once

#include "sphere.h"
#include "light.h"
#include "ray.h"
#include <vector>

class World
{
public:
    explicit World()
    {
        pointLights.push_back(PointLight(Tuple::Point(-10, 10, -10), Color(1, 1, 1)));
        objects.push_back(Sphere(Material(Color(0.8f, 1, 0.6f), 0.1f, 0.7f, 0.2f, 200.f)));
        
        Sphere s2 = Sphere();
        s2.world = Matrix<4, 4>::scale(0.5f, 0.5f, 0.5f);

        objects.push_back(s2);
    };

    std::vector<Intersection> intersects(Ray& r) const
    {
        std::vector<Intersection> result;

        for (auto o : objects)
            for (auto i : r.intersects(o))
                result.push_back(i);

        std::sort(result.begin(), result.end());
        return result;
    }


    std::vector<PointLight> pointLights;
    std::vector<Shape> objects;

private:


};