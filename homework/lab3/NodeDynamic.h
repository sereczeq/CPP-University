//
// Created by jakub on 13.11.2020.
//

#ifndef LAB3_CPP_NODEDYNAMIC_H
#define LAB3_CPP_NODEDYNAMIC_H

using namespace std;

#include <iostream>
#include <vector>

class NodeDynamic {
public:
    NodeDynamic();

    NodeDynamic(NodeDynamic * newParent);

    ~NodeDynamic();


    void setValue(int newValue);

    int getChildrenNumber();

    void addNewChild();

    void addNewChild(NodeDynamic * child);

    NodeDynamic *getChild(int childOffset);

    void print();

    void printAllBelow();

    bool deleteChild(NodeDynamic * toDelete);

private:
    NodeDynamic * parent;
    vector<NodeDynamic *> children;
    int val;
};


#endif //LAB3_CPP_NODEDYNAMIC_H
