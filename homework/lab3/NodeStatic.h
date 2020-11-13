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
	NodeStatic* getChild(int iChildOffset);
	void print() const;
	void printAllBelow();
	void printUp();
private:
	vector<NodeStatic> children;
	T val;
	NodeStatic* parent;
};