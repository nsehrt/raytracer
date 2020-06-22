#include "pattern.h"
#include "shape.h"

Color Pattern::patternAtShape(const Shape* shape, const Tuple& point) const
{
    auto objPoint = shape->worldToObject(point);
    auto pattPoint = transform.inverse() * objPoint;

    return patternAt(pattPoint);
}
