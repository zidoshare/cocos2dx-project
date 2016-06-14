#include "TimerHand.h"

bool TimerHand::init(){
	return true;
}
void TimerHand::setTimer(bool func(int, int), int x1, int x2, float delay){
	auto f = &func;
}
void TimerHand::setTimer(void func(int), int, float delay){

}
void TimerHand::setTimer(void func(),float delay){

}

void TimerHand::update(float dt) {

}