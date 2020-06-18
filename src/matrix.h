#pragma once

#include <algorithm>
#include <ostream>
#include <iomanip>
#include <vector>
#include "tuple.h"

template<uint16_t rows, uint16_t columns>
class Matrix
{
public:

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
                matrix[i][j] = data[i * columns + j];
            }
        }
    }

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

    Tuple operator* (const Tuple& t)
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