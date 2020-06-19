#pragma once

#include <algorithm>
#include <ostream>
#include <iomanip>
#include <vector>
#include "tuple.h"

const float PI = 3.14159265358979323846f;

template<uint16_t rows, uint16_t columns>
class Matrix
{
public:

    /*constructors*/

    Matrix() {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = 0.0f;
            }
        }
    }

    Matrix(std::vector<float>& data)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = data[(long long)i * columns + j];
            }
        }
    }

    Matrix(std::initializer_list<std::initializer_list<float>> data)
    {
       
        int i = 0;

        for (auto y : data)
        {
            int c = 0;
            for (float value : y)
            {
                matrix[i][c++] = value;
            }
            i++;
        }
    }

    /*basic utility*/

    static Matrix identity()
    {
        Matrix m;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                m[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }

        return m;
    }

    Matrix transpose() const
    {
        Matrix res;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                res[i][j] = matrix[j][i];
            }
        }
        return res;
    }
    
    Matrix inverse() const
    {
        Matrix<rows, columns> inverse;

        float det = determinant();

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                inverse[j][i] = cofactor(i, j) / det;
            }
        }

        return inverse;
    }

    bool isInvertible() const
    {
        return (bool)determinant();
    }

    float determinant() const;

    float minor(uint16_t r, uint16_t c) const
    {
        return this->submatrix(r, c).determinant();
    }

    float cofactor(uint16_t r, uint16_t c) const
    {
        return minor(r, c) * ((r + c) % 2 == 0 ? 1.0f : -1.0f);
    }

    Matrix<rows - 1, columns - 1> submatrix(uint16_t r, uint16_t c) const
    {
        Matrix<rows - 1, columns - 1> sub;

        int indexR = 0;
        int indexC = 0;

        for (uint16_t i = 0; i < rows; i++)
        {
            if (i == r) continue;

            for (uint16_t j = 0, indexC = 0; j < columns; j++)
            {
                if (j == c) continue;

                sub[indexR][indexC] = matrix[i][j];
                indexC++;
            }

            indexR++;
        }

        return sub;
    }

    /* transformations */
    static Matrix<4, 4> translation(float _x, float _y, float _z)
    {
        Matrix<4,4> m = Matrix<4, 4>::identity();

        m[0][3] = _x;
        m[1][3] = _y;
        m[2][3] = _z;

        return m;
    }

    static Matrix<4, 4> scale(float _x, float _y, float _z)
    {
        Matrix<4, 4> m = Matrix<4,4>::identity();

        m[0][0] = _x;
        m[1][1] = _y;
        m[2][2] = _z;

        return m;
    }

    static Matrix<4, 4> rotateX(float radians)
    {
        Matrix<4, 4> m = Matrix<4, 4>::identity();

        m[1][1] = std::cos(radians);
        m[1][2] = -std::sin(radians);
        m[2][1] = std::sin(radians);
        m[2][2] = std::cos(radians);
        
        return m;
    }


    static Matrix<4, 4> rotateY(float radians)
    {
        Matrix<4, 4> m = Matrix<4, 4>::identity();

        m[0][0] = std::cos(radians);
        m[0][2] = std::sin(radians);
        m[2][0] = -std::sin(radians);
        m[2][2] = std::cos(radians);

        return m;
    }

    static Matrix<4, 4> rotateZ(float radians)
    {
        Matrix<4, 4> m = Matrix<4, 4>::identity();

        m[0][0] = std::cos(radians);
        m[0][1] = -std::sin(radians);
        m[1][0] = std::sin(radians);
        m[1][1] = std::cos(radians);

        return m;
    }

    static Matrix<4, 4> shear(float _xy, float _xz, float _yx, float _yz, float _zx, float _zy)
    {
        Matrix<4, 4> m = Matrix<4, 4>::identity();

        m[0][1] = _xy;
        m[0][2] = _xz;
        m[1][0] = _yx;
        m[1][2] = _yz;
        m[2][0] = _zx;
        m[2][1] = _zy;

        return m;
    }

    /*operator overloads*/
    friend std::ostream& operator<< (std::ostream& os, const Matrix<rows, columns>& m)
    {
        for (int i = 0; i < rows; i++)
        {
            os << "| ";
            for (int j = 0; j < columns; j++)
            {
                os << std::fixed << std::setprecision(2) << m[i][j] << " ";
            }
            os << "|\n";
        }

        return os;
    }


    Matrix<rows, columns> operator* (const Matrix<rows, columns>& m) const
    {
        Matrix<rows, columns> result;
        
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                result[i][j] = matrix[i][0] * m[0][j] +
                    matrix[i][1] * m[1][j] +
                    matrix[i][2] * m[2][j] +
                    matrix[i][3] * m[3][j];
            }
        }

        return result;
    }

    Tuple operator* (const Tuple& t) const
    {
        return Tuple(matrix[0][0] * t.x + matrix[0][1] * t.y + matrix[0][2] * t.z + matrix[0][3] * t.w,
                     matrix[1][0] * t.x + matrix[1][1] * t.y + matrix[1][2] * t.z + matrix[1][3] * t.w,
                     matrix[2][0] * t.x + matrix[2][1] * t.y + matrix[2][2] * t.z + matrix[2][3] * t.w,
                     matrix[3][0] * t.x + matrix[3][1] * t.y + matrix[3][2] * t.z + matrix[3][3] * t.w);
    }

    float* operator[](int index) const
    {
        return (float*)&matrix[index];
    }

    bool operator== (const Matrix<rows, columns>& m) const
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (!isEqualFloat(this->matrix[i][j], m[i][j])) return false;
            }
        }

        return true;
    }

    bool operator!= (const Matrix<rows, columns>& m) const
    {
        return !operator==(m);
    }


private:
    float matrix[rows][columns] = {};


    /*used to determine wheter floats are equal or close enough to equal*/
    bool isEqualFloat(const float& a, const float& b) const
    {
        return (std::abs(a - b) < 0.00001f);
    }
};


template<>
inline float Matrix<2, 2>::determinant() const
{
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

template<uint16_t rows, uint16_t columns>
float Matrix<rows, columns>::determinant() const
{
    float det = 0.0f;

    for (int i = 0; i < rows; i++)
    {
        det += matrix[0][i] * cofactor(0, i);
    }

    return det;
}