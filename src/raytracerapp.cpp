#include "raytracerapp.h"

RayTracerApp::RayTracerApp()
{

}

void RayTracerApp::drawSphereSilhouette()
{
    Canvas canvas(100,100);

    Color red = Color(1.0f, 0.0f, 0.0f);
    std::shared_ptr<Sphere> s = std::make_shared<Sphere>();

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
    Canvas canvas(150, 150);

    Color red = Color(1.0f, 0.0f, 0.0f);
    std::shared_ptr<Sphere> s = std::make_shared<Sphere>();
    s->material.color = Color(1.0f, 0.2f, 0.4f);
    s->material.shininess = 20.0f;

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

void RayTracerApp::drawFirstScene()
{

    World w;
    Camera c(480, 320, PI / 3.0f);
    c.transform = Matrix<4, 4>::view(Tuple::Point(0, 1.5f, -5), Tuple::Point(0, 1, 0), Tuple::Vector(0, 1, 0));

    w.pointLights[0].position = Tuple::Point(-10, 10, -10);
    w.objects.clear();

    auto floor = std::make_shared<Sphere>();
    floor->transform = Matrix<4, 4>::scale(10, 0.01f, 10);
    floor->material.color = Color(1, 0.9f, 0.9f);
    floor->material.specular = 0.0f;

    auto lwall = std::make_shared<Sphere>();
    lwall->transform = Matrix<4, 4>::translation(0, 0, 5) * Matrix<4, 4>::rotateY(-PI/4.0f) * Matrix<4, 4>::rotateX(PI / 2.0f) * Matrix<4, 4>::scale(10, 0.01f, 10);
    lwall->material = floor->material;

    auto rwall = std::make_shared<Sphere>();
    rwall->transform = Matrix<4, 4>::translation(0, 0, 5) * Matrix<4, 4>::rotateY(PI / 4.0f) * Matrix<4, 4>::rotateX(PI / 2.0f) * Matrix<4, 4>::scale(10, 0.01f, 10);
    rwall->material = floor->material;

    auto middle = std::make_shared<Sphere>();
    middle->transform = Matrix<4, 4>::translation(-0.5f, 1, 0.5f);
    middle->material.color = Color(0.1f, 1, 0.5f);
    middle->material.diffuse = 0.7f;
    middle->material.specular = 0.3f;

    auto right = std::make_shared<Sphere>();
    right->transform = Matrix<4, 4>::translation(1.5f, 0.5, -0.5f) * Matrix<4,4>::scale(0.5f,0.5f,0.5f);
    right->material.color = Color(0.5f, 1, 0.1f);
    right->material.diffuse = 0.7f;
    right->material.specular = 0.3f;

    auto left = std::make_shared<Sphere>();
    left->transform = Matrix<4, 4>::translation(-1.5f, 0.33, -0.75f) * Matrix<4, 4>::scale(0.33f, 0.33f, 0.33f);
    left->material.color = Color(1, 0.8f, 0.1f);
    left->material.diffuse = 0.7f;
    left->material.specular = 0.3f;

    w.objects.push_back(floor);
    w.objects.push_back(lwall);
    w.objects.push_back(rwall);
    w.objects.push_back(middle);
    w.objects.push_back(right);
    w.objects.push_back(left);


    auto canvas = c.render(w);
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
