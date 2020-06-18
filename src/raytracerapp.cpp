#include "raytracerapp.h"

RayTracerApp::RayTracerApp()
{
    Canvas canvas(100, 100);

    Tuple canvasCenter = Tuple::Point(50, 50, 50);

    Tuple twelve = Tuple::Point(0, 0, 1);
    float radius = (3.0f / 8.0f) * 100;

    int iter = 12;

    for (int i = 0; i < iter; i++)
    {
        auto trf = Matrix<4, 4>::rotateY(i * (2 * PI/(float)iter));
        auto p = trf * twelve;
        p *= radius;

        p += canvasCenter;

        canvas.writePixel((int)p.x, (int)p.z, Color(1.0f, 0.0f, 0.0f));
    }


    canvas.save("canvas.ppm");
}
