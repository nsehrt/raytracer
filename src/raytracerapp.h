#pragma once

#include "camera.h"
#include "canvas.h"
#include "intersection.h"
#include "light.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "pattern.h"

#include <iostream>

using UINT = unsigned int;

class RayTracerApp
{
public:
    explicit RayTracerApp();
    ~RayTracerApp() = default;

    void drawSphereSilhouette();
    void drawSphereLit();
    void drawFirstScene();
    void drawPlanes();

private:

};