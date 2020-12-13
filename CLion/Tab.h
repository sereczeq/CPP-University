//
// Created by jakub on 13.12.2020.
//

#ifndef CLION_TAB_H
#define CLION_TAB_H

#include "print.h"

class Tab
{
private:
    int *tab;
    int size;

    void copy(const Tab &other)
    {
        print("copy");
        size = other.size;
        tab = new int[size];

        for(int i = 0; i < size; i++)
        {
            tab[i] = other.tab[i];
        }
    }

public:
    Tab()
    {
        size = 10;
        tab = new int[size]{0};
    }

    Tab(const Tab &other)
    {
        copy(other);
    }

    Tab(Tab &&other)
    {
        print("move");
        size = other.size;
        tab = other.tab;

        other.size = 0;
        other.tab = nullptr;
    }

    ~Tab()
    {
        print("destructor called");
        delete[] tab;

    }

//    Tab& operator=(const Tab &other)
//    {
//        print("operator =");
//        if (*this != other)
//        {
//            delete[] tab;
//            copy(other);
//        }
//        return *this;
//    }

    Tab& operator=(Tab&& other) noexcept
    {
        print("move");
        if (this != &other)
        {
            delete[] tab;

            size = other.size;
            tab = other.tab;

            other.size = 0;
            other.tab = nullptr;
        }
        return *this;
    }

    void toString()
    {
        std::cout<<"table contents: ";
        for(int i = 0; i < size; i++)
        {
            std::cout<<tab[i]<<", ";
        }
        print("");
    }

    bool setSize(int newSize)
    {
        if(newSize < size) return false;
        int *newTab = new int[newSize];
        for(int i = 0; i < size; i++)
        {
            newTab[i] = tab[i];
        }
        delete[] tab;
        size = newSize;
        tab = newTab;
        return true;
    }

    int getSize()
    { return size; }


};


#endif //CLION_TAB_H
