//
// Created by jakub on 22.12.2020.
//

#ifndef CLION_MATRIX_H
#define CLION_MATRIX_H

#include<iostream>
#include <type_traits>
#include "../print.h"
template<typename T>
class Matrix
{
private:
    T** array;
    int width;
    int height;
public:
    Matrix(T **array, int width, int height) : array(array), width(width), height(height)
    {
        static_assert(std::is_arithmetic_v<T> , "Wrong type given. Matrix can't be created");
    }

    Matrix(int width, int height) : width(width), height(height)
    {
        static_assert(std::is_arithmetic_v<T> , "Wrong type given. Matrix can't be created");
        array = newArray(width, height);
    }

    ~Matrix()
    {
        for(int i = 0; i < height; i++)
        {
            delete [] array[i];
        }
        delete array;
    }

    Matrix transpose()
    {
        T ** result = new T*[width];
        for(int i = 0; i < width; i++)
        {
            result[i] = getColumn(i);
        }
        return {result, height, width};
    }

    Matrix operator + (Matrix &other)
    {
        if(width != other.width || height != other.height) return *this; //TODO add an exception
        T ** result = newArray(width, height);
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                result[i][j] = array[i][j] + other.array[i][j];
        return {result, width, height};
    }

    Matrix operator - (Matrix &other)
    {
        if(width != other.width || height != other.height) return *this; //TODO add an exception
        T ** result = newArray(width, height);
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                result[i][j] = array[i][j] - other.array[i][j];
        return {result, width, height};
    }

    Matrix operator * (T multiplier)
    {
        T **result = newArray(width, height);
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                result[i][j] = array[i][j] * multiplier;
        return {result, width, height};
    }



    Matrix operator * (Matrix & other)
    {
        if (width != other.height) return *this; //TODO add an exception
        //setting up new array
        int resultWidth = other.width;
        int resultHeight = height;
        T ** result = newArray(other.width, height);
        //multiplying
        for(int i = 0; i < resultHeight; i++)
        {
            for(int j = 0; j < resultWidth; j++)
            {
                int number = 0;
                T * row = getRow(i);
                T * column = other.getColumn(j);
                for(int x = 0; x < width; x++)
                {
                    number += row[x] * column[x];
                }
                result[i][j] = number;
                delete [] row;
                delete [] column;
            }
        }
        return {result, resultWidth, resultHeight};
    }

    static T **newArray(int width, int height)
    {
        T ** result = new T * [height];
        for(int i = 0; i < height; i++)
        {
            result[i] = new T [width]{0};
        }
        return result;
    }

    T * getRow(int index)
    {
        if(index > height || index < 0) return nullptr;//TODO add exception
        T * row = new T[width];
        for(int i = 0; i < width; i++)
        {
            row[i] = array[index][i];
        }
        return row;
    }

    T * getColumn(int index)
    {
        if(index > width || index < 0) return nullptr;//TODO add exception
        T * column = new T [height];
        for(int i = 0; i < height; i++)
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
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
    {
        os << "{Matrix:\n"<< "width: " << matrix.width << ", height: " << matrix.height << ", array:\n";
        for(int i = 0; i < matrix.height; i++)
        {
            os<<"[";
            for (int j = 0; j < matrix.width; j++)
            {
                os<< matrix.array[i][j];
                if (j != matrix.width - 1) os << ",\t";
            }
            os<<"]\n";
        }
        os <<"}";
        return os;
    }


};


#endif //CLION_MATRIX_H
