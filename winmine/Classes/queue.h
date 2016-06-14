#pragma once
class list_value{
public :
	list_value();
	~list_value();
	int x, y;
	int value;
	list_value *next;
};
class queue
{
public:
	queue();
	~queue();
	static queue* create();
	void destroyQueue();
	bool clearQueue();
	bool queueEmpty();
	int getLength();
	list_value* getHead();
	bool push(list_value *);
	list_value* pop();
	bool init();
private:
	list_value* head;
	list_value* body;
	int length;
};

