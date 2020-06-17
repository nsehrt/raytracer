#pragma once

#include <cmath>
#include <iostream>
#include <assert.h>

constexpr float EPSILON = 0.00001f;

class Tuple
{

public:

    /*constructors*/
    Tuple() : x(0.0f),y(0.0f),z(0.0f), w(0.0f) {}

    Tuple(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
    {    }

    /*create a point with values x, y, z, 1.0 */
    static Tuple Point(float _x, float _y, float _z)
    {
        return Tuple(_x, _y, _z, 1.0f);
    }

    /*create a vector with values x, y, z, 0.0f*/
    static Tuple Vector(float _x, float _y, float _z)
    {
        return Tuple(_x, _y, _z, 0.0f);
    }

    /*check if tuple is a point*/
    bool isPoint()
    {
        return (isEqualFloat(w, 1.0f));
    }

    /*check if tuple is a vector*/
    bool isVector()
    {
        return (isEqualFloat(w, 0.0f));
    }

    /*return magnitude of vector*/
    float magnitude()
    {
        return (std::sqrt(x * x + y * y + z * z + w * w));
    }

    /*return a normalized tuple*/
    Tuple normalize()
    {
        float mag = magnitude();
        return Tuple(x / mag, y / mag, z / mag, w / mag);
    }

    /*return dot product*/
    float dot(const Tuple& t)
    {
        return (x * t.x + y * t.y + z * t.z + w * t.w);
    }

    /*return the cross product as a vector*/
    Tuple cross(const Tuple & t)
    {
        return Tuple::Vector(y * t.z - z * t.y,
                             z * t.x - x * t.z,
                             x * t.y - y * t.x);
    }

    /*operator overloads*/

    bool operator== (const Tuple& a)
    {
        return (isEqualFloat(a.x, x) && isEqualFloat(a.y, y) && isEqualFloat(a.z, z) && isEqualFloat(a.w, w));
    }

    bool operator!= (const Tuple& a)
    {
        return !(operator==(a));
    }

    Tuple operator+ (const Tuple& a)
    {
        return Tuple(x + a.x, y + a.y, z + a.z, w + a.w);
    }

    Tuple operator- (const Tuple& a)
    {
        return Tuple(x - a.x, y - a.y, z - a.z, w - a.w);
    }

    Tuple operator- ()
    {
        return Tuple(-x, -y, -z, -w);
    }

    Tuple operator* (const float& scalar)
    {
        return Tuple(scalar * x, scalar * y, scalar * z, scalar * w);
    }

    friend Tuple operator* (const float& scalar, const Tuple& a)
    {
        return Tuple(scalar * a.x, scalar * a.y, scalar * a.z, scalar * a.w);
    }

    Tuple operator/ (const float& scalar)
    {
        return Tuple(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    float operator[](size_t index) const
    {
        assert(index < 4 && index > -1);
        return ((float*)(this))[index];
    }

    float& operator[](size_t index)
    {
        assert(index < 4 && index > -1);
        return ((float*)(this))[index];
    }

    friend std::ostream& operator<< (std::ostream& os, const Tuple& a)
    {
        os << "[" << a.x << ", " << a.y << ", " << a.z << ", " << a.w << "]";
        return os;
    }

    /*variables*/
    float x, y, z, w;

private:

    /*used to determine wheter floats are equal or close enough to equal*/
    bool isEqualFloat(const float& a, const float& b)
    {
        return (std::abs(a - b) < EPSILON);
    }

};