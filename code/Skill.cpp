#include "Skill.h"
#include "Creature.h"
#include <windows.h>
// 基本計算公式 atk - def

bool NormalAttack::activateSkill(Creature& player, Creature& monster) {
	if (player.getMp() < getMpCost()) return false;
	player.addMp(-getMpCost());
	player.setHunger(player.getHunger() - 5);
	player.setThirst(player.getThirst() - 5);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(-5, 5);
	int hurtValue = player.getAtk() * player.getAtkMul() - monster.getDef() * monster.getDefMul();
	float Float = 1.0 - float(dist(gen)) * 0.01; // 95%~105%
	int hurtFloat = hurtValue * Float;
	int hurtReal = hurtFloat * monster.getHurtMul();
	monster.addHp(-hurtReal);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << endl;
	cout << "造成了 " << hurtReal << " 點傷害" << endl;
	return true;
}

bool Impale::activateSkill(Creature& player, Creature& monster) {
	if (player.getMp() < getMpCost()) return false;
	player.addMp(-getMpCost());
	player.setHunger(player.getHunger() - 5);
	player.setThirst(player.getThirst() - 5);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(-5, 5);
	int hurtValue = player.getAtk() * player.getAtkMul();
	float Float = 1.0 - float(dist(gen)) * 0.01; // 95%~105%
	int hurtFloat = hurtValue * Float;
	int hurtReal = hurtFloat * monster.getHurtMul();
	monster.addHp(-hurtReal);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << endl;
	cout << monster.getName() << " 身上被捅出了一個窟窿" << endl;
	cout << "造成了 " << hurtReal << " 點傷害" << endl;
	return true;
}

bool PoisonFang::activateSkill(Creature& player, Creature& monster) {
	if (player.getMp() < getMpCost()) return false;
	player.addMp(-getMpCost());
	player.setHunger(player.getHunger() - 5);
	player.setThirst(player.getThirst() - 5);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(-5, 5);

	int hurtValue = player.getAtk() * player.getAtkMul() - monster.getDef() * monster.getDefMul();
	float Float = 1.0 - float(dist(gen)) * 0.01; // 95%~105%
	int hurtFloat = hurtValue * Float;
	int hurtReal = hurtFloat * monster.getHurtMul();
	// cout << player.getName();
	monster.addHp(-hurtReal);
	monster.setBuff(Creature::Buff::POISON, 3);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << endl;
	cout << monster.getName() << " 變得腳步輕浮" << endl;
	cout << "造成了 " << hurtReal << " 點傷害" << endl;
	cout << "造成了 3 層中毒" << endl;
	return true;
}

bool StrongPoisonFang::activateSkill(Creature& player, Creature& monster) {
	if (player.getMp() < getMpCost()) return false;
	player.addMp(-getMpCost());
	player.setHunger(player.getHunger() - 5);
	player.setThirst(player.getThirst() - 5);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(-5, 5);

	int hurtValue = player.getAtk() * player.getAtkMul() - monster.getDef() * monster.getDefMul();
	float Float = 1.0 - float(dist(gen)) * 0.01; // 95%~105%
	int hurtFloat = hurtValue * Float;
	int hurtReal = hurtFloat * monster.getHurtMul();
	monster.addHp(-hurtReal);
	monster.setBuff(Creature::Buff::STRONGPOISON, 1);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << endl;
	cout << monster.getName() << " 開始晃頭晃腦" << endl;
	cout << "造成了 " << hurtReal << " 點傷害" << endl;
	cout << "造成了 1 層劇毒" << endl;
	return true;
}

bool PreciseShooting::activateSkill(Creature& player, Creature& monster) {
	if (player.getMp() < getMpCost()) return false;
	player.addMp(-getMpCost());
	player.setHunger(player.getHunger() - 5);
	player.setThirst(player.getThirst() - 5);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(-5, 5);
	int hurtValue = (player.getAtk() * player.getAtkMul() - monster.getDef() * monster.getDefMul() ) * 2;
	float Float = 1.0 - float(dist(gen)) * 0.01; // 95%~105%
	int hurtFloat = hurtValue * Float;
	int hurtReal = hurtFloat * monster.getHurtMul();
	monster.addHp(-hurtReal);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << endl;
	cout << "造成了 " << hurtReal << " 點傷害" << endl;
	return true;
}

