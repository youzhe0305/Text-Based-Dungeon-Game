#ifndef _PLAYER_
#define _PLAYER_

#include "Creature.h"
#include "Item.h"
#include "TreasureBox.h"
using namespace std;

class Player : public Creature {
private:
	int exp = 0;
	int maxExp = 0;
	int money = 100;
	vector<pair<Item*, int>> backpack = {
		make_pair(new Food(0),3), make_pair(new Food(1), 3),
		make_pair(new Drug(0), 1), make_pair(new Drug(1), 1), };
		// make_pair(new Equipment(0),1), make_pair(new Equipment(2), 1) };
	Equipment equipment;
public:
	Player() {}
	Player(string name) : Creature(name, 300, 25, 10, 100, 1), maxExp(100) {}
	void operator= (Player player2);
	int getExp() const { return exp; }
	int getMaxExp() const { return maxExp; }
	int getMoney() const { return money; }
	vector<pair<Item*, int>>& getBackpack() { return backpack; }
	Equipment getEquipment() const { return equipment; }
	void levelup();
	void checkExp() { if (exp > maxExp) levelup(); }
	void obtainExp(int newExp) { exp += newExp; checkExp(); }
	void addMoney(int addVal) { money += addVal; }
	void takeItem(Item* newItem);
	void useBackpackItem(int index);
	void sellItem(int index);
	void printBackpack();
	void printBackpackWithPrice();
	friend void Equipment::useItem(Player& player);
};



#endif // !_PLAYER_
