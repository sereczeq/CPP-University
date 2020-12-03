#pragma once
using namespace std;

template< typename T >
class Stack
{
public:
	Stack();
	~Stack();
	bool push(T elem);
	T pop();
private:
	T* array;
	int arraySize;
};

template <typename T>
Stack<T>::Stack()
{
	array = new T[0];
	arraySize = 0;
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] array;
}

template <typename T>
bool Stack<T>::push(T elem)
{
	T* newArray = new T[arraySize + 1];
	for (int i = 0; i < arraySize; i++)
	{
		newArray[i] = array[i];
	}
	newArray[arraySize] = elem;
	arraySize++;
	delete[] array;
	array = newArray;
	return true;
}

template <typename T>
T Stack<T>::pop()
{
	if (arraySize == 0) return 0;
	T *newArray = new T[--arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		newArray[i] = array[i];
	}
	T temp = array[arraySize];
	delete[] array;
	array = newArray;
	return temp;
}
