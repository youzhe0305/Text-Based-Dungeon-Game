#include "Player.h"


void Player::operator= (Player player2) {
	exp = player2.exp;
	maxExp = player2.maxExp;
	backpack = player2.backpack;
	money = player2.money;

	name = player2.name;
	baseHp = player2.baseHp; // 超參數
	hp = player2.hp;
	maxHp = player2.maxHp;
	baseAtk = player2.baseAtk; // 超參數
	atk = player2.atk;
	baseDef = player2.baseDef; // 超參數
	def = player2.def;
	baseMp = player2.baseMp; // 超參數
	mp = player2.mp;
	maxMp = player2.maxMp;
	hunger = player2.hunger;
	maxHunger = player2.maxHunger;
	thirst = player2.thirst;
	maxThisrt = player2.maxThisrt;
	level = player2.level; // attribute = baseAttribute * (1.1)^level
	hurtMul = player2.hurtMul; // 受傷倍數
	atkMul = player2.atkMul;
	defMul = player2.defMul;
	skillList = player2.skillList;
	//buffStatue[10] = player2.buffStatue;
}

void Player::levelup() {
	level++;
	exp = exp - maxExp;
	maxExp *= 1.3; // 怪物的exp掉落也會增加，所以倍率調高到1.2倍
	maxHp = baseHp * pow(1.5, level - 1); // 1 base
	hp = maxHp;
	maxMp = baseMp * pow(1.5, level - 1);
	mp = maxMp;
	atk = baseAtk * pow(1.2, level - 1);
	atk += equipment.atk;
	def = baseDef * pow(1.2, level - 1);
	def += equipment.def;
	cout << name << " 升級! 升到了 " << level << " 級!" << endl;
}

void Player::takeItem(Item* newItem) {
	for (pair<Item*, int>& item : backpack) {
		if (newItem->getName() == item.first->getName()) {
			item.second += 1;
			return;
		}
	}
	backpack.push_back(make_pair(newItem, 1));
}

void Player::useBackpackItem(int index) {
	if (index < 0 || index >= backpack.size()) {
		if (index == -1) return;
		cout << "物品不存在" << endl;
		system("pause");
		return;
	}
	backpack[index].first->useItem(*this);
	backpack[index].second--;
	if (backpack[index].second <= 0) backpack.erase(backpack.begin() + index);
	system("pause");
}

void Player::sellItem(int index) {
	money += backpack[index].first->getPrice() / 2;
	backpack[index].second--;
	if (backpack[index].second <= 0) backpack.erase(backpack.begin() + index);
}

void Player::printBackpack() {
	int idx = 1;
	for (pair<Item*, int>& item : backpack) {
		cout << idx << ". " << item.first->getName() << " X " << item.second << " | " << item.first->getDescription() << endl;
		idx++;
	}
}

void Player::printBackpackWithPrice() {
	int idx = 1;
	for (pair<Item*, int>& item : backpack) {
		cout << idx << ". " << item.first->getName() << " X " << item.second << "市價: " << item.first->getPrice() << " | " << item.first->getDescription() << endl;
		idx++;
	}
}