//
// Created by jakub on 22.12.2020.
//

#ifndef CLION_MATRIX_H
#define CLION_MATRIX_H

#include<iostream>
#include <fstream>
#include <type_traits>
#include "MatrixException.h"
#include "../print.h"

template<typename T>
class Matrix
{
//private:
public:
    T **array;
    int width;
    int height;
    Matrix(T **array, int width, int height) : array(array), width(width), height(height)
    {
        static_assert(std::is_arithmetic_v<T>, "Wrong type given. Matrix can't be created");
    }

    Matrix(int width, int height) : width(width), height(height)
    {
        static_assert(std::is_arithmetic_v<T>, "Wrong type given. Matrix can't be created");
        array = newArray(width, height);
    }

    /// User has to use correct type
    /// In case of wrong dimensions, matrix will be filled with zeros
    Matrix(const std::string &filePath, int width, int height) : width(width), height(height)
    {
        std::ifstream file(filePath);
        if (!file.is_open()) throw std::exception("File not found");
        array = newArray(width, height);
        for (int i = 0; i < height; i++) for (int j = 0; j < width; j++) file >> array[i][j];
        file.close();
    }

    Matrix(const Matrix &other)
    {
        width = other.width;
        height = other.height;
        array = newArray(width, height);
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                array[i][j] = other.array[i][j];
    }

    Matrix(Matrix &&other)
 noexcept     {
        width = other.width;
        height = other.height;
        array = other.array;
        for (int i = 0; i < height; i++)
        {
            other.array[i] = nullptr;
        }
        other.array = nullptr;
    }

    ~Matrix()
    {
        for (int i = 0; i < height; i++)
        {
            delete[] array[i];
        }
        delete array;
    }

    Matrix transpose()
    {
        T **result = new T *[width];
        for (int i = 0; i < width; i++)
        {
            result[i] = getColumn(i);
        }
        return {result, height, width};
    }

    ///Throws an exception if matrix is not square.
    float calculateDeterminant()
    {
        return calculateDeterminant(array, width, height);
    }

    static float calculateDeterminant(T** array, int width, int height)
    {
        if (width != height) throw MatrixException("Can't calculate calculateDeterminant of not square matrix");
        if (width == 1)
        {
            auto x = array[0][0];
            return x;
        }
        else if (width == 2) return array[0][0] * array[1][1] - array[0][1] * array[1][0];
        else
        {
            float det = 0;
            for (int i = 0; i < width; i++)
            {
                int sign = 1;
                if (i % 2 == 1) sign = -1;
                det += sign * array[0][i] *
                        calculateDeterminant(getArrayWithout(array, width, height, 0, i), width - 1,
                                             height - 1);
            }
            return det;
        }
    }

    ///Returns a pointer array of given type, new array does not contain specified row and column.
    T **getArrayWithout(int row, int column)
    {
        return getArrayWithout(array, width, height, row, column);
    }

    ///Returns a pointer array of given type, new array does not contain specified row and column.
    static T **getArrayWithout(T **array, int width, int height, int row, int column)
    {
        //create new array
        T **result = new T *[--height];
        for (int i = 0; i < height; i++)
        {
            result[i] = new T[width - 1];
        }

        //copy contents (except this one row an column)
        for (int i = 0, x = 0; i < height; i++, x++)
        {
            if (i == row) x++; // skip the row
            for (int j = 0, y = 0; j < width - 1; j++, y++)
            {
                if (j == column) y++; // skip the column
                result[i][j] = array[x][y];
            }
        }

        return result;
    }

