#include "stack.h"
#define size 100

stack::stack()
:top(0), length(0)
{
	sck = new mp*[size];
	/*if (!sck)
		return ;*/
	//ÉêÇëÄÚ´æÊ§°Ü²Ù×÷
}


stack::~stack()
{
	
}
stack* stack::create(){
	auto s = new stack();

	return s;
}
void stack::destroyStack(){
	delete[] sck;
}
bool stack::clearStack(){
	destroyStack();
	sck = new mp*[size];
	if (sck)
		return true;
	return false;
}
bool stack::stackEmpty(){
	if (top == 0)
		return true;
	return false;
}
int stack::getLength(){
	return length;
}
mp *stack::getTop(){
	return sck[top];
}
bool stack::push(mp *p){
	if (top >= size - 1)
		return false;
	top++;
	length++;
	sck[top] = p;
}
mp *stack::pop(){
	if (stackEmpty()){
		return nullptr;
	}
	auto qq = sck[top];
	top--;
	return qq;
}
