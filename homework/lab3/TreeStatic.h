#pragma once

#include "NodeStatic.h"

template<typename T>
class TreeStatic {
public:
    TreeStatic();

    ~TreeStatic();

    NodeStatic<T> *getRoot();

    void printTree();

    bool moveSubTree(NodeStatic<T> parentNode, NodeStatic<T> newChild, NodeStatic<T> parentNode2);
private:
    NodeStatic<T>* root_;

};

