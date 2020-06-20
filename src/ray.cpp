#include "ray.h"
#include "shape.h"

IntersectionData Ray::precompute(const Intersection& i) const
{
        IntersectionData comps;

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

        comps.overPoint = comps.point + comps.normalV * (EPSILON); /*shadow acne*/

        return comps;
}
