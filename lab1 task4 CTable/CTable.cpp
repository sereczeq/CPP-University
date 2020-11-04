#include "CTable.h"

using namespace std;

void CTable::Init(string sName, int iTableLen)
{
	s_name = sName;
	array_size = iTableLen;
	int_array = new int[iTableLen];
	for(int i = 0; i < iTableLen; i++) int_array[i] = 0;
}

CTable::CTable()
{
	Init("default", 0);
	cout << "without: " + s_name << endl;
}

CTable::CTable(string sName, int iTableLen)
{
	Init(sName, iTableLen);
	cout << "parameter: " + s_name << endl;
}

CTable::CTable(const CTable& pcOther)
{
	Init(pcOther.s_name + "_copy", pcOther.array_size);
	for (int i = 0; i < pcOther.array_size; i++) int_array[i] = pcOther.int_array[i];
	cout << "copy: " + s_name << endl;
}

//CTable::~CTable()
//{
//	cout << "deleting: " + s_name << endl;
//	delete[] int_array;
//}

void CTable::vSetName(string sName)
{
	s_name = sName;
}

bool CTable::bSetNewSize(int iTableLen)
{
	if (iTableLen < array_size) return false;

	int* array_clone = new int[iTableLen];
	for(int i = 0; i < iTableLen; i++) array_clone[i] = 0;
	for (int i = 0; i < array_size; i++) array_clone[i] = int_array[i];
	delete[] int_array;
	int_array = array_clone;
	array_size = iTableLen;
	return true;
}

CTable* CTable::pcClone()
{
	return new CTable(*this);
}

string CTable::getName()
{
	return s_name;
}

int CTable::getSizeOfArray()
{
	return array_size;
}

void CTable::vSetValueAt(int iIndex, int iValue)
{
	if (iIndex < 0 || iIndex > array_size || int_array[iIndex] != 0) return;
	int_array[iIndex] = iValue;
}

void CTable::vPrint()
{
	for(auto i = 0;i < array_size; i++)
	{
		cout << int_array[i];
		if (i < array_size - 1) cout << ",";
	}
	cout << endl;
}

CTable CTable::operator + (CTable& other)
{
	CTable c_to_return(s_name, other.array_size + array_size);

	for(int i = 0; i < array_size + other.array_size; i++)
	{
		if (i < array_size) c_to_return.int_array[i] = int_array[i];
		else c_to_return.int_array[i] = other.int_array[i - array_size];
	}
	
	return c_to_return;
}

CTable CTable:: operator-- (int)
{
	CTable c_to_return(s_name, array_size - 1);

	for(int i = 0; i < c_to_return.array_size; i++)	c_to_return.int_array[i] = int_array[i];

	delete[] int_array;
	
	return c_to_return;
}