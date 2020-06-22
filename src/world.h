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
        objects.push_back(std::make_shared<Sphere>(Material(Color(0.8f, 1, 0.6f), 0.1f, 0.7f, 0.2f, 200.f, 0.0f)));
        
        auto s2 = std::make_shared<Sphere>();
        s2->transform = Matrix<4, 4>::scale(0.5f, 0.5f, 0.5f);

        objects.push_back(std::move(s2));
    };



    std::vector<Intersection> intersects(const Ray& r) const
    {
        std::vector<Intersection> result;

        for (auto o : objects)
            for (const auto i : o->intersect(r))
                result.push_back(i);

        std::sort(result.begin(), result.end());
        return result;
    }



    Color shadeHit(const IntersectionData& i, int remaining = 5)const
    {
        bool shadowed = isShadowed(i.overPoint);

        auto surface = lighting(i.object->material, i.object, pointLights[0], i.overPoint, i.eyeV, i.normalV, shadowed);

        auto reflected = reflectedColor(i, remaining);
        auto refracted = refractedColor(i, remaining);

        auto mat = i.object->material;

        if (mat.reflective > 0.0f && mat.transparency > 0.0f)
        {
            float reflectance = Intersection::schlick(i);

            return surface + reflected * reflectance + refracted * (1.0f - reflectance);
        }
        else
        {
            return surface + reflected + refracted;
        }
        
    }


    bool isShadowed(const Tuple& point) const
    {
        auto v = pointLights[0].position - point;
        auto distance = v.magnitude();
        auto direction = v.normalize();

        auto intersections = intersects(Ray(point, direction));

        auto hit = Intersection::hit(intersections);

        return  (hit && hit.time < distance);
    }

    Color colorAt(const Ray& r, int remaining = 5) const
    {

        auto xs = intersects(r);
        auto hit = Intersection::hit(xs);

        if (!hit)
        {
            return Color(0, 0, 0);
        }
        else
        {
            return shadeHit(r.precompute(hit, xs), remaining);
        }
    }


    Color reflectedColor(const IntersectionData& comps, int remaining = 5) const
    {
        if (comps.object->material.reflective == 0.0f || remaining < 1)
        {
            return Color(0, 0, 0);
        }

        auto reflectRay = Ray(comps.overPoint, comps.reflectV);
        auto color = colorAt(reflectRay, remaining - 1);

        return color * comps.object->material.reflective;
    }


    Color refractedColor(const IntersectionData& comps, int remaining = 5) const
    {
        if (comps.object->material.transparency == 0.0f || remaining < 1)
        {
            return Color(0, 0, 0);
        }


        float nRatio = comps.n1 / comps.n2;
        float cosI = comps.eyeV.dot(comps.normalV);
        float sin2t = (nRatio * nRatio) * (1.0f - (cosI * cosI));

        if (sin2t > 1.0f)
        {
            return Color(0, 0, 0);
        }

        float cosT = std::sqrt(1.0f - sin2t);
        auto direction = (comps.normalV * ((nRatio * cosI) - cosT)) - (comps.eyeV * nRatio);
        auto refractRay = Ray(comps.underPoint, direction);

        return colorAt(refractRay, remaining - 1) * comps.object->material.transparency;
    }

    

    std::vector<PointLight> pointLights;
    std::vector<std::shared_ptr<Shape>> objects;

private:


};