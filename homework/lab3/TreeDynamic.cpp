//
// Created by jakub on 13.11.2020.
//

#include "TreeDynamic.h"

TreeDynamic::TreeDynamic() {
    root = new NodeDynamic();
}

TreeDynamic::~TreeDynamic() {
    root->~NodeDynamic();
    delete this;
}

NodeDynamic *TreeDynamic::getRoot() {
    return root;
}

void TreeDynamic::printTree() {
    root->printAllBelow();
}



bool TreeDynamic::moveSubTree(NodeDynamic *parentNode, NodeDynamic *newChild, NodeDynamic *parentNode2) {
    parentNode->addNewChild(newChild);
    return parentNode2->deleteChild(newChild);
}
