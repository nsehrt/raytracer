#include "ray.h"
#include "shape.h"

IntersectionData Ray::precompute(const Intersection& i, const std::vector<Intersection>& xs) const
{
        IntersectionData comps;
        std::vector<Shape*> containers;

        comps.time = i.time;
        comps.object = i.object;
        comps.point = position(comps.time);
        comps.eyeV = -direction;
        comps.normalV = comps.object->normalAt(comps.point);

        if (comps.normalV.dot(comps.eyeV) < 0.0f)
        {
            comps.inside = true;
            comps.normalV *= -1.0f;
        }

        comps.reflectV = direction.reflect(comps.normalV);

        comps.overPoint = comps.point + comps.normalV * EPSILON;
        comps.underPoint = comps.point - comps.normalV * EPSILON;

        for (const auto& x : xs)
        {
            bool isHit = x == i;

            if (isHit)
            {
                comps.n1 = containers.empty() ? 1.0f : containers.back()->material.refractiveIndex;
            }


            auto it = std::find(containers.begin(), containers.end(), x.object);
            if (it != containers.end())
            {
                containers.erase(it);
            }
            else
            {
                containers.push_back(x.object);
            }

            if (isHit)
            {
                comps.n2 = containers.empty() ? 1.f : containers.back()->material.refractiveIndex;
                break;
            }

        }

        return comps;
}
