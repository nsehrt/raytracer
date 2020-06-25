#pragma once

#include "matrix.h"
#include "color.h"
#include "material.h"


class Sequ
{

public:
    explicit Sequ() = default;
    explicit Sequ(std::vector<float>& values)
    {
        v = values;
        pos = 0;
    }

    float next()
    {
        if (v.empty()) return 0.5f;

        return v[pos++ % v.size()];
    }

private:
    std::vector<float> v;
    int pos = 0;

};



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


class AreaLight
{
public:

    explicit AreaLight()
    {
        corner = Tuple();
        uvec = Tuple();
        usteps = 0;
        vvec = Tuple();
        vsteps = 0;
        samples = 0;
        position = Tuple();
        position.w = 1.0f;

        intensity = Color();
    }

    explicit AreaLight(const Tuple& _corner, const Tuple& _fullUvec, const int _usteps,
                       const Tuple& _fullVvec, const int _vsteps, const Color& _intensity, bool jitterEnabled = true)
    {
        corner = _corner;
        uvec = _fullUvec / (float)_usteps;
        usteps = _usteps;
        vvec = _fullVvec / (float)_vsteps;
        vsteps = _vsteps;
        samples = usteps * vsteps;
        position = (_fullUvec + _fullVvec) / 2;
        position.w = 1.0f;

        intensity = _intensity;

        std::vector<float> v(1024);

        for (int i = 0; i < (int)v.size(); i++)
        {
            v[i] = rand() / (float) RAND_MAX;
        }

        if(jitterEnabled)
        jitter = Sequ(v);
    }

    ~AreaLight() = default;


    Tuple pointOnLight(const int u, const int v)
    {
        return corner + 
            uvec * (u + jitter.next()) + 
            vvec * (v + jitter.next());
    }

    void jitterBy(Sequ s)
    {
        jitter = s;
    }

    Tuple corner;
    Tuple uvec;
    Tuple vvec;
    int usteps;
    int vsteps;
    int samples;
    Tuple position;

    Color intensity;

    Sequ jitter;


private:



};



static Color lighting(const Material& mat, const Shape* object, AreaLight& light, const Tuple& pos,  const Tuple& eyeVector, const Tuple& normalVector, float shadowIntensity)
{
    Color ambient, diffuse, specular;
    Color col;

    if (mat.pattern != nullptr)
    {
        col = mat.pattern->patternAtShape(object, pos);
    }
    else
    {
        col = mat.color;
    }

    const Color effectiveColor = col * light.intensity;
    Color sum = Color::Black();

    for (int v = 0; v < light.vsteps; v++)
    {
        for (int u = 0; u < light.usteps; u++)
        {

            const Tuple lightV = (light.pointOnLight(u,v) - pos).normalize();
            ambient = effectiveColor * mat.ambient;

            if (shadowIntensity < EPSILON) return ambient;

            float lightDotNormal = lightV.dot(normalVector);

            if (lightDotNormal < 0.0f)
            {
                diffuse = Color(0.0f, 0.0f, 0.0f);
                specular = Color(0.0f, 0.0f, 0.0f);
            }
            else
            {
                diffuse = effectiveColor * mat.diffuse * lightDotNormal * shadowIntensity;
                auto reflectV = (-lightV).reflect(normalVector);
                auto reflectDotEye = reflectV.dot(eyeVector);

                if (reflectDotEye <= 0.0f)
                {
                    specular = Color(0.0f, 0.0f, 0.0f);
                }
                else
                {
                    float factor = std::pow(reflectDotEye, mat.shininess);
                    specular = light.intensity * mat.specular * factor * shadowIntensity;
                }

            }

            sum += diffuse;
            sum += specular;

        }
    }

    return ambient + (sum / (float)light.samples) * shadowIntensity;
}

//
//    const Tuple lightV = (light.position - pos).normalize();
//    ambient = effectiveColor * mat.ambient;
//
//    if (shadowIntensity < EPSILON) return ambient;
//
//    float lightDotNormal = lightV.dot(normalVector);
//
//    if (lightDotNormal < 0.0f)
//    {
//        diffuse = Color(0.0f, 0.0f, 0.0f);
//        specular = Color(0.0f, 0.0f, 0.0f);
//    }
//    else
//    {
//
//        for (int v = 0; v < light.vsteps; v++)
//        {
//            for (int u = 0; u < light.usteps; u++)
//            {
//                diffuse = effectiveColor * mat.diffuse * lightDotNormal * shadowIntensity;
//                auto reflectV = (-lightV).reflect(normalVector);
//                auto reflectDotEye = reflectV.dot(eyeVector);
//
//                if (reflectDotEye <= 0.0f)
//                {
//                    specular = Color(0.0f, 0.0f, 0.0f);
//                }
//                else
//                {
//                    float factor = std::pow(reflectDotEye, mat.shininess);
//                    specular = light.intensity * mat.specular * factor * shadowIntensity;
//                }
//
//                sum += diffuse;
//                sum += specular;
//            }
//        }
//
//
//
//    }
//
//    return ambient + diffuse + specular;
//    //return ambient + (sum / (float)light.samples) * shadowIntensity;
//}