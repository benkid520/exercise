#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#define INIT_SIZE 5
#include <iostream>
using namespace std;

template <typename T>
class Container
{
public:
	size_t size = sizeof(T);
	int count = 0;
	int capacity = 5;
	Container();
	~Container();
	void pushBack(T element);
	void pushFront(T element);
	void pushByIndex(int index, T element);
	void popBack();
	void popFront();
	void popByIndex(int index);
	void printElement();
private:
	T* vessel = new T[INIT_SIZE];
	void extendCapac();
	void decreCapac();
};

template <typename T>
Container<T>::Container() {

};

template <typename T>
Container<T>::~Container() {
	delete[] vessel;
};

template <typename T>
void  Container<T>::pushBack(T element) {
	if (count == capacity) {
		extendCapac();
	}
	vessel[count] = T(element);
	count++;
};
template <typename T>
void Container<T>::pushFront(T element) {
	if (count == capacity) {
		extendCapac();
	}
	memmove_s(vessel + 1, capacity * size - size, vessel, count * size);
	memset(vessel, 0, size);
	vessel[0] = T(element);
	count++;
};
template <typename T>
void Container<T>::pushByIndex(int index, T element) {
	if (count == capacity) {
		extendCapac();
	}
	if (index <= count) {

		memmove_s(
			vessel + index + 1,
			(count - index) * size,
			vessel + index,
			(count - index) * size
		);
		memset(vessel + index, 0, size);
		vessel[index] = T(element);
		count++;
	};
};

template <typename T>
void Container<T>::popBack() {
	if (count) {
		memset(vessel + (count - 1), 0, size);
		vessel[count - 1] = T();
		count--;
	};
	if (capacity - count > count) {
		decreCapac();
	};
};

template <typename T>
void Container<T>::popFront() {
	if (count) {
		memmove_s(vessel, count * size, vessel + 1, count * size - size);
		memset(vessel + (count - 1), 0, size);
		vessel[count - 1] = T();
		count--;
	};
	if (capacity - count > count) {
		decreCapac();
	};
};

template <typename T>
void Container<T>::popByIndex(int index) {
	if (count && index < count) {
		memmove_s(
			vessel + index,
			(count - index) * size,
			vessel + index + 1,
			(count - index) * size - size
		);
		memset(vessel + (count - 1), 0, size);
		vessel[count - 1] = T();
		count--;
	};
	if (capacity - count > count) {
		decreCapac();
	};
};

template <typename T>
void Container<T>::printElement() {
	for (int i = 0; i < count; i++)
	{
		cout << vessel[i] << " ";
	}
	for (int i = 0; i < capacity - count; i++)
	{
		cout << "_ ";
	}
	cout << endl;
};

template <typename T>
void Container<T>::extendCapac() {
	int newCapacity = capacity + (int)(capacity * 0.5);
	T* temp = new T[newCapacity];
	memmove_s(temp, newCapacity * size, vessel, count * size);
	memset(vessel, 0, size * capacity); //Essential part , if without it user-define type may occur destructor execute ahead of time
	delete[] vessel;
	vessel = temp;
	capacity = newCapacity;
};

template <typename T>
void Container<T>::decreCapac() {
	int newCapacity = count;
	T* temp = new T[newCapacity];
	memmove_s(temp, newCapacity * size, vessel, count * size);
	memset(vessel, 0, size * capacity);
	delete[] vessel;
	vessel = temp;
	capacity = newCapacity;
};