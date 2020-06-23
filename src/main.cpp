#include <iostream>
#include "raytracerapp.h"
#include <chrono>

int main()
{
    RayTracerApp rayTracerApp;

    auto start = std::chrono::system_clock::now();

    //rayTracerApp.drawSphereSilhouette();
    //rayTracerApp.drawSphereLit();
    //rayTracerApp.drawFirstScene();
    //rayTracerApp.drawPlanes();
    //rayTracerApp.drawRefraction();
    //rayTracerApp.drawCover();
    rayTracerApp.drawTeaPot();

    auto end = std::chrono::system_clock::now();

    std::cout << "Finished in " << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count() << " ms." << std::endl;


}