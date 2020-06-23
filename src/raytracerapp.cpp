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

            auto xs = s->intersect(r);

            if (Intersection::hit(xs))
            {
                canvas.writePixel(x, y, red);
            }
        }
    }


    canvas.save("canvas.bmp");
}

void RayTracerApp::drawSphereLit()
{
    Canvas canvas(100, 100);

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

            auto xs = s->intersect(r);

            Intersection hit = Intersection::hit(xs);

            if (hit)
            {
                Tuple point = r.position(hit.time);
                Tuple normal = hit.object->normalAt(point, hit);
                Tuple eye = -r.direction;

                Color out = lighting(hit.object->material, s.get(), light, point, eye, normal, false);

                canvas.writePixel(x, y, out);
            }
        }
    }


    canvas.save("canvas.bmp");
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
    left->transform = Matrix<4, 4>::translation(-1.5f, 0.33f, -0.75f) * Matrix<4, 4>::scale(0.33f, 0.33f, 0.33f);
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
    canvas.save("canvas.bmp");
}

void RayTracerApp::drawPlanes()
{

    World w;
    Camera c(1920, 1080, PI / 3.0f);
    c.transform = Matrix<4, 4>::view(Tuple::Point(0, 2.5f, -5), Tuple::Point(0, 1, 0), Tuple::Vector(0, 1, 0));

    w.pointLights[0].position = Tuple::Point(-10, 10, -10);
    w.objects.clear();

    auto floor = std::make_shared<Plane>();

    auto patternf = std::make_shared<CheckerPattern>();
    patternf->a = Color(0.65f, 0.65f, 0.65f);
    patternf->b = Color(0.3f, 0.3f, 0.3f);
    floor->material.pattern = patternf.get();

    auto wall = std::make_shared<Plane>();
    wall->transform = Matrix<4, 4>::translation(0, 0, 15) * Matrix<4, 4>::rotateX(PI / 2.0f);
    wall->material.reflective = 1.0f;
    wall->material.specular = 0.0f;

    auto pattern = std::make_shared<CheckerPattern>();
    pattern->a = Color(0.65f, 0.65f, 0.65f);
    pattern->b = Color(0.3f, 0.3f, 0.3f);

    wall->material.pattern = pattern.get();

    auto middle = std::make_shared<Sphere>();
    middle->transform = Matrix<4, 4>::translation(-0.5f, 2, 0.5f);
    middle->material.color = Color(1, 1, 1);
    middle->material.diffuse = 0.3f;
    middle->material.specular = 0.15f;
    middle->material.transparency = 0.9f;
    middle->material.refractiveIndex = 1.5f;
    middle->material.reflective = 0.5f;


    auto smiddle = std::make_shared<Sphere>();
    smiddle->transform = Matrix<4, 4>::translation(-0.5f, 2.0f, 0.5f) * Matrix<4, 4>::scale(0.5f, 0.5f, 0.5f);
    smiddle->material.color = Color(1, 1, 1);
    smiddle->material.diffuse = 0.3f;
    smiddle->material.specular = 0.15f;
    smiddle->material.transparency = 1.0f;
    smiddle->material.refractiveIndex = 1.0002f;
    smiddle->material.reflective = 0.9f;

    auto right = std::make_shared<Cone>();
    right->minimum = -1;
    right->maximum = 0;
    right->closed = true;
    right->transform = Matrix<4, 4>::scale(1.0f, 2.5f, 1.0f) * Matrix<4, 4>::translation(1.0f, 1.0f, 3.5f);
    right->material.color = Color(0.5f, 1, 0.8f);
    right->material.diffuse = 0.3f;
    right->material.specular = 0.3f;
    right->material.reflective = 0.45f;
    right->material.transparency = 0.77f;
    right->material.refractiveIndex = 2.44f;
    //right->material.pattern = pattern.get();

    auto left = std::make_shared<Sphere>();
    left->transform = Matrix<4, 4>::translation(-1.5f, 0.33f, -0.75f) * Matrix<4, 4>::scale(0.33f, 0.33f, 0.33f);
    left->material.color = Color(1, 0.8f, 0.1f);
    left->material.diffuse = 0.7f;
    left->material.specular = 0.3f;


    w.objects.push_back(floor);
    w.objects.push_back(wall);
    w.objects.push_back(middle);
    w.objects.push_back(smiddle);
    w.objects.push_back(right);
    w.objects.push_back(left);

    auto canvas = c.render(w);
    canvas.save("canvas.bmp");




}

