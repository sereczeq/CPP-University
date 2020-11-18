#pragma once
#include <iostream>
#include <vector>
using namespace std;

template< typename T >class NodeStatic
{
public:
	NodeStatic();
	NodeStatic(T val);
	NodeStatic(NodeStatic* parent);
	~NodeStatic();
	void setValue(T iNewVal);
	int getChildrenNumber();
	void addNewChild();
    void addNewChild(NodeStatic<T> newChild);
	bool deleteChild(NodeStatic<T> toDelete);
	NodeStatic* getChild(int iChildOffset);
	void print() const;
	void printAllBelow();
	void printUp();
    int countOccurrences(T elem);
	bool operator == (NodeStatic other);
private:
	vector<NodeStatic> children;
	T val;
	NodeStatic* parent;
};