bool ButterflyLead::activateSkill(Creature& player, Creature& monster) {
	if (player.getMp() < getMpCost()) return false;
	player.addMp(-getMpCost());
	player.setHunger(player.getHunger() - 5);
	player.setThirst(player.getThirst() - 5);
	player.setBuff(Creature::Buff::FIREBUTTERFLY, 5);
	cout << "蝶火燎原!" << endl;
	cout << player.getName() << " 獲得了5層彼岸蝶舞"<< endl;
	return true;
}

bool DeadLance::activateSkill(Creature& player, Creature& monster) {
	if (player.getMp() < getMpCost()) return false;
	player.addMp(-getMpCost());
	player.setHunger(player.getHunger() - 5);
	player.setThirst(player.getThirst() - 5);

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(-5, 5);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << endl;
	Sleep(500);
	for (int i = 1; i <= 6; i++) {
		int hurtValue = player.getAtk() * player.getAtkMul() * 0.9 - monster.getDef() * monster.getDefMul();
		float Float = 1.0 - float(dist(gen)) * 0.01; // 95%~105%
		int hurtFloat = hurtValue * Float;
		int hurtReal = hurtFloat * monster.getHurtMul();
		monster.addHp(-hurtReal);
		cout << "喝！ 第" << i << "槍" << endl;
		cout << "造成了 " << hurtReal << " 點傷害" << endl;
		Sleep(500);
	}
}


bool LightingFiveWhip::activateSkill(Creature& player, Creature& monster) {
	if (player.getMp() < getMpCost()) return false;
	player.addMp(-getMpCost());
	player.setHunger(player.getHunger() - 5);
	player.setThirst(player.getThirst() - 5);
	monster.addHp(-5);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << " 第一鞭" << endl;
	cout << "造成了 " << 1 << " 點傷害" << endl;
	Sleep(500);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << " 第二鞭" << endl;
	cout << "造成了 " << 1 << " 點傷害" << endl;
	Sleep(500);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << " 第三鞭" << endl;
	cout << "造成了 " << 1 << " 點傷害" << endl;
	Sleep(500);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << " 第四鞭" << endl;
	cout << "造成了 " << 1 << " 點傷害" << endl;
	Sleep(500);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << " 第五鞭" << endl;
	cout << "造成了 " << 1 << " 點傷害" << endl;
	return true;
}

bool Explosion::activateSkill(Creature& player, Creature& monster) {
	if (player.getMp() < getMpCost()) return false;
	int hurt = player.getMp() * 2;
	player.addMp(-player.getMp());
	player.setHunger(player.getHunger() - 5);
	player.setThirst(player.getThirst() - 5);

	monster.addHp(-hurt);
	cout << "向那比黑更黑比暗更暗的深淵，祈求吾之深紅閃光" << endl;
	Sleep(2000);
	cout << "覺醒之時已然降至，墮入無謬境界的真理啊，化作無窮的扭曲限界吧！" << endl;
	Sleep(2500);
	cout << "起舞吧，起舞吧，起舞吧！吾之魔力奔流所求之物即崩壞，無人能及之崩壞！" << endl;
	Sleep(2500);
	cout << "森羅萬象皆歸塵土，從深淵降臨吧" << endl;
	Sleep(2000);
	cout << "這是人類最大的攻擊手段，這正是最強的攻擊魔法" << endl;
	Sleep(2000);
	cout << "Explosion！" << endl;
	Sleep(1000);

	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << endl;
	cout << "造成了 " << hurt << " 點傷害" << endl;
}

bool StarBrustStream::activateSkill(Creature& player, Creature& monster) { // 70%砍16下
	if (player.getMp() < getMpCost()) return false;
	player.addMp(-getMpCost());
	player.setHunger(player.getHunger() - 5);
	player.setThirst(player.getThirst() - 5);

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(-5, 5);
	cout << player.getName() << " 對 " << monster.getName() << " 使用了 " << getName() << endl;
	Sleep(500);
	cout << "嗨壓哭！摸頭嗨壓哭！" << endl;
	Sleep(500);
	for (int i = 1; i <= 16; i++) {
		int hurtValue = player.getAtk() * player.getAtkMul() * 0.8 - monster.getDef() * monster.getDefMul() ;
		float Float = 1.0 - float(dist(gen)) * 0.01; // 95%~105%
		int hurtFloat = hurtValue * Float;
		int hurtReal = hurtFloat * monster.getHurtMul();
		monster.addHp(-hurtReal);
		cout << "第" << i << "斬" << endl;
		cout << "造成了 " << hurtReal << " 點傷害" << endl;
		Sleep(500);
	}
	
}