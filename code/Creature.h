#ifndef _CREATURE_
#define _CREATURE_

#include<iostream>
#include<vector>
#include "skill.h"
using namespace std;


class Creature {

protected:
	string name = "?";
	int baseHp = 0; // 超參數
	int hp = 0;
	int maxHp = 0;
	int baseAtk = 0; // 超參數
	int atk = 0;
	int baseDef = 0; // 超參數
	int def = 0;
	int baseMp = 0; // 超參數
	int mp = 0;
	int maxMp = 0;
	int hunger = 100;
	int maxHunger = 100;
	int thirst = 100;
	int maxThisrt = 100;
	int level = 1; // attribute = baseAttribute * (1.1)^level
	float hurtMul = 1.0; // 受傷倍數
	float atkMul = 1.0;
	float defMul = 1.0;
	vector<Skill*> skillList = {new NormalAttack()};
	vector<string> buffName = { "飢餓", "口渴", "中毒", "彼岸蝶舞", "劇毒"};
	int buffStatue[10] = {0,0,0,0,0};
public:
	Creature() {}
	Creature(string newName, int newBaseHp, int newBaseAtk, int newBaseDef, int newBaseMp, int newLevel);
	const int buffNum = 5;
	enum Buff { HUNGER, THIRST, POISON, FIREBUTTERFLY, STRONGPOISON };

	string getName() const { return name; }
	int getHp() const { return hp; }
	int getMaxHp() const { return maxHp; }
	int getAtk() const { return atk; }
	int getDef() const { return def; }
	int getMp() const { return mp; }
	int getMaxMp() const { return maxMp; }
	int getHunger() const { return hunger; }
	int getMaxHunger() const { return maxHunger; }
	int getThirst() const { return thirst; }
	int getMaxThirst() const { return maxThisrt; }
	int getLevel() const { return level; }
	float getHurtMul() const{ return hurtMul; }
	float getAtkMul() const { return atkMul; }
	float getDefMul() const { return defMul; }
	vector<Skill*>& getSkillList() { return skillList; }
	vector<string> getBuffName() { return buffName; }
	int* getBuffStatue() { return buffStatue; }
	
	void addHp(int addVal) { hp += addVal; hp = hp >= 0 ? hp : 0;  hp = hp <= maxHp ? hp : maxHp;}
	void addMp(int addVal) { mp += addVal; mp = mp >= 0 ? mp : 0;  mp = mp <= maxMp ? mp : maxMp;}
	void addAtk(int addVal) { atk += addVal; }
	void addDef(int addVal) { def += addVal; }
	void setName(string newName) { name = newName; }
	void setBaseValue(int newBaseHp, int newBaseAtk, int newBaseDef, int newBaseMp) { 
		baseHp = newBaseHp; baseAtk = newBaseAtk; baseDef = newBaseDef; baseMp = newBaseMp; 
	}
	void setThirst(int newThirst);
	void setHunger(int newHunger);
	void setLevel(int newLevel) { level = newLevel; }
	void setBuff(int buffType, int stack);

	void initValue();
	void initMul();
	void applyBuff();
	void addSkill(Skill* newSkill);
	void printSkillList();
	bool deathCheck() { return !(hp > 0); } // true -> death
	void clearBuff();
	void creatureHeal();
};

#endif // !_CREATURE_
