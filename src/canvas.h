#pragma once

#include "color.h"

class Canvas
{
public:
    explicit Canvas(unsigned int w, unsigned int h);
    ~Canvas();

    unsigned int getWidth() const
    {
        return width;
    }

    unsigned int getHeight() const
    {
        return height;
    }

    /*set pixel x, y to color col*/
    void writePixel(int x, int y, const Color& col);

    /*get the color of the pixel x, y*/
    Color getPixel(int x, int y) const;

    /*save canvas to file*/
    void save(const std::string& fileName);

private:
    unsigned int width, height;
    Color* pixels;
};