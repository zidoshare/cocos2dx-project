#include "LogicControl.h"

LogicControl::LogicControl()
{
}

LogicControl::~LogicControl()
{
}
bool LogicControl::init(){
	return true;
}

void LogicControl::setPlayer(Player* p){
	m_player = p;
}
