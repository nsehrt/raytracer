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


    Ray rayForPixel(const int x, const int y) const;


    Canvas render(World& w);
    Canvas renderSingle(World& w);

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

static int divRoundClosest(const int n, const int d)
{
    return ((n < 0) ^ (d < 0)) ? ((n - d / 2) / d) : ((n + d / 2) / d);
}