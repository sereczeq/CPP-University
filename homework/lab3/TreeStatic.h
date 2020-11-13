#pragma once

#include "NodeStatic.h"

template<typename T>
class TreeStatic {
public:
    TreeStatic();

    ~TreeStatic();

    NodeStatic<T> *getRoot();

    void printTree();

private:
    NodeStatic<T>* root_;

};

