#pragma once

#include "color.h"
#include "pattern.h"

class Material
{
public:
    Material() {
        color = Color(1.0f, 1.0f, 1.0f);
        ambient = 0.1f;
        diffuse = 0.9f;
        specular = 0.9f;
        shininess = 200.0f;
        reflective = 0.0f;
        refractiveIndex = 1.0f;
        transparency = 0.0f;
        pattern = nullptr;
    };

    Material(const Color& _intensity)
    {
        color = _intensity;
        ambient = 0.1f;
        diffuse = 0.9f;
        specular = 0.9f;
        shininess = 200.0f;
        reflective = 0.0f;
        refractiveIndex = 1.0f;
        transparency = 0.0f;
        pattern = nullptr;
    };

    Material(const Color& _intensity, float a, float d, float s, float sh, float r) :
        color(_intensity), ambient(a), diffuse(d), specular(s), shininess(sh), reflective(r){ 

        refractiveIndex = 1.0f;
        transparency = 0.0f;
        pattern = nullptr;
    }

    ~Material() = default;

    /*overloads*/
    friend std::ostream& operator<<(std::ostream& os, Material const& i)
    {
        os << "(" << i.color.r() << ", " << i.color.g() << ", " << i.color.b() << " | " <<
            i.ambient << ", " << i.diffuse << ", " << i.specular << ", " << i.shininess;
        return os;
    }

    bool operator==(Material const& i) const
    {
        return (color == i.color && ambient == i.ambient && diffuse == i.diffuse && specular == i.specular && shininess == i.shininess);
    }

    bool operator!=(Material const& i) const
    {
        return !operator==(i);
    }

    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    float reflective;
    float transparency;
    float refractiveIndex;


    Pattern* pattern;

private:


};