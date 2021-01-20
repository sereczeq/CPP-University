//
// Created by jakub on 03.01.2021.
//

#ifndef CLION_MATRIXEXCEPTION_H
#define CLION_MATRIXEXCEPTION_H

#include <exception>
class MatrixException : public std::exception
{
public:
    explicit MatrixException(const char *msg)
            : std::exception(msg)
    {
    }

};
#endif //CLION_MATRIXEXCEPTION_H
