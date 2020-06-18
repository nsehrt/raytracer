#include "raytracerapp.h"

RayTracerApp::RayTracerApp()
{
    Canvas canvas(100, 100);

    Tuple canvasCenter = Tuple::Point(50, 50, 50);

    Tuple center = Tuple::Point(1, 0, 0);

    for (int i = 0; i < 12; i++)
    {
        auto trf = Matrix<4, 4>::rotateY(2 * PI / i);
        auto p = trf * center;

        canvas.writePixel((int)p.x, (int)p.y, Color(1.0f, 0.0f, 0.0f));
    }


    canvas.save("canvas.ppm");
}
