#pragma once

#include "tuple.h"
#include "canvas.h"
#include "matrix.h"
#include "sphere.h"
#include "light.h"
#include "material.h"
#include "ray.h"
#include <iostream>

using UINT = unsigned int;

class RayTracerApp
{
public:
    explicit RayTracerApp();
    ~RayTracerApp() = default;

    void drawSphereSilhouette();
    void drawSphereLit();

private:

};