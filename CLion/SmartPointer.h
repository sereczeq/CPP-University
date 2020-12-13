//
// Created by jakub on 12.12.2020.
//

#ifndef CLION_SMARTPOINTER_H
#define CLION_SMARTPOINTER_H

#include "print.h"
template<typename T>
class SmartPointer
{
public:
    explicit SmartPointer(T *whatToPointAt);

    explicit SmartPointer(T whatToPointAt);

    SmartPointer(const SmartPointer<T> &other);

    ~SmartPointer();

    T &operator*();

    T *operator->();

    SmartPointer &operator = (SmartPointer<T> other);
private:
    int* counter{};
    T *pointer;

};

template<typename T>
SmartPointer<T>::SmartPointer(T *whatToPointAt)
{
    counter = new int(1);
    pointer = whatToPointAt;
    print("initialized pointer dynamically: " << *pointer);
}

template<typename T>
SmartPointer<T>::SmartPointer(T whatToPointAt)
{
    counter = new int(1);
    pointer = new T(whatToPointAt);
    print("initialized pointer statically: " << *pointer);
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T> &other)
{
    pointer = other.pointer;
    counter = other.counter;
    (*counter)++;
    print("copied pointer: " << *pointer);
}

template<typename T>
SmartPointer<T>::~SmartPointer()
{
    print("destructor called on: " << *pointer);
    if(--(*counter) <=0)
    {
        delete pointer;
        delete counter;
        print("pointer destroyed");
    }
    else print("references on: " << *pointer << " left: " << *counter);
}

template<typename T>
T &SmartPointer<T>::operator*()
{
    return *pointer;
}

template<typename T>
T *SmartPointer<T>::operator->()
{
    &pointer;
}

template<typename T>
SmartPointer<T> &SmartPointer<T>::operator=(SmartPointer<T> other)
{
    print("operator = on: " << *pointer);
    print("clearing old data of: " << *pointer);
    if(--(*counter) <=0)
    {
        delete pointer;
        delete counter;
        print("pointer destroyed");
    }
    else print("references on: " << *pointer << " left: " << *counter);
    pointer = other.pointer;
    counter = other.counter;
    (*counter)++;
    return *this;
}



#endif //CLION_SMARTPOINTER_H
