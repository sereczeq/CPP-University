//
// Created by jakub on 13.11.2020.
//

#include "NodeDynamic.h"

NodeDynamic::NodeDynamic() {
    val = 0;
    parent = nullptr;
}
NodeDynamic::NodeDynamic(NodeDynamic * newParent) {
    val = 0;
    parent = newParent;
}

void NodeDynamic::printAllBelow() {
    print();
    for(NodeDynamic * child : children) child->printAllBelow();
}

NodeDynamic::~NodeDynamic() {
    for(NodeDynamic * child : children)
    {
        delete child;
    }
    children.clear();
}

void NodeDynamic::setValue(int newValue) {
    val = newValue;
}

int NodeDynamic::getChildrenNumber() {
    return children.size();
}

void NodeDynamic::addNewChild() {
    children.push_back(new NodeDynamic(this));
}
void NodeDynamic::addNewChild(NodeDynamic * newChild) {
    newChild->parent = this;
    children.push_back(newChild);
}

// ***** ***
bool NodeDynamic::deleteChild(NodeDynamic *toDelete) {
    for(int i = 0; i < children.size(); i++)
    {
        if (children[i] == toDelete)
        {
            children[i]->~NodeDynamic();
            delete children[i];
            children.erase(children.begin() + i);
            return true;
        }
    }
    return false;
}


void NodeDynamic::print() {
    cout<< " "<<val;
}

NodeDynamic *NodeDynamic::getChild(int childOffset) {
    for(int i = 0; i < children.size(); i++)
    {
        if (i == childOffset) return children[i];
    }
    return 0;
}

