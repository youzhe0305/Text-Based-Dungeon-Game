#include<iostream>
#include "Player.h"
#include "item.h"

using namespace std;

Food::Food(int index) {
	setName(get<0>(foodInfo[index]));
	setDescription(get<3>(foodInfo[index]));
	saturation = get<1>(foodInfo[index]);
	water = get<2>(foodInfo[index]);
	setPrice(get<4>(foodInfo[index]));

}

void Food::useItem(Player& player) {
	cout << player.getName() << " 食用了 " << getName() << endl;
	player.setHunger(player.getHunger() + saturation);
	if(saturation > 0) cout << " 增加 " << saturation << " 點飽食度" << endl;
	player.setThirst(player.getThirst() + water);
	if(water > 0) cout << " 增加 " << water << " 點口渴值" << endl;
}

void Food::itemInit() {
	random_device rd; 
	mt19937 gen(rd());  
	uniform_int_distribution<> dist(0, foodNum-1);
	int index = dist(gen);
	setName(get<0>(foodInfo[index]));
	setDescription(get<3>(foodInfo[index]));
	saturation = get<1>(foodInfo[index]);
	water = get<2>(foodInfo[index]);
	setPrice(get<4>(foodInfo[index]));
}

Drug::Drug(int index) {
	setName(get<0>(drugInfo[index]));
	setDescription(get<4>(drugInfo[index]));
	hp = get<1>(drugInfo[index]);
	mp = get<2>(drugInfo[index]);
	buffClear = get<3>(drugInfo[index]);
	setPrice(get<5>(drugInfo[index]));
}

void Drug::useItem(Player& player) {
	cout << player.getName() << " 使用了 " << getName() << endl;
	player.addHp(hp);
	if (hp > 0) cout << " 增加 " << hp << " 點生命值" << endl;
	player.addMp(mp);
	if (mp > 0) cout << " 增加 " << mp << " 點魔力" << endl;
	if (buffClear) {
		player.clearBuff();
		cout << player.getName() << "感覺全身通暢，負擔都消失了" << endl;
	}
}
void Drug::itemInit() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, drugNum - 1);
	int index = dist(gen);
	setName(get<0>(drugInfo[index]));
	setDescription(get<4>(drugInfo[index]));
	hp = get<1>(drugInfo[index]);
	mp = get<2>(drugInfo[index]);
	buffClear = get<3>(drugInfo[index]);
	setPrice(get<5>(drugInfo[index]));
}

Equipment::Equipment(int index) {
	setName(get<0>(equipmentInfo[index]));
	setDescription(get<3>(equipmentInfo[index]));
	atk = get<1>(equipmentInfo[index]);
	def = get<2>(equipmentInfo[index]);
	setPrice(get<4>(equipmentInfo[index]));
}

void Equipment::operator = (Equipment& equipment2) {
	atk = equipment2.atk;
	def = equipment2.def;
	setName(equipment2.getName());
	setDescription(equipment2.getDescription());
}

void Equipment::useItem(Player& player) {
	if (player.equipment.getName() == "") {
		player.equipment = *this;
		player.addAtk(atk);
		player.addDef(def);
		cout << player.getName() << " 裝備了 " << getName() << endl;
	}
	else {
		Equipment* retBackpackItem = new Equipment;
		*retBackpackItem = player.equipment;
		player.addAtk(-retBackpackItem->atk);
		player.addDef(-retBackpackItem->def);
		player.takeItem(retBackpackItem);
		cout << player.getName() << " 脫下了 " << retBackpackItem->getName() << endl;
		player.equipment = *this;
		player.addAtk(atk);
		player.addDef(def);
		cout << player.getName() << " 裝備了 " << getName() << endl;
	}
}

void Equipment::itemInit() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, equipmentNum - 1);
	int index = dist(gen);
	setName(get<0>(equipmentInfo[index]));
	setDescription(get<3>(equipmentInfo[index]));
	atk = get<1>(equipmentInfo[index]);
	def = get<2>(equipmentInfo[index]);
	setPrice(get<4>(equipmentInfo[index]));
}
