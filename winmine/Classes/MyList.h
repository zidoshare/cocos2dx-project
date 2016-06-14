#pragma once
#include <iostream>
class MyList{
public:
	MyList(int s);
	~MyList();
	static MyList* create(int size);
	void add(int x, int y);
	void front(int index);
	int getSize();
	int getLength();
	int getX(int index);
	int getY(int index);
private:
	int size, length, start;
	int *a;
	int *b;
	bool init();
};