    ///Returns float type Matrix; to make an inverse we have to divide numbers.
    ///Throws an exception when matrix is not square.
    Matrix<float> inverse()
    {
        if (width != height)
            throw MatrixException("Inverse cannot be calculated for not square matrix");

        // step 1 - calculate multiplier (1 / calculateDeterminant)
        float determinant = calculateDeterminant(array, width, height);
        if (determinant == 0) throw MatrixException("This matrix does not have an inverse");

        // step 2 - transpose
        Matrix matrix = transpose();

        // step 3 - make matrix of minors (matrix containing determinants)


        // make a new array to store determinants (otherwise determinants would be wrongly used in next calculations)
        Matrix<float> temp (width, height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                temp.array[i][j] = calculateDeterminant(matrix.getArrayWithout(i, j), width - 1, height - 1);
        // step 4 - make cofactor matrix  (multiply every second element by -1)
        for (int i = 0, counter = 0; i < height; i++)
            for (int j = 0; j < width; j++, counter++)
                if (counter % 2 == 1) temp.array[i][j] *= -1;
        // step 5 - multiply adjacent matrix by 1 / calculateDeterminant
        return temp * (1.0f / determinant);
    }

    ///Returns float type Matrix for safety
    Matrix<float> operator*(float multiplier)
    {
        //create array of floats
        auto **result = new float *[height];
        for (int i = 0; i < height; i++) result[i] = new float[width];
        //multiply every element
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                result[i][j] = array[i][j] * multiplier;
        return {result, width, height};
    }

    ///Throws an exception if dimensions do not match
    Matrix operator+(Matrix &other)
    {
        if (width != other.width || height != other.height)
            throw MatrixException("cannot add matrices of different sizes");
        T **result = newArray(width, height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                result[i][j] = array[i][j] + other.array[i][j];
        return {result, width, height};
    }

    ///Throws an exception if dimensions do not match
    Matrix operator-(Matrix &other)
    {
        if (width != other.width || height != other.height)
            throw MatrixException("cannot subtract matrices of different sizes");
        T **result = newArray(width, height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                result[i][j] = array[i][j] - other.array[i][j];
        return {result, width, height};
    }

    ///Throws an exception if dimensions do not match
    Matrix operator*(Matrix &other)
    {
        if (width != other.height) throw MatrixException("cannot multiply matrices without matching dimensions");
        //setting up new array
        int resultWidth = other.width;
        int resultHeight = height;
        T **result = newArray(other.width, height);
        //multiplying
        for (int i = 0; i < resultHeight; i++)
        {
            for (int j = 0; j < resultWidth; j++)
            {
                float number = 0;
                T *row = getRow(i);
                T *column = other.getColumn(j);
                for (int x = 0; x < width; x++)
                {
                    number += row[x] * column[x];
                }
                result[i][j] = number;
                delete[] row;
                delete[] column;
            }
        }
        return {result, resultWidth, resultHeight};
    }

    //creation of new 2d arrays is used often, made a separate static method for that
    static T **newArray(int width, int height)
    {
        T **result = new T *[height];
        for (int i = 0; i < height; i++)
        {
            result[i] = new T[width]{0};
        }
        return result;
    }

    T *getRow(int index)
    {
        if (index > height || index < 0) throw std::out_of_range("row doesn't exist");
        T *row = new T[width];
        for (int i = 0; i < width; i++)
        {
            row[i] = array[index][i];
        }
        return row;
    }

    T *getColumn(int index)
    {
        if (index > width || index < 0) throw std::out_of_range("column doesn't exist");
        T *column = new T[height];
        for (int i = 0; i < height; i++)
        {
            column[i] = array[i][index];
        }
        return column;
    }



    T **getArray() const
    {
        return array;
    }

    int getWidth() const
    {
        return width;
    }

    int getHeight() const
    {
        return height;
    }

    bool operator==(const Matrix &rhs) const
    {
        return array == rhs.array;
    }

    bool operator!=(const Matrix &rhs) const
    {
        return rhs != *this;
    }

    explicit operator Matrix<float>() const
    {
        auto **result = new float *[height];
        for (int i = 0; i < height; i++)
        {
            result[i] = new float[width]{0};
            for (int j = 0; j < width; j++)
            {
                result[i][j] = (float) array[i][j];
            }
        }
        return Matrix<float>(result, width, height);
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
    {
        os << "{Matrix:\n" << "width: " << matrix.width << ", height: " << matrix.height << ", array:\n";
        for (int i = 0; i < matrix.height; i++)
        {
            os << "[";
            for (int j = 0; j < matrix.width; j++)
            {
                os << matrix.array[i][j];
                if (j != matrix.width - 1) os << ",\t";
            }
            os << "]\n";
        }
        os << "}";
        return os;
    }


};


#endif //CLION_MATRIX_H
