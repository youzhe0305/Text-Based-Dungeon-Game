#include "Arena.h"
#include <random>
#include<stdlib.h>

void Arena::printPlayerInfo(Player& player) {
	cout << player.getName() << "(" << player.getLevel() << "):" << endl;
	cout << "生命值: " << player.getHp() << "/" << player.getMaxHp() << " 魔力: " << player.getMp() << "/" << player.getMaxMp() << endl;
	cout << "飢餓值: " << player.getHunger() << "/" << player.getMaxHunger() << " 口渴值: " << player.getThirst() << "/" << player.getMaxThirst() << endl;
	cout << "Buff: ";
	int* buffStatue = player.getBuffStatue();
	vector<string> buffName = player.getBuffName();
	for (int i = 0; i < buffName.size(); i++) {
		if (buffStatue[i] > 0) cout << buffName[i] << "<" << buffStatue[i] << "> ";
	}
	cout << endl;
	cout << "--------------------" << endl;
}
void Arena::printMonsterSimpleInfo(Monster& monster) {
	cout << monster.getName() << "(" << monster.getLevel() << "):" << endl;
	cout << "生命值: " << monster.getHp() << "/" << monster.getMaxHp() << endl;
	cout << "Buff: ";
	int* buffStatue = monster.getBuffStatue();
	vector<string> buffName = monster.getBuffName();
	for (int i = 0; i < buffName.size(); i++) {
		if (buffStatue[i] > 0) cout << buffName[i] << "<" << buffStatue[i] << "> ";
	}
	cout << endl;
	cout << "--------------------" << endl;
}

bool Arena::activatePlayerAction(Player& player, Monster& monster) {

	cout << "1. 使用技能" << endl;
	cout << "2. 使用物品" << endl;
	cout << "3. 逃跑" << endl;
	cout << "請輸入要執行的動作(1~3): " << endl;
	int option;
	cin >> option;
	while (option != 1 && option != 2 && option != 3) {
		cout << "不要亂輸入阿~" << endl;
		cout << "請輸入要執行的動作(1~3): " << endl;
		cin >> option;
	}
	if (option == 1) {
		cout << "0. 返回" << endl;
		player.printSkillList();
		int skillOption;
		cout << "請輸入要使用的的技能編號(0~"<<player.getSkillList().size()<<"): ";
		cin >> skillOption;
		if (skillOption == 0) return false; // 直接重跑一回合
		if (skillOption < 0 || skillOption > player.getSkillList().size()) {
			cout << "技能不存在" << endl;
			system("pause");
			return false;
		}
		if (player.getSkillList()[skillOption - 1]->getMpCost() > player.getMp()) {
			cout << "魔力不足" << endl;
			system("pause");
			return false;
		}
		player.getSkillList()[skillOption - 1]->activateSkill(player, monster); // 1 base
		return true;
	}
	else if (option == 2) {
		cout << "0. 返回" << endl;
		player.printBackpack();
		cout << "請輸入要使用的的物品編號(0~" << player.getBackpack().size() << "): ";
		int backpackOption;
		cin >> backpackOption;
		if (backpackOption == 0) return false;
		if (backpackOption < 0 || backpackOption > player.getBackpack().size()) {
			cout << "物品不存在" << endl;
			system("pause");
			return false;
		}
		player.useBackpackItem(backpackOption - 1);
		return true; // 使用物品
	}
	else if (option == 3) {
		endGameInMiddle = true;
		return false; // 逃跑
	}
}

void Arena::monsterAutoAction(Player& player, Monster& monster) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, monster.getSkillList().size()-1);
	int option = dist(gen);
	while (monster.getSkillList()[option]->getMpCost() > monster.getMp()) option = dist(gen);
	monster.getSkillList()[option]->activateSkill(monster, player);

}

void Arena::battle(Player& player, Monster& monster) {

	endGameInMiddle = false;
	bool buffActive = false;
	while (!player.deathCheck() && !monster.deathCheck()) {
		if (endGameInMiddle == true) {
			monster.monsterHeal();
			cout << "逃跑成功" << endl;
			system("pause");
			return;
		}
		if (buffActive == false) {
			system("cls");
			printPlayerInfo(player); // BUFF 啟用
			printMonsterSimpleInfo(monster);
			player.applyBuff();
			if (player.deathCheck()) break;
			monster.applyBuff();
			if (monster.deathCheck()) break;
			buffActive = true;
		}
		system("cls"); 
		printPlayerInfo(player); // 戰鬥啟用
		printMonsterSimpleInfo(monster);
		if (!activatePlayerAction(player, monster)) continue;
		if (monster.deathCheck()) break;
		system("pause");
		monsterAutoAction(player, monster);
		system("pause");
		buffActive = false;
	}
	if (player.deathCheck()) {
		system("cls");
		for (int i = 1; i <= 10; i++)  cout << "Death~" << endl;
		system("pause");
		exit(0);
	}
	else {
		system("pause");
		system("cls");
		printPlayerInfo(player);
		printMonsterSimpleInfo(monster);
		cout << "勝利!!!" << endl;
		cout << "獲得" << monster.getDropExp() << "點經驗值" << endl;
		player.obtainExp(monster.getDropExp()); // bug
		// 技能獲取
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> distDrop(1, 100);
		if ( distDrop(gen) <= 20 ) { // 30% 機率會得到怪物技能
			uniform_int_distribution<> distSkill(1, monster.getSkillList().size() - 1);
			Skill* skillToAdd = monster.getSkillList()[distSkill(gen)];
			string skillName = skillToAdd->getName();
			player.addSkill(skillToAdd);
			cout << "從 " << monster.getName() << " 身上學會了 " << skillName << endl;;
		}
	}
	system("pause");
}
