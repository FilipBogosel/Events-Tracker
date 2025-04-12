#pragma once
#include <string>
#include "Event.h"
template <typename T>
class DynamicVector
{
private:
	int size, capacity;
	T* elements;
public:
	//Default constructor for a DynamicVector with default size 10 if not specified
	DynamicVector(int capacity = 10);
	//Copy constructor
	DynamicVector(const DynamicVector& v);
	//destructor
	~DynamicVector();
	//assignment operator overloading
	DynamicVector& operator=(const DynamicVector& v);
	/*
		Overloading the subscript operator 
		Input: pos, a position in the vector
		Output: a refference to the element on position pos
	*/
	T& operator[](int pos);
	//Adds an element to the end of the DynamicVector
	void append(T element);

	//Removes an element from a given position
	void remove_from_position(int position);

	//Inserts an element at a given position:TODO

	//Returns the position of a given entity in the vector, if it doesn't find it returns -1
	int find_position(T element);
	

	int get_size() const;
	int get_capacity() const;

private:
	//Resize operation with default factor for capacity enlarging 2
	void resize(int factor = 2);




};

template<typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->capacity; i++)
	{
		this->elements[i] = T();
	}
}

template<typename T>
DynamicVector<T>::DynamicVector(const DynamicVector& v)
{
	this->size = v.size;
	this->capacity = v.capacity;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = v.elements[i];
}

template<typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elements;
}

template<typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& v)
{
	if (this == &v)
		return *this;
	this->size = v.size;
	this->capacity = v.capacity;
	T *aux = new T[this->capacity];
	delete[] this->elements;
	this->elements = aux;
	for (int i = 0; i < this->capacity; i++) {
		this->elements[i] = v.elements[i];
	}
	return *this;
}

template<typename T>
T& DynamicVector<T>::operator[](int pos)
{
	return this->elements[pos];
}

template<typename T>
void DynamicVector<T>::append(T element)
{
	if (this->size == this->capacity)
		this->resize();
	this->elements[this->size] = element;
	this->size++;
}

template<typename T>
void DynamicVector<T>::resize(int factor) {
	this->capacity *= factor;
	T* elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++) {
		elems[i] = this->elements[i];
	}
	delete[] this->elements;
	this->elements = elems;
}

template<typename T>
void DynamicVector<T>::remove_from_position(int position)
{
	for (int i = position; i < this->size - 1; i++) {
		this->elements[i] = this->elements[i + 1];
	}
	this->size--;
}

template<typename T>
int DynamicVector<T>::find_position(T element)
{
	for (int i = 0; i < this->size; i++) {
		if (this->elements[i] == element) return i;
	}
	return -1;
}

template<typename T>
int DynamicVector<T>::get_size() const {
	return this->size;
}

template<typename T>
int DynamicVector<T>::get_capacity() const {
	return this->capacity;
}


