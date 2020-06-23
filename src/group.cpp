#include "group.h"

void Group::addChild(std::shared_ptr<Shape> s)
{
    s->parent = this;
    children.push_back(std::move(s));
}

std::vector<Intersection> Group::localIntersect(const Ray& r)
{
    std::vector<Intersection> xs{};

    for (const auto& p : children)
    {
        auto in = p->intersect(r);

        for (const auto e : in)
        {
            xs.push_back(e);
        }

    }

    std::sort(xs.begin(), xs.end());

    return xs;
}

Tuple Group::localNormalAt(const Tuple& p, const Intersection& i) const
{
    std::cerr << "do not call this" << std::endl;
    return Tuple();
}
