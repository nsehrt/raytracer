#pragma once

#include "matrix.h"
#include "ray.h"
#include "canvas.h"
#include "world.h"


class Camera
{

public:
    explicit Camera(int _hSize, int _vSize, float _fov)
    {
        hSize = _hSize;
        vSize = _vSize;
        fov = _fov;

        halfView = std::tan(fov / 2.0f);
        aspectRatio = (float)hSize / (float)vSize;

        if (aspectRatio >= 1)
        {
            halfWidth = halfView;
            halfHeight = halfView / aspectRatio;
        }
        else
        {
            halfWidth = halfView * aspectRatio;
            halfHeight = halfView;
        }

        pixelSize = (halfWidth * 2.0f) / hSize;

        transform = Matrix<4, 4>::identity();
    }

    ~Camera() = default;


    Ray rayForPixel(const int x, const int y) const
    {
        float xoffset = ((float)x + 0.5f) * pixelSize;
        float yoffset = ((float)y + 0.5f) * pixelSize;

        float worldX = halfWidth - xoffset;
        float worldY = halfHeight - yoffset;

        auto pixel = transform.inverse() * Tuple::Point(worldX, worldY, -1.0f);
        auto origin = transform.inverse() * Tuple::Point(0, 0, 0);

        return Ray(origin, (pixel - origin).normalize());
    }


    Canvas render(const World& w)
    {
        Canvas image = Canvas(hSize, vSize);

        for (int y = 0; y < vSize; y++)
        {
            for (int x = 0; x < hSize; x++)
            {
                Ray r = rayForPixel(x, y);
                Color out = w.colorAt(r);
                image.writePixel(x, y, out);
            }
        }

        return image;
    }

    float pixelSize;

    float aspectRatio;
    float halfView;

    float halfWidth, halfHeight;

    Matrix<4, 4> transform;

private:

    int hSize;
    int vSize;
    float fov;

};