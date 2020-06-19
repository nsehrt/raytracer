#include "raytracerapp.h"

RayTracerApp::RayTracerApp()
{

}

void RayTracerApp::drawSphereSilhouette()
{
    Canvas canvas(100,100);

    Color red = Color(1.0f, 0.0f, 0.0f);
    Sphere s = Sphere();

    Tuple ray_origin = Tuple::Point(0, 0, -5);
    float wall_z = 10.0f;
    float wall_size = 7.0f;

    float pixel_size = wall_size / canvas.getWidth();
    float half = wall_size / 2.0f;

    float world_x, world_y;

    /*test transforms*/
    //s.setWorld(Matrix<4,4>::rotateZ(PI/ 4.0f)*  Matrix<4, 4>::scale(0.5f, 1.0f, 1.0f));
    //s.setWorld(Matrix<4, 4>::shear(1,0,0,0,0,0) * Matrix<4, 4>::scale(0.5f, 1.0f, 1.0f));

    for (int y = 0; y < (int)canvas.getHeight(); y++)
    {
        world_y = half - pixel_size * y;

        for (int x = 0; x < (int)canvas.getWidth(); x++)
        {
            world_x = -half + pixel_size * x;

            Tuple position = Tuple::Point(world_x, world_y, wall_z);

            Ray r = Ray(ray_origin, (position - ray_origin).normalize());

            auto xs = r.intersects(s);

            if (Intersection::hit(xs))
            {
                canvas.writePixel(x, y, red);
            }
        }
    }


    canvas.save("canvas.ppm");
}

void RayTracerApp::drawSphereLit()
{
    Canvas canvas(500, 500);

    Color red = Color(1.0f, 0.0f, 0.0f);
    Sphere s = Sphere();
    s.material.intensity = Color(1.0f, 0.2f, 0.4f);
    s.material.shininess = 20.0f;

    PointLight light(Tuple::Point(-10, 10, -10), Color(1, 0.5f, 1));

    Tuple ray_origin = Tuple::Point(0, 0, -5);
    float wall_z = 10.0f;
    float wall_size = 7.0f;

    float pixel_size = wall_size / canvas.getWidth();
    float half = wall_size / 2.0f;

    float world_x, world_y;

    /*test transforms*/
    //s.world = Matrix<4,4>::rotateZ(PI/ 4.0f)*  Matrix<4, 4>::scale(0.5f, 1.0f, 1.0f);
    //s.world = Matrix<4, 4>::shear(1,0,0,0,0,0) * Matrix<4, 4>::scale(0.5f, 1.0f, 1.0f);

    for (int y = 0; y < (int)canvas.getHeight(); y++)
    {
        world_y = half - pixel_size * y;

        for (int x = 0; x < (int)canvas.getWidth(); x++)
        {
            world_x = -half + pixel_size * x;

            Tuple position = Tuple::Point(world_x, world_y, wall_z);

            Ray r = Ray(ray_origin, (position - ray_origin).normalize());

            auto xs = r.intersects(s); 

            Intersection hit = Intersection::hit(xs);

            if (hit)
            {
                Tuple point = r.position(hit.time);
                Tuple normal = hit.object->normalAt(point);
                Tuple eye = -r.direction;

                Color out = lighting(hit.object->material, light, point, eye, normal);

                canvas.writePixel(x, y, out);
            }
        }
    }


    canvas.save("canvas.ppm");
}

/*clock test*/
    //Canvas canvas(100,100);
    //Tuple canvasCenter = Tuple::Point(50, 50, 50);

    //Tuple twelve = Tuple::Point(0, 0, 1);
    //float radius = (3.0f / 8.0f) * 100;

    //int iter = 12;

    //for (int i = 0; i < iter; i++)
    //{
    //    auto trf = Matrix<4, 4>::rotateY(i * (2 * PI/(float)iter));
    //    auto p = trf * twelve;
    //    p *= radius;

    //    p += canvasCenter;

    //    canvas.writePixel((int)p.x, (int)p.z, Color(1.0f, 0.0f, 0.0f));
    //}
    //canvas.save("canvas.ppm");
