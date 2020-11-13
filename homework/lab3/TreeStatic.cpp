#include "TreeStatic.h"

template <typename T>
TreeStatic<T>::TreeStatic()
{
    root_ = NodeStatic<T>();
}

template <typename T>
TreeStatic<T>::~TreeStatic()
{
}

template <typename T>
void TreeStatic<T>::printTree()
{
    root_->printAllBelow();
}

template<typename  T>
NodeStatic<T> *TreeStatic<T>::getRoot() {
    return root_;
}
template <typename T>
bool TreeStatic<T>::moveSubTree(NodeStatic<T> parentNode, NodeStatic<T> newChild, NodeStatic<T> parentNode2) {
    parentNode.addNewChild(newChild);
    return parentNode2.deleteChild(newChild);
}