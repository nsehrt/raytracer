#include "raytracerapp.h"

RayTracerApp::RayTracerApp()
{
    //Canvas canvas(900, 550);

    //Tuple start = Tuple::Point(0, 1, 0);
    //Tuple velocity = Tuple::Vector(1, 1.8, 0).normalize() * 11.25;

    //Tuple gravity = Tuple::Vector(0.0f, -0.1f, 0.0f);
    //Tuple wind = Tuple::Vector(-0.01f, 0.0f, 0.0f);

    //Tuple projPosition = start;

    //for (int i = 0; i < 1000; i++)
    //{
    //    projPosition = projPosition + velocity;
    //    velocity = velocity + gravity + wind;

    //    canvas.writePixel((int)projPosition.x, canvas.getHeight() - (int)projPosition.y, Color(1.0f, 0.0f, 0.0f));
    //}

    //canvas.save("cannon.ppm");

    Matrix<4, 4> m;

    m[1][2] = 1.5f;

    m = Matrix<4, 4>::identity();

    std::cout << m;

}
