#pragma once
#include <iostream>
#include "Container.h"
using namespace std;
int main() {
	Container<string> c;
	c.pushBack("hello");
	c.pushBack("world");
	c.pushBack("!");
	c.printElement();
	c.pushFront("first");
	c.pushBack("back");
	c.pushByIndex(1, "sec");
	c.printElement();
	c.popFront();
	c.popBack();
	c.popByIndex(1);
	c.printElement();
	return 0;
};