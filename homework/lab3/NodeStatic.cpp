#include "NodeStatic.h"

template <typename T>
NodeStatic<T>::NodeStatic()
{
	val = 0;
	parent = 0;
}
template< typename T >
NodeStatic<T>::NodeStatic(NodeStatic* parent)
{
	val = 0;
	this->parent = parent;
}

template< typename T >
NodeStatic<T>::~NodeStatic()
= default;


template< typename T >
void NodeStatic<T>::setValue(T iNewVal)
{
	val = iNewVal;
}


template< typename T >
int NodeStatic<T>::getChildrenNumber()
{
	return (children.size());
}

template< typename T >
void NodeStatic<T>::addNewChild()
{
	children.push_back(NodeStatic(this));
}

template< typename T >
NodeStatic<T>* NodeStatic<T>::getChild(int iChildOffset)
{
	for(int i = 0; i < children.size(); i++)
	{
		if (i == iChildOffset) return &children[i];
	}
	return 0;
}

template< typename T >
void NodeStatic<T>::print() const
{
	cout << " " << val;
}

template< typename T >
void NodeStatic<T>::printAllBelow()
{
	print();
	for (NodeStatic<T> child : children) child.printAllBelow();
}

template <typename T>
void NodeStatic<T>::printUp()
{
	print();
	if (parent == 0) return;
	parent->printUp();
}

template<typename T>
void NodeStatic<T>::addNewChild(NodeStatic<T> newChild) {
	newChild.parent = this;
	children.push_back(newChild);
}

//***** ***
template<typename T>
bool NodeStatic<T>::deleteChild(NodeStatic<T> toDelete) {
    auto it = find(children.begin(), children.end(), toDelete);
    if(it != children.end())
    {
        children.erase(it);
        return true;
    }
	return false;
}

template<typename T>
bool NodeStatic<T>::operator==(NodeStatic other) {
    return parent == other.parent && val == other.val;
}
