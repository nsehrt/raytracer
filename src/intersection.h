#pragma once

#include "Matrix.h"
#include "Tuple.h"

class Shape;

struct IntersectionData
{
    Shape* object = nullptr;
    float time = 0.0f;
    bool inside = false;
    Tuple point;
    Tuple eyeV;
    Tuple normalV;
    Tuple overPoint;
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
    Shape* object = nullptr;

private:

};