#include "DataManager.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}
bool DataManager::init(){
	readData();
	return true;
}
void DataManager::readData(){
	for (int i = 0; i < 10; i++){
		hps.push_back(Value(i));
		attacks.push_back(Value(i));
		manas.push_back(Value(1));
		ranges.push_back(Value(i % 2 + 1));
	}
}
int* DataManager::getCardDataById(int id){
	int cards[4];

	cards[0] = hps.at(id).asInt();
	cards[1] = attacks.at(id).asInt();
	cards[2] = manas.at(id).asInt();
	cards[3] = ranges.at(id).asInt();
	return cards;
}
//通过id得到hp
int DataManager::getCardHpById(int id){
	return hps.at(id).asInt();
}
//通过id得到attack
int DataManager::getCardAttackById(int id){
	return attacks.at(id).asInt();
}
//通过id得到mana
int DataManager::getCardManaById(int id){
	return manas.at(id).asInt();
}
int DataManager::getCardRangeById(int id){
	return ranges.at(id).asInt();
}