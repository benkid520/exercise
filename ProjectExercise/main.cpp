#pragma once
#include "Container.h"
#include <iostream>
using namespace std;
int main() {
	
	Container<string> c;
	c.push_back("hello");
	c.push_back("world");
	c.push_back("!");
	c.print_element();
	c.push_front("first");
	c.push_back("back");
	c.push_by_index(1, "sec");
	c.print_element();
	c.pop_front();
	c.pop_back();
	c.pop_by_index(1);
	c.print_element();

	for (size_t i = 0; i < 10; i++)
	{
		cout << c.iter_element() << endl;
	}
	return 0;
};