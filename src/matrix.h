#pragma once

#include <algorithm>
#include <ostream>
#include <iomanip>

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

    static Matrix identity()
    {
        Matrix m;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }

    friend std::ostream& operator<< (std::ostream& os, Matrix<rows, columns>& m)
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

    float* operator[](int index)
    {
        return (float*)&matrix[index];
    }


private:
    float matrix[rows][columns];

};