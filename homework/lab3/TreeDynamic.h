//
// Created by jakub on 13.11.2020.
//

#ifndef LAB3_CPP_TREEDYNAMIC_H
#define LAB3_CPP_TREEDYNAMIC_H


#include "NodeDynamic.h"

class TreeDynamic
{
public:
    TreeDynamic();
    ~TreeDynamic();
    NodeDynamic * getRoot();
    void printTree();
    bool moveSubTree (NodeDynamic * whichNode, NodeDynamic *whichTree, NodeDynamic * whichNodeToSwap);
private:
    NodeDynamic * root;
};


#endif //LAB3_CPP_TREEDYNAMIC_H
