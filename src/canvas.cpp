#include "canvas.h"
#include "bitmap_image.hpp"
#include <fstream>

Canvas::Canvas(unsigned int w, unsigned int h)
{
    width = w;
    height = h;

    pixels.resize((long long)width * height);
}

Canvas::~Canvas()
{
}

void Canvas::writePixel(int x, int y, const Color col)
{
    if (x > (int)width || y > (int)height || x < 0 || y < 0)
    {
        return;
    }
    long long index = (long long)x + (long long)width * (long long)y;
    pixels[index] = col;
}

Color Canvas::getPixel(int x, int y) const
{
    if (x > (int)width || y > (int)height || x < 0 || y < 0) {
        return Color(0.0f, 0.0f, 0.0f);
    }
    long long index = (long long)x + (long long)width * (long long)y;
    return pixels[index];
}

void Canvas::save(const std::string& fileName)
{
    bitmap_image file(width, height);

    if (!file)
        return;

    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            auto c = getPixel(j, i);
            unsigned char r = std::clamp((int)(c.r() / 1.0f * 255), 0, 255);
            unsigned char g = std::clamp((int)(c.g() / 1.0f * 255), 0, 255);
            unsigned char b = std::clamp((int)(c.b() / 1.0f * 255), 0, 255);
            file.set_pixel(j,i, r,g,b);
        }
    }

    file.save_image(fileName);

}
