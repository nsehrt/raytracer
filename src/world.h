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
        objects.push_back(std::make_shared<Sphere>(Material(Color(0.8f, 1, 0.6f), 0.1f, 0.7f, 0.2f, 200.f)));
        
        auto s2 = std::make_shared<Sphere>();
        s2->transform = Matrix<4, 4>::scale(0.5f, 0.5f, 0.5f);

        objects.push_back(std::move(s2));
    };



    std::vector<Intersection> intersects(const Ray& r) const
    {
        std::vector<Intersection> result;

        for (auto o : objects)
            for (const auto i : r.intersects(o))
                result.push_back(i);

        std::sort(result.begin(), result.end());
        return result;
    }



    Color shadeHit(const IntersectionData& i)const
    {
        return lighting(i.object->material, pointLights[0], i.point, i.eyeV, i.normalV);
    }



    Color colorAt(const Ray& r) const
    {
        auto hit = Intersection::hit(intersects(r));

        if (!hit)
        {
            return Color(0, 0, 0);
        }
        else
        {
            return shadeHit(r.precompute(hit));
        }
    }


    std::vector<PointLight> pointLights;
    std::vector<std::shared_ptr<Shape>> objects;

private:


};