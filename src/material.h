#pragma once

#include "color.h"

class Material
{
public:
    Material() {
        intensity = Color(1.0f, 1.0f, 1.0f);
        ambient = 0.1f;
        diffuse = 0.9f;
        specular = 0.9f;
        shininess = 200.0f;
    };

    Material(const Color& _intensity)
    {
        intensity = _intensity;
        ambient = 0.1f;
        diffuse = 0.9f;
        specular = 0.9f;
        shininess = 200.0f;
    };

    Material(const Color& _intensity, float a, float d, float s, float sh) :
        intensity(_intensity), ambient(a), diffuse(d), specular(s), shininess(sh){ }

    ~Material() = default;

    /*overloads*/
    friend std::ostream& operator<<(std::ostream& os, Material const& i)
    {
        os << "(" << i.intensity.r() << ", " << i.intensity.g() << ", " << i.intensity.b() << " | " <<
            i.ambient << ", " << i.diffuse << ", " << i.specular << ", " << i.shininess;
        return os;
    }

    bool operator==(Material const& i) const
    {
        return (intensity == i.intensity && ambient == i.ambient && diffuse == i.diffuse && specular == i.specular && shininess == i.shininess);
    }

    bool operator!=(Material const& i) const
    {
        return !operator==(i);
    }

    Color intensity;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

private:


};