#include "canvas.h"
#include <fstream>

Canvas::Canvas(unsigned int w, unsigned int h)
{
    width = w;
    height = h;

    pixels = new Color[width * height];
}

Canvas::~Canvas()
{
    if (pixels)
    {
        delete[] pixels;
        pixels = nullptr;
    }
}

void Canvas::writePixel(int x, int y, const Color& col)
{
    if (x > (int)width || y > (int)height || x < 0 || y < 0)
    {
        return;
    }
    pixels[y * width + x] = col;
}

Color Canvas::getPixel(int x, int y) const
{
    if (x > (int)width || y > (int)height || x < 0 || y < 0) {
        return Color(0.0f, 0.0f, 0.0f);
    }

    return pixels[y * width + x];
}

void Canvas::save(const std::string& fileName)
{

    std::ofstream file(fileName);

    if (file.is_open())
    {
        file << "P3\n" << width << " " << height << "\n255\n";

        for (unsigned int i = 0; i < height; i++)
        {
            for (unsigned int j = 0; j < width; j++)
            {
                file << getPixel(j, i).toString() << "\n";
            }
        }

        file.close();
    }
    else
    {
        std::cerr << "Failed to save canvas!" << std::endl;
    }

}
