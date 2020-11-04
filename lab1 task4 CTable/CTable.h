#pragma once
#include <iostream>

using namespace std;

class CTable
{
private:
	string s_name;
	int* int_array;
	
	void Init(string sName, int iTableLen);
public:
	int array_size;
	CTable();
	CTable(string sName, int iTableLen);
	CTable(const CTable& pcOther);
	//~CTable();
	void vSetName(string sName);
	bool bSetNewSize(int iTableLen);
	CTable* pcClone();
	string getName();
	int getSizeOfArray();
	void vSetValueAt(int iIndex, int iValue);
	void vPrint();
	CTable operator + (CTable& other);
	CTable operator -- (int);
};
