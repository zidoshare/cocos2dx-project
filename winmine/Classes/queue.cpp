#include "queue.h"
#include "cocos2d.h"

list_value::list_value(){

}
list_value::~list_value(){

	cocos2d::log("xxxx");
}
queue::queue()
:head(NULL), length(0)
{
}


queue::~queue()
{
}
queue* queue::create(){
	auto q = new queue();
	if (q->init())
		return q;
	return NULL;
}
bool queue::init(){



	return true;
}
void queue::destroyQueue(){
	if (head == NULL)
		return;
	while (head->next != NULL){
		auto val = head;
		head = head->next;
		delete val;
	}
}
bool queue::clearQueue(){
	head = NULL;
	length = 0;
	return true;
}
bool queue::queueEmpty(){
	return length == 0 ? true : false;
}
int queue::getLength(){
	return length;
}
list_value* queue::getHead(){
	return head;
}
bool queue::push(list_value *val){
	if (val == NULL)
		return false;
	if (queueEmpty()){
		head = val;
		body = head;
	}
		
	else{
		body->next = val;
		val->next = NULL;
		body = val;
	}
	body->next = NULL;
	
	/*auto v = new list_value();
	v->x = val->x;
	v->y = val->y;
	body->next = v;
	v->next = NULL;
	body = v;*/
	
	
	length++;
	return true;
}
list_value* queue::pop(){
	if (this->queueEmpty())
		return NULL;
	length--;
	
	list_value* val = head;
	//cocos2d::log("=======%d %d", val->x, val->y);
	head = head->next;
	return val;
}