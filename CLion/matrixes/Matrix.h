//
// Created by jakub on 22.12.2020.
//

#ifndef CLION_MATRIX_H
#define CLION_MATRIX_H

#include<iostream>
#include "../print.h"
class Matrix
{
private:
    int** array;
    int width;
    int height;
public:
    Matrix(int **array, int width, int height) : array(array), width(width), height(height)
    {}

    Matrix(int width, int height) : width(width), height(height)
    {
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

    

    Matrix operator + (Matrix &other)
    {
        if(width != other.width || height != other.height) return *this; //TODO add an exception
        int ** result = newArray(width, height);
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                result[i][j] = array[i][j] + other.array[i][j];
        return {result, width, height};
    }

    Matrix operator - (Matrix &other)
    {
        if(width != other.width || height != other.height) return *this; //TODO add an exception
        int ** result = newArray(width, height);
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                result[i][j] = array[i][j] - other.array[i][j];
        return {result, width, height};
    }

    Matrix operator * (int multiplier)
    {
        int **result = newArray(width, height);
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
        int ** result = newArray(other.width, height);
        //multiplying
        for(int i = 0; i < resultHeight; i++)
        {
            for(int j = 0; j < resultWidth; j++)
            {
                int number = 0;
                int * row = getRow(i);
                int * column = other.getColumn(j);
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

    static int **newArray(int width, int height)
    {
        int ** result = new int * [height];
        for(int i = 0; i < height; i++)
        {
            result[i] = new int [width]{0};
        }
        return result;
    }

    int * getRow(int index)
    {
        if(index > width || index < 0) return nullptr;//TODO add exception
        int * row = new int[width];
        for(int i = 0; i < width; i++)
        {
            row[i] = array[index][i];
        }
        return row;
    }

    int * getColumn(int index)
    {
        if(index > height || index < 0) return nullptr;//TODO add exception
        int * column = new int [height];
        for(int i = 0; i < height; i++)
        {
            column[i] = array[i][index];
        }
        return column;
    }

    int **getArray() const
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
                std::cout<< matrix.array[i][j];
                if (j != matrix.width - 1) os << ",\t";
            }
            os<<"]\n";
        }
        os <<"}";
        return os;
    }


};


#endif //CLION_MATRIX_H
