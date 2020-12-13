//
// Created by jakub on 13.12.2020.
//

#ifndef CLION_CTABLE_H
#define CLION_CTABLE_H
#pragma once

#include <iostream>
#include <utility>

using namespace std;

class CTable
{
private:
    string s_name;
    int array_size;
    int *int_array;

    void Init(string sName, int iTableLen)
    {
        s_name = std::move(sName);
        array_size = iTableLen;
        int_array = new int[iTableLen]{};
    }

public:

    CTable()
    {
        Init("default", 1);
        cout << "without: " + s_name << endl;
    }

    CTable(string sName, int iTableLen)
    {
        Init(sName, iTableLen);
        cout << "parameter: " + s_name << endl;
    }

    CTable(const CTable &pcOther)
    {
        Init(pcOther.s_name + "_copy", pcOther.array_size);
        for (int i = 0; i < pcOther.array_size; i++) int_array[i] = pcOther.int_array[i];
        cout << "copy: " + s_name << endl;
    }

    CTable(CTable &&other) noexcept
    {
        cout << "move: " + s_name << endl;
        array_size = other.array_size;
        int_array = other.int_array;

        other.int_array = nullptr;
        other.array_size = 0;

    }

    ~CTable()
    {
        cout << "destructor: " + s_name << endl;
        delete[] int_array;
    }


    void vSetName(string sName)
    {
        s_name = std::move(sName);
    }

    bool bSetNewSize(int iTableLen)
    {
        if (iTableLen < array_size) return false;

        CTable c_to_return("newSize", iTableLen);
        for (int i = 0; i < array_size; i++) c_to_return.int_array[i] = int_array[i];

        int_array = c_to_return.int_array;
        array_size = c_to_return.array_size;

        c_to_return.array_size = 0;
        c_to_return.int_array = nullptr;

        return true;
    }

    CTable *pcClone()
    {
        return new CTable(*this);
    }

    string getName()
    {
        return s_name;
    }

    int getSizeOfArray()
    {
        return array_size;
    }

    void vSetValueAt(int iIndex, int iValue)
    {
        if (iIndex < 0 || iIndex > array_size || int_array[iIndex] != 0) return;
        int_array[iIndex] = iValue;
    }

    void vPrint()
    {
        cout << "table: ";
        for (auto i = 0; i < array_size; i++)
        {
            cout << int_array[i];
            if (i < array_size - 1) cout << ",";
        }
        cout << endl;
    }

    CTable &operator=(CTable &&other) noexcept
    {
        cout << "move: " + s_name << endl;
        if (this != &other)
        {
            delete[] int_array;

            array_size = other.array_size;
            int_array = other.int_array;

            other.array_size = 0;
            other.int_array = nullptr;
        }
        return *this;
    }

    CTable operator+(CTable &other)
    {
        CTable c_to_return("addTable", other.array_size + array_size);

        for (int i = 0; i < array_size + other.array_size; i++)
        {
            if (i < array_size) c_to_return.int_array[i] = int_array[i];
            else c_to_return.int_array[i] = other.int_array[i - array_size];
        }

        int_array = c_to_return.int_array;
        array_size = c_to_return.array_size;

        c_to_return.array_size = 0;
        c_to_return.int_array = nullptr;
        if (this != &other)
        {
            other.array_size = 0;
            other.int_array = nullptr;
        }
        return *this;
    }

    CTable operator--(int)
    {
        CTable c_to_return("--Table", array_size - 1);

        for (int i = 0; i < c_to_return.array_size; i++) c_to_return.int_array[i] = int_array[i];

        int_array = c_to_return.int_array;
        array_size = c_to_return.array_size;

        c_to_return.array_size = 0;
        c_to_return.int_array = nullptr;

        return *this;
    }
};

#endif //CLION_CTABLE_H