void RayTracerApp::drawRefraction()
{


    World w;
    Camera c(640, 480, PI / 3.0f);
    c.transform = Matrix<4, 4>::view(Tuple::Point(0, 1.5f, -5), Tuple::Point(0, 1, 0), Tuple::Vector(0, 1, 0));

    w.pointLights[0].position = Tuple::Point(-10, 10, -10);
    w.objects.clear();

    auto floor = std::make_shared<Plane>();

    auto wall = std::make_shared<Plane>();
    wall->transform = Matrix<4, 4>::translation(0, 0, 2) * Matrix<4, 4>::scale(40,40,0.01f);

    auto pattern = std::make_shared<CheckerPattern>();
    pattern->a = Color(0.65f, 0.65f, 0.65f);
    pattern->b = Color(0.3f, 0.3f, 0.3f);

    wall->material.pattern = pattern.get();

    auto middle = std::make_shared<Sphere>();

    middle->material.color = Color(1.0f,1.0f,1.0f);
    middle->material.ambient = 0.1f;
    middle->material.diffuse = 0.9f;
    middle->material.specular = 0.9f;
    middle->material.shininess = 200.0f;
    middle->material.transparency = 0.9f;
    middle->material.refractiveIndex = 1.5f;
    middle->material.reflective = 0.1f;

    w.objects.push_back(floor);
    w.objects.push_back(wall);
    w.objects.push_back(middle);


    auto canvas = c.render(w);
    canvas.save("canvas.bmp");

}

void RayTracerApp::drawGroup()
{
    World w;
    Camera c(1920, 1080, PI / 3.0f);
    c.transform = Matrix<4, 4>::view(Tuple::Point(0, 4.5f, -15), Tuple::Point(0, 1, 0), Tuple::Vector(0, 1, 0));

    w.pointLights[0].position = Tuple::Point(-10, 10, -10);
    w.objects.clear();

    auto gr = std::make_shared<Group>();
    auto gr2 = std::make_shared<Group>();

    auto floor = std::make_shared<Plane>();

    auto patternf = std::make_shared<CheckerPattern>();
    patternf->a = Color(0.65f, 0.65f, 0.65f);
    patternf->b = Color(0.3f, 0.3f, 0.3f);
    floor->material.pattern = patternf.get();
    floor->material.reflective = 0.6f;

    auto wall = std::make_shared<Plane>();
    wall->transform = Matrix<4, 4>::translation(0, 0, 15) * Matrix<4, 4>::rotateX(PI / 2.0f);

    auto pattern = std::make_shared<CheckerPattern>();
    pattern->a = Color(0.65f, 0.65f, 0.65f);
    pattern->b = Color(0.4f, 0.4f, 0.4f);
    wall->material.pattern = pattern.get();
    wall->material.color = Color::White();
    wall->material.diffuse = 0.6f;
    wall->material.specular = 0.4f;

    auto s = std::make_shared<Sphere>();
    s->material.color = Color(1.0f, 1,1);
    s->transform = Matrix<4, 4>::translation(0, 1, 0);
    s->material.transparency = 1.0f;
    s->material.refractiveIndex = 1.52f;
    s->material.diffuse = 0.2f;
    s->material.specular = 0.3f;

    auto s2 = std::make_shared<Sphere>();
    s2->material.color = Color(0.4f, 0.2f, 0.8f);
    s2->transform = Matrix<4, 4>::translation(4, 1, 0);

    auto s3 = std::make_shared<Sphere>();
    s3->material.color = Color(1.0f, 0.2f, 0.1f);
    s3->transform = Matrix<4, 4>::translation(-5, 1, 5);

    auto pat = std::make_shared<RingPattern>();
    pat->a = Color(1, 0.850f, 0.38f);
    pat->b = Color(0.639f, 1, 0.380f);
    pat->transform = Matrix<4, 4>::rotateY(-PI / 2.0f);

    auto s4 = std::make_shared<Triangle>(Tuple::Point(0,0,0), Tuple::Point(0.5f, 1, 0), Tuple::Point(1, 0, 0));
    s4->transform = Matrix<4, 4>::translation(-15, 1.25, 11) * Matrix<4,4>::rotateZ(PI/2.0f) * Matrix<4, 4>::scale(1, 2, 1);
    s4->material.color = Color(0.0f,0.64f, 0.2f);
    s4->material.pattern = pat.get();
    s4->material.reflective = 0.7f;

    //gr->addChild(floor.get());
    //gr->addChild(wall.get());
    ////gr->transform = Matrix<4, 4>::rotateY(PI / 2.0f);

    //gr2->addChild(s.get());
    //gr2->addChild(s2.get());
    //gr2->addChild(s3.get());
    //gr2->addChild(s4.get());

    //gr->addChild(gr2.get());

    w.objects.push_back(gr);


    auto canvas = c.render(w);
    canvas.save("canvas.bmp");
}

