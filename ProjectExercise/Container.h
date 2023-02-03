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
	unsigned int iter_index = 0;
	unsigned int count = 0;
	unsigned int capacity = INIT_SIZE;
	Container();
	~Container();

	void push_back(T element);
	void push_front(T element);
	void push_by_index(unsigned int index, T element);

	void pop_back();
	void pop_front();
	void pop_by_index(unsigned int index);

	T iter_element();

	void print_element();
private:
	T* vessel = new T[INIT_SIZE];
	void extend_capac();
	void decre_capac();
};



template <typename T>
Container<T>::Container() {

};

template <typename T>
Container<T>::~Container() {
	delete[] vessel;
};

template <typename T>
void  Container<T>::push_back(T element) {
	if (count == capacity) {
		extend_capac();
	}
	vessel[count] = T(element);
	count++;
};
template <typename T>
void Container<T>::push_front(T element) {
	if (count == capacity) {
		extend_capac();
	}
	memmove_s(vessel + 1, capacity * size - size, vessel, count * size);
	memset(vessel, 0, size);
	vessel[0] = T(element);
	count++;
};
template <typename T>
void Container<T>::push_by_index(unsigned int index, T element) {
	if (count == capacity) {
		extend_capac();
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
void Container<T>::pop_back() {
	if (count) {
		memset(vessel + (count - 1), 0, size);
		vessel[count - 1] = T();
		count--;
	};
	if (capacity - count > count) {
		decre_capac();
	};
};

template <typename T>
void Container<T>::pop_front() {
	if (count) {
		memmove_s(vessel, count * size, vessel + 1, count * size - size);
		memset(vessel + (count - 1), 0, size);
		vessel[count - 1] = T();
		count--;
	};
	if (capacity - count > count) {
		decre_capac();
	};
};

template <typename T>
void Container<T>::pop_by_index(unsigned int index) {
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
		decre_capac();
	};
};

template <typename T>
T Container<T>::iter_element() {
	if (!(iter_index<count))
	{
		iter_index = 0;
	}
	return vessel[iter_index++];
};

template <typename T>
void Container<T>::print_element() {
	for (unsigned int i = 0; i < count; i++)
	{
		cout << vessel[i] << " ";
	}
	for (unsigned int i = 0; i < capacity - count; i++)
	{
		cout << "_ ";
	}
	cout << endl;
	cout << "count:\t\t" << count << endl;
	cout << "capacity:\t" << capacity << endl;
	cout << endl;
};

template <typename T>
void Container<T>::extend_capac() {
	unsigned int newCapacity = capacity + (unsigned int)(capacity * 0.5);
	T* temp = new T[newCapacity];
	memmove_s(temp, newCapacity * size, vessel, count * size);
	memset(vessel, 0, size * capacity); //Essential part , if without it user-define type may occur destructor execute ahead of time
	delete[] vessel;
	vessel = temp;
	capacity = newCapacity;
};

template <typename T>
void Container<T>::decre_capac() {
	unsigned int newCapacity = count;
	T* temp = new T[newCapacity];
	memmove_s(temp, newCapacity * size, vessel, count * size);
	memset(vessel, 0, size * capacity);
	delete[] vessel;
	vessel = temp;
	capacity = newCapacity;
};