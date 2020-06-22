#pragma once

#include "shape.h"


class Group : public Shape
{

public:

    Group() : Shape(){
        transform = Matrix<4, 4>::identity();
    }

    bool isEmpty()
    {
        return children.empty();
    }

    void addChild(Shape* s);

    std::vector<Intersection> localIntersect(const Ray& r) override;
    Tuple localNormalAt(const Tuple& p) const override;

    
private:
    std::vector<Shape*> children;

};