#ifndef _SKILL_
#define _SKILL_

#include<iostream>
#include <random>

using namespace std;

class Creature; // forward declaration

class Skill {
private:
	string name;
	string description;
	int mpCost;
public:
	Skill(string newName, string newDescription, int newMpCost) : name(newName), description(newDescription), mpCost(newMpCost) {  }
	string getName() const { return name; }
	string getDescription() const { return description; }
	int getMpCost() const { return mpCost; }
	virtual bool activateSkill(Creature& player, Creature& monster) = 0;
};

class NormalAttack : public Skill{
public:
	NormalAttack() : Skill("普通攻擊", "普通的攻擊", 0) {}
	bool activateSkill(Creature& player, Creature& monster) override;
};

class Impale : public Skill {
public:
	Impale() : Skill("穿刺攻擊", "貫穿防禦，無視防禦力的攻擊", 20) {}
	bool activateSkill(Creature& player, Creature& monster) override;
};

class PoisonFang : public Skill {
public:
	PoisonFang() : Skill("毒牙", "分泌毒素，使對方中毒+3", 20) {}
	bool activateSkill(Creature& player, Creature& monster) override;
};

class StrongPoisonFang : public Skill {
public:
	StrongPoisonFang() : Skill("劇毒牙", "分泌劇毒，使對方中劇毒", 30) {}
	bool activateSkill(Creature& player, Creature& monster) override;
};

class PreciseShooting : public Skill {
public:
	PreciseShooting() : Skill("精準射擊", "瞄準對方弱點，並一擊貫穿的招式，造成2倍的傷害", 30) {}
	bool activateSkill(Creature& player, Creature& monster) override;
};

class ButterflyLead : public Skill {
public:
	ButterflyLead() : Skill("蝶引來生", "飛舞的火之蝶與永不間斷的烈焰，將洗淨世間的不淨之物，獲得彼岸蝶舞buff 5 回合", 50) {}
	bool activateSkill(Creature& player, Creature& monster) override;
};

class DeadLance : public Skill {
public:
	DeadLance() : Skill("往生秘傳槍法", "往生堂代代相傳的槍法，用6連槍貫穿不淨之物", 50) {}
	bool activateSkill(Creature& player, Creature& monster) override;
};

class LightingFiveWhip : public Skill {
public:
	LightingFiveWhip() : Skill("閃電五連鞭", "馬保國大師秘傳的絕招，據說在遠處用氣功麻痺敵人，並造成大量傷害，然而實際並沒什麼用", 50) {}
	bool activateSkill(Creature& player, Creature& monster) override;
};

class Explosion :public Skill {
public:
	Explosion() : Skill("爆裂魔法", "紅魔族天才魔法使惠惠的獨門絕技，魔力越多可以製造越大的爆炸，但放完之後，魔力會歸零", 100) {}
	bool activateSkill(Creature& player, Creature& monster) override;
};

class StarBrustStream :public Skill {
public:
	StarBrustStream() : Skill("星爆氣流斬", "黑衣劍士的獨門絕技，用快還要更快的速度，10秒砍出16下，", 80) {}
	bool activateSkill(Creature& player, Creature& monster) override;
};

#endif // !_SKILL_
