#include "MyList.h"
using namespace std;
MyList::MyList(int s) :length(0), start(0),size(s){

}
MyList::~MyList(){

}
MyList* MyList::create(int size){
	MyList *li = new MyList(size);
	if (li->init())
		return li;
	return nullptr;
}
bool MyList::init(){
	try{
		a = new int[size];
		b = new int[size];
	}
	catch (bad_alloc& e){
		return false;
	}
	return true;
}
void MyList::add(int x, int y){
	a[length + start] = x;
	b[length + start] = y;
	length++;
}
void MyList::front(int index){
	int wa = a[index + start], wb = b[index + start];
	for (int i = index + start; i > start; i--){
		a[i] = a[i - 1];
		b[i] = b[i - 1];
	}
	a[0] = wa;
	b[0] = wb;
	start++;
	length--;
}
int MyList::getSize(){
	return size;
}
int MyList::getLength(){
	return length;
}
int MyList::getX(int index){
	return a[index + start];
}
int MyList::getY(int index){
	return b[index + start];
}
