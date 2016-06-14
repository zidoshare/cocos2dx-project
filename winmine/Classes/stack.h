#pragma once
//自写栈，用于DFS算法
class mp{
public:
	int x, y;
};
class stack
{
public:
	stack();
	~stack();
	static stack* create();
	void destroyStack();
	bool clearStack();
	bool stackEmpty();
	int getLength();
	mp *getTop();
	bool push(mp *);
	mp *pop();
private:
	int length;
	int top;
	(mp*)*sck;
};

