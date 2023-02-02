#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Container
{
public:
	size_t size = sizeof(T);
	int count = 0;
	int capacity = 5;
	Container() {
		
	};
	~Container() {
		delete[] vessel;
	};
	void pushBack(T element) {
		if (count == capacity) {
			extendCapac();
		}
		vessel[count] = T(element);
		count++;
	};
	void pushFront(T element) {
		if (count == capacity) {
			extendCapac();
		}
		memmove_s( vessel + 1, capacity * size - size, vessel, count * size);
		memset(vessel, 0, size);
		vessel[0] = T(element);
		count++;
	};
	void pushByIndex(int index,T element) {
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
	void popBack() {
		if (count) {
			memset(vessel + (count - 1), 0, size);
			vessel[count-1] = T();
			count--;
		};
		if (capacity - count > count) {
			decreCapac();
		};
	};
	void popFront() {
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
	void popByIndex(int index) {
		if (count && index < count) {
			memmove_s(  
						vessel + index,
						(count - index) * size,
						vessel + index + 1,
						(count - index) * size - size
					 );
			memset(vessel+(count-1), 0, size);
			vessel[count - 1] = T();
			count--;
		};
		if (capacity - count > count) {
			decreCapac();
		};
	};
	void printElement() {
		for (int i = 0; i < count; i++)
		{
			cout << vessel[i]<< " ";
		}
		for (int i = 0; i < capacity - count; i++)
		{
			cout <<"_ ";
		}
		cout << endl;
	};
private:
	T* vessel = new T[5];
	void extendCapac() {
		int newCapacity = capacity + (int)(capacity * 0.5);
		T* temp = new T[newCapacity];
		memmove_s(temp, newCapacity * size, vessel, count * size); 
		memset(vessel, 0, size * capacity); //Essential part , if without it user-define type may occur destructor execute ahead of time
		delete[] vessel;
		vessel = temp;
		capacity = newCapacity;
	};
	void decreCapac() {
		int newCapacity = count;
		T* temp = new T[newCapacity];
		memmove_s(temp, newCapacity * size, vessel, count * size);
		memset(vessel, 0, size * capacity);
		delete[] vessel;
		vessel = temp;
		capacity = newCapacity;
	};
};

int TestMain() {
	Container<string> c;
	/*for (int i = 0; i < 13; i++) {
		c.pushBack(i+1);
	}*/
	/*c.pushFront(99);
	c.pushFront(888);*/

	c.pushBack("hello");
	c.pushBack("world");
	c.pushBack("that's");
	c.pushBack("all");
	c.pushBack("!");

	c.pushBack("last");
	c.pushFront("first");
	c.pushByIndex(1, "sec");
	c.printElement();

	//for (int i = 0; i < 1; i++) {
	//	//c.popFront();
	//	//c.popByIndex(0);
	//	c.pushByIndex(13, 99);
	//};
	
	c.popBack();
	c.popFront();
	c.popByIndex(1);
	c.popByIndex(1);
	//c.pushByIndex(1, "sec");
	//c.pushByIndex(2,"last");
	c.printElement();
	cout << "Count:\t\t" << c.count << endl;
	cout << "Capacity:\t" << c.capacity << endl;
	return 0;
};