void RayTracerApp::drawTeaPot()
{
    World w;
    Camera c(1920, 1080, PI / 3.0f);
    c.transform = Matrix<4, 4>::view(Tuple::Point(0, 8.5f, -25), Tuple::Point(0, 1, 0), Tuple::Vector(0, 1, 0));

    w.pointLights[0].position = Tuple::Point(-10, 10, -10);
    w.objects.clear();

    auto floor = std::make_shared<Plane>();

    auto patternf = std::make_shared<CheckerPattern>();
    patternf->a = Color(0.65f, 0.65f, 0.65f);
    patternf->b = Color(0.3f, 0.3f, 0.3f);
    floor->material.pattern = patternf.get();
    floor->material.reflective = 0.6f;

    auto wall = std::make_shared<Plane>();
    wall->transform = Matrix<4, 4>::translation(0, 0, 15) * Matrix<4, 4>::rotateX(PI / 2.0f);

    auto pattern = std::make_shared<CheckerPattern>();
    pattern->a = Color(0.65f, 0.65f, 0.65f);
    pattern->b = Color(0.4f, 0.4f, 0.4f);
    wall->material.pattern = pattern.get();
    wall->material.color = Color::White();
    wall->material.diffuse = 0.6f;
    wall->material.specular = 0.4f;


    auto s = std::make_shared<Sphere>();
    s->material.color = Color(1.0f, 1, 1);
    s->transform = Matrix<4, 4>::translation(-2, 1, -7);
    s->material.transparency = 1.0f;
    s->material.refractiveIndex = 1.52f;
    s->material.diffuse = 0.2f;
    s->material.specular = 0.3f;

    auto s4 = std::make_shared<Sphere>();
    s4->material = s->material;
    s4->transform = Matrix<4, 4>::translation(-5.5f, 3, 1.5f);

    auto s2 = std::make_shared<Sphere>();
    s2->material.color = Color(0.4f, 0.2f, 0.8f);
    s2->transform = Matrix<4, 4>::translation(2, 1, -9);

    auto s3 = std::make_shared<Sphere>();
    s3->material.color = Color(1.0f, 0.2f, 0.1f);
    s3->transform = Matrix<4, 4>::translation(0, 1, -11);

    auto mirror = std::make_shared<Plane>();
    mirror->transform = Matrix<4, 4>::translation(7, 0, 0) * Matrix<4, 4>::rotateZ(PI / 8.0f) * Matrix<4, 4>::rotateY(PI / 2.0f) * Matrix<4, 4>::rotateX(PI / 2.0f);
    mirror->material.color = Color(1, 1, 1);
    mirror->material.reflective = 0.99f;
    mirror->material.diffuse = 0.2f;
    mirror->material.specular = 0.2f;
    mirror->material.ambient = 0.0f;

    //WaveFront load;
    //load.parseObjFile("teapot.obj");

    //load.defaultGroup->transform = Matrix<4, 4>::translation(-2, 0, 1) * Matrix<4,4>::rotateY(PI/5.0f) * Matrix<4, 4>::rotateX(-PI / 2.0f) * Matrix<4, 4>::scale(0.5f, 0.5f, 0.5f);
    //load.defaultGroup->material = Color(0.8f, 0.2f, 0.3f);

    auto cube1 = std::make_shared<Cube>();
    auto cube2 = std::make_shared<Cube>();
    auto cube3 = std::make_shared<Cube>();
    auto cube4 = std::make_shared<Cube>();
    auto cube5 = std::make_shared<Cube>();


    cube1->transform = Matrix<4, 4>::translation(-2.5f, 1.0f, 3.f);
    cube2->transform = Matrix<4, 4>::translation(0.25f, 1.0f, 3.f) * Matrix<4, 4>::rotateY(PI / 8.0f);
    cube3->transform = Matrix<4, 4>::translation(-2.f, 3.0f, 3.25f) * Matrix<4, 4>::rotateY(-PI / 16.0f);
    cube4->transform = Matrix<4, 4>::translation(-5.5f, 1.0f, 1.25f) * Matrix<4, 4>::rotateY(-PI / 16.0f);
    cube5->transform = Matrix<4, 4>::translation(-5.f, 1.0f, -3.25f) * Matrix<4, 4>::rotateY(-PI / 4.0f);

    cube1->material.color = Color(0.592f, 0.84f, 0.533f);
    cube2->material.color = Color(0.117f, 0.741f, 0.862f);
    cube3->material.color = Color(1.f, 0.764f, 0.180f);
    cube4->material.color = Color(0.749f, 0.168f, 0.592f);
    cube5->material.color = Color(0.211f, 0.850f, 0.756f);

    cube1->material.reflective = 0.1f;
    cube2->material.reflective = 0.1f;
    cube3->material.reflective = 0.1f;
    cube4->material.reflective = 0.2f;
    cube5->material.reflective = 0.2f;
    
    auto cyl = std::make_shared<Cylinder>();
    cyl->minimum = -1;
    cyl->maximum = 4;
    cyl->closed = true;

    cyl->material.reflective = 0.95f;
    cyl->material.diffuse = 0.2f;
    cyl->material.specular = 0.2f;

    cyl->transform = Matrix<4, 4>::translation(1.5f, 1, -1);

    auto cone1 = std::make_shared<Cone>();
    cone1->minimum = 0;
    cone1->maximum = 1;
    cone1->closed = true;

    auto pc = std::make_shared<GradientPattern>();
    pc->transform = Matrix<4, 4>::rotateY(PI / 2.0f);

    cone1->material.color = Color(0.752f, 0.858f, 0.121f);
    cone1->material.pattern = pc.get();
    cone1->transform = Matrix<4, 4>::translation(0.0f, 2, -3) * Matrix<4, 4>::rotateX(PI) * Matrix<4, 4>::scale(1, 2, 1);



    w.objects.push_back(floor);
    w.objects.push_back(wall);
    w.objects.push_back(s);
    w.objects.push_back(s2);
    w.objects.push_back(s3);
    w.objects.push_back(s4);
    w.objects.push_back(mirror);
    //w.objects.push_back(load.defaultGroup);

    w.objects.push_back(cube1);
    w.objects.push_back(cube2);
    w.objects.push_back(cube3);
    w.objects.push_back(cube4);
    w.objects.push_back(cube5);
    //w.objects.push_back(cone1);
    w.objects.push_back(cyl);

    auto canvas = c.render(w);
    canvas.save("canvas.bmp");
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
