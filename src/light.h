#pragma once

#include "matrix.h"
#include "color.h"
#include "material.h"

class PointLight
{
public:
    PointLight()
    {
        intensity = Color();
        position = Tuple::Point();
    }

    explicit PointLight(const Tuple& _position, const Color& _intensity)
    {
        intensity = _intensity;
        position = _position;
    }

    ~PointLight() = default;


    Color intensity;
    Tuple position;

private:



};

static Color lighting(const Material& mat, const PointLight& light, const Tuple& pos,  const Tuple& eyeVector, const Tuple& normalVector)
{
    Color ambient, diffuse, specular;

    const Color effectiveColor = mat.color * light.intensity;

    const Tuple lightV = (light.position - pos).normalize();
    ambient = effectiveColor * mat.ambient;

    float lightDotNormal = lightV.dot(normalVector);

    if (lightDotNormal < 0.0f)
    {
        diffuse = Color(0.0f, 0.0f, 0.0f);
        specular = Color(0.0f, 0.0f, 0.0f);
    }
    else
    {
        diffuse = effectiveColor * mat.diffuse * lightDotNormal;
        auto reflectV = (-lightV).reflect(normalVector);
        auto reflectDotEye = reflectV.dot(eyeVector);

        if (reflectDotEye <= 0.0f)
        {
            specular = Color(0.0f, 0.0f, 0.0f);
        }
        else
        {
            float factor = std::pow(reflectDotEye, mat.shininess);
            specular = light.intensity * mat.specular * factor;
        }

    }

    return ambient + diffuse + specular;
}