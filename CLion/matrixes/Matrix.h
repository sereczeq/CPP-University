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
    class Determinant //TODO make private later
    {
    public:
        static T calculateDeterminant(T ** array, int width, int height)
        {
            print("array given for determinant: ");
            for(int i = 0; i < width; i++) for(int j = 0; j < height; j++) print(array[i][j]);
            if(width != height) return 0; //TODO thrown an exception
            if(width == 1) {
                auto x = array[0][0];
                return x;
            }
            else if(width == 2) return array[0][0] * array[1][1] - array[0][1] * array[1][0];
            else
            {
                int determinant = 0;
                for(int i= 0; i < width; i++)
                {
                    int sign = 1;
                    if(i % 2 == 1) sign = -1;
                    determinant += sign * array[0][i] *calculateDeterminant(getArrayWithout(array, width, height, 0, i), width - 1, height - 1);
                }
                return determinant;
            }
        }

        static T ** getArrayWithout(T** array, int width, int height, int row, int column)
        {
            //create new array
            T** result = new T*[--height];
            for(int i = 0; i < height; i++)
            {
                result[i] = new T[width - 1];
            }

            //copy contents (except this one row an column)
            for(int i = 0, x = 0; i < height; i++, x++)
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
    };
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

    T determinant()
    {
        return Determinant().calculateDeterminant(array, width, height);
    }
    T** getArrayWithout(int row, int column)
    {
        return Determinant().getArrayWithout(array, width, height, row, column);
    }

    Matrix<float> inverse()
    {
        //if(width != height) return *this; //TODO add an exception

        // step 1 - calculate multiplier
        float multiplier = 1.0f/ Determinant().calculateDeterminant(array, width, height);

        // step 2 - transpose
        Matrix matrix = transpose();
        print("transpose\n"<<matrix);

        // step 3 - make matrix of minors (matrix containing determinants)

        // make a new array to store determinants (otherwise determinants would be wrongly used in next calculations)
        T** temp = newArray(width, height);

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                temp[i][j] = Determinant().calculateDeterminant(matrix.getArrayWithout(i, j), width - 1, height - 1);
                print("elem: " << temp[i][j]);
            }
        }
        delete [] matrix.array;
        matrix.array = temp;
        print("minors\n"<<matrix);

        // step 4 - make cofactor matrix  (multiply every second element by -1)
        for(int i = 0, counter = 0; i <height; i++)
            for(int j = 0; j < width; j++, counter++)
                if(counter % 2 ==1) matrix.array[i][j] *= -1;
        print("cofactors\n"<<matrix);
        // step 5 - multiply adjacent matrix by 1 / determinant
        return matrix  * multiplier;
    }


    Matrix<float> operator * (float multiplier)
    {
        print(multiplier);
        //T **result = newArray(width, height);
        float ** result = new float*[height];
        for(int i = 0; i < height; i++) result[i] = new float[width];
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                result[i][j] = array[i][j] * multiplier;
        return {result, width, height};
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

    explicit operator Matrix<float>() const
    {
        float ** result = new float * [height];
        for(int i = 0; i < height; i++)
        {
            result[i] = new float [width]{0};
            for(int j = 0; j < width; j++)
            {
                result[i][j] = (float)array[i][j];
            }
        }
        return Matrix<float>(result, width, height);
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
