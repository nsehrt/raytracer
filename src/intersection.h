#pragma once

#include "Matrix.h"

class Shape;

struct IntersectionData
{
    Shape* object = nullptr;
    float time = 0.0f;
    bool inside = false;
    Tuple point;
    Tuple eyeV;
    Tuple normalV;
    Tuple reflectV;
    float n1 = 0.0f;
    float n2 = 0.0f;
    Tuple overPoint;
    Tuple underPoint;
};

class Intersection
{
public:
    /*constructors/destructor*/
    Intersection() = default;
    Intersection(float t, Shape* s)
    {
        time = t;
        object = s;
    }

    Intersection(float t, Shape* s, float _u, float _v)
    {
        time = t;
        object = s;
        u = _u;
        v = _v;
    }

    ~Intersection() = default;



    static Intersection hit(const std::vector<Intersection>& i)
    {

        for (auto& v : i)
        {
            if (v.time >= 0.0f)
            {
                return v;
            }
        }

        return { 0.0f, nullptr };
    }

    /*aggregation*/
    template<typename ...Args>
    static std::vector<Intersection> intersections(Args const&... args)
    {
        std::vector<Intersection> xs{ args... };
        std::sort(xs.begin(), xs.end());
        return xs;
    }

    static float schlick(const IntersectionData& comps)
    {
        float cos = comps.eyeV.dot(comps.normalV);

        if (comps.n1 > comps.n2)
        {
            float n = comps.n1 / comps.n2;
            float sin2t = (n * n) * (1.0f - (cos * cos));

            if (sin2t > 1.0f)
            {
                return 1.0f;
            }

            float cost = std::sqrt(1.0f - sin2t);
            cos = cost;

        }

        float r0 = ((comps.n1 - comps.n2) / (comps.n1 + comps.n2)) * ((comps.n1 - comps.n2) / (comps.n1 + comps.n2));


        return r0 + (1 - r0) * std::pow((1.0f - cos), 5.0f);
    }

    /*overloads*/
    friend std::ostream& operator<<(std::ostream& os, Intersection const& i)
    {
        os << "(" << i.time << " | " << std::hex << i.object << ")";
        return os;
    }

    bool operator<(Intersection const& i) const
    {
        return time < i.time;
    }

    bool operator==(Intersection const& i) const
    {
        return (time == i.time && object == i.object);
    }

    bool operator!=(Intersection const& i) const
    {
        return !operator==(i);
    }

    operator bool() const
    {
        return object == nullptr ? false : true;
    }

    /*member variables*/
    float time = 0.0f;
    float u = 0.0f;
    float v = 0.0f;
    Shape* object = nullptr;

private:

};