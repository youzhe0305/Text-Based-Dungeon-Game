#include<cmath>
#include "Creature.h"

void Creature::initValue() {
	maxHp = baseHp * pow(1.4, level - 1); // 1 base
	hp = maxHp;
	maxMp = baseMp * pow(1.5, level - 1);
	mp = maxMp;
	atk = baseAtk * pow(1.2, level - 1);
	def = baseDef * pow(1.2, level - 1);
}

Creature::Creature(string newName, int newBaseHp, int newBaseAtk, int newBaseDef, int newBaseMp, int newLevel)
:name(newName), baseHp(newBaseHp), baseAtk(newBaseAtk), baseDef(newBaseDef), baseMp(newBaseMp), level(newLevel) {
	initValue();

}

void Creature::initMul() {
	hurtMul = 1.0;
	atkMul = 1.0;
	defMul = 1.0;
}

void Creature::setThirst(int newThirst) {
	if (newThirst > maxThisrt) thirst = maxThisrt;
	else if (newThirst < 0) thirst = 0;
	else thirst = newThirst;
}
void Creature::setHunger(int newHunger) {
	if (newHunger > maxHunger) hunger = maxHunger;
	else if (newHunger < 0) hunger = 0;
	else hunger = newHunger;
}

void Creature::setBuff(int buffType, int stack){
	buffStatue[buffType] += stack;
}

void Creature::printSkillList() {
	int idx = 1;
	for (Skill* skill : skillList) {
		cout << idx << ". " << skill->getName() << ": " << skill->getMpCost() << " mp | " << skill->getDescription() << endl;
		idx++;
	}
}


void Creature::applyBuff() {
	buffStatue[Buff::HUNGER] = hunger <= 0 ? 1 : 0;
	buffStatue[Buff::THIRST] = thirst <= 0 ? 1 : 0;
	initMul();
	if (buffStatue[Buff::HUNGER]) { // 飢餓: 血量一回合-5, 攻擊力 *0.75
		addHp(-5);
		atkMul *= 0.75;
		cout << name << " 飢餓到無法思考，攻擊力*0.75倍，受到5點傷害" << endl;
		system("pause");
	}
	if (buffStatue[Buff::THIRST]) { // 口渴: 血量一回合-5, 防禦力 *0.75
		addHp(-5);
		defMul *= 0.75;
		cout << name << " 口渴到視線模糊，防禦力*0.75倍，受到5點傷害" << endl;
		system("pause");
	}
	if (buffStatue[Buff::POISON]) { // 減去中毒*2的血量
		cout << name << " 身體內的毒液快速擴散，痛苦至極，受到"<< buffStatue[Buff::POISON] * 2 <<"點傷害" << endl;
		addHp(-buffStatue[Buff::POISON] * 2);
		buffStatue[Buff::POISON]--;
		system("pause");

	}
	if (buffStatue[Buff::FIREBUTTERFLY]) { // 蝶引來生專屬buff，1.5倍傷
		cout << name << " 的周圍環繞火之蝶，傷害提升1.5倍"<< endl;
		atkMul *= 1.5;
		buffStatue[Buff::FIREBUTTERFLY]--;
		system("pause");

	}
	if (buffStatue[Buff::STRONGPOISON]) { // 解不掉，固定10傷
		cout << name << " 身中不會減弱的劇毒，神智開始模糊，受到固定" << 10 << "點傷害" << endl;
		addHp(-10);
		system("pause");
	}
}

void Creature::addSkill(Skill* newSkill) { 
	for (Skill* skill : skillList) 
		if (skill->getName() == newSkill->getName()) return;
	skillList.push_back(newSkill); 
}

void Creature::clearBuff() {
	for (int i = 0; i < buffNum; i++) {
		buffStatue[i] = 0;
	}
}
void Creature::creatureHeal() {
	hp = maxHp;
	mp = maxMp;
	hunger = maxHunger;
	thirst = maxThisrt;
	clearBuff();
}