#ifndef _MONSTER_
#define _MONSTER_
#include<iostream>
#include<string>
#include <tuple>
#include<stdlib.h>
#include<random>
#include<time.h>
#include "Creature.h"
#include "Skill.h"
#include "Player.h"
using namespace std;

class Monster : public Creature {
private:
	const int monsterNum = 5;
	tuple<string, int, int, int, int, int, string> monsterBaseInfo[100] = { 
		// name, baseHp, bsaeAtk, bsaeDef, baseMp, baseDropExp, description
		tuple<string, int, int, int, int, int, string>("殭屍", 100, 20, 10, 100, 30,
		"原本是冒險者，慘死於地城後，被地城的魔力侵蝕，成為了渴求啃食擁有魔力生物的行屍走肉"),

		tuple<string, int, int, int, int, int, string>("蜘蛛", 80, 25, 5, 80, 20,
		"在地城建造出來之前，就生存在地下的生物，因為被地城的魔力影響，體型逐漸變大，也變得嗜血"),
		
		tuple<string, int, int, int, int, int, string>("骷髏弓箭手", 60, 35, 5, 100, 30,
		"勇者的屍骨，被地城的魔力操縱，成為傀儡，在地城中遊蕩，到處狩獵其他冒險者"),

		tuple<string, int, int, int, int, int, string>("毒蛇", 60, 25, 5, 80, 20,
		"生活在地城縫隙中的生物，會在冒險者不注意時，突然衝出來咬冒險者一口，讓他身受劇毒"),

		tuple<string, int, int, int, int, int, string>("胡桃", 300, 40, 20, 500, 200,
		"往生堂第十七代堂主，來到地下城引領死去的冒險者"), 

		
	};
	vector<Skill*> monsterSkill[100] = {
		{new Impale()}, // 殭屍
		{new PoisonFang()}, // 蜘蛛
		{new PreciseShooting()}, // 骷髏弓箭手
		{new StrongPoisonFang()}, // 毒蛇
		{new ButterflyLead(), new DeadLance()} // 胡桃
	};
	int baseDropExp;
	int dropExp;
	string description;
public:
	Monster() : Creature() {}
	void monsterInit(Player player);
	int getDropExp()const { return dropExp; }
	string getDescription() const { return description; }
	void setBaseDropExp(int newBaseDropExp) { baseDropExp = newBaseDropExp; }
	void setDescription(string newDescription) { description = newDescription; }
	void monsterHeal() { creatureHeal(); };

};



#endif // !_PLAYER_
