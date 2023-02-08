#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#define INIT_SIZE 5
#define EXTEND_SCALE_HALF capacity + (unsigned int)(capacity * 0.5)
#define EXTEND_SCALE_QUARTER capacity + (unsigned int)(capacity * 0.25)
#define EXTEND_SCALE_INIT lst.size() + (lst.size() * 0.25)
#include <iostream>
#include <initializer_list>
using namespace std;



template <typename T>
class Container
{
	typedef int(*CmpPtr)(T,T);
public:
	size_t size = sizeof(T);
	Container(initializer_list<T> lst);
	~Container();

	T& operator[](unsigned int i);

	/*
		set_cmpfunc:
		Set a compare function to a pointer for sort component
		the function convention format should be   :    int(*)(T mainVar,T subVar)
		if mainVar greater than subVar return 1
		if mainVar equal subVar return 0
		if mainVar less than subVar return -1
	*/
	inline void set_cmpfunc(CmpPtr p) { compare_fp = p; };
	
	void push_back(T element);
	void push_front(T element);
	void push_by_index(unsigned int index, T element);

	void pop_back();
	void pop_front();
	void pop_by_index(unsigned int index);

	void sort_asc();
	void sort_desc();

	T iter_element();

	void print_element();

	
private:
	unsigned int iter_index = 0;
	unsigned int count = 0;
	unsigned int capacity = INIT_SIZE;
	T* vessel = new T[INIT_SIZE];
	CmpPtr compare_fp = NULL;
	void extend_capac(unsigned int extendScale);
	void decre_capac();
};

template <typename T>
Container<T>::Container(initializer_list<T> lst) {
	if (lst.size() > capacity) extend_capac(EXTEND_SCALE_INIT);
	for (size_t i = 0; i < lst.size(); i++)
	{
		vessel[i] = *(lst.begin() + i);
	};
	count = lst.size();
};

template <typename T>
Container<T>::~Container() {
	delete[] vessel;
};

template <typename T>
T& Container<T>::operator[](unsigned int i) {
	return vessel[i];
};

template <typename T>
void  Container<T>::push_back(T element) {
	if (count == capacity) extend_capac(EXTEND_SCALE_HALF);
	vessel[count] = T(element);
	count++;
};

template <typename T>
void Container<T>::push_front(T element) {
	if (count == capacity) extend_capac(EXTEND_SCALE_HALF);
	memmove_s(vessel + 1, capacity * size - size, vessel, count * size);
	memset(vessel, 0, size);
	vessel[0] = T(element);
	count++;
};

template <typename T>
void Container<T>::push_by_index(unsigned int index, T element) {
	if (count == capacity) extend_capac(EXTEND_SCALE_HALF);
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
	for (size_t i = 0; i < count; i++)
	{
		cout << vessel[i] << " ";
	}
	for (size_t i = 0; i < capacity - count; i++)
	{
		cout << "_ ";
	}
	cout << endl;
	cout << "count:\t\t" << count << endl;
	cout << "capacity:\t" << capacity << endl;
	cout << endl;
};

template <typename T>
void Container<T>::sort_asc() {
	if (!compare_fp) return;
	T temp = T();
	for (size_t i = count - 1; i; i--) {
		for (size_t j = 0; j < count - 1; j++) {
			if (compare_fp(vessel[j], vessel[j+1])==1) {
				temp = vessel[j];
				vessel[j] = vessel[j + 1];
				vessel[j + 1] = temp;
			}
		};
	};
};

template <typename T>
void Container<T>::sort_desc() {
	if (!compare_fp) return;
	T temp = T();
	for (size_t i = count - 1; i; i--) {
		for (size_t j = 0; j < count - 1; j++) {
			if (compare_fp(vessel[j], vessel[j + 1]) == -1) {
				temp = vessel[j];
				vessel[j] = vessel[j + 1];
				vessel[j + 1] = temp;
			}
		};
	};
};

template <typename T>
void Container<T>::extend_capac(unsigned int extendScale) {
	unsigned int newCapacity = extendScale;								
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