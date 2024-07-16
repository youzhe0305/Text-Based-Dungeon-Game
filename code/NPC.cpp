#include "NPC.h"
#include <Windows.h>

void Trader::takeItem(Item* newItem) {
	for (Item* item : commodity) {
		if (item->getName() == newItem->getName()) {
			delete newItem;
			return;
		}
	}
	commodity.push_back(newItem);
}

void Trader::npcInit() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 100); // 食物商人, 藥水商人, 武器商人
	int dice = dist(gen);
	int type = 1;
	if (dice <= 50) type = 1;
	else if (50 < dice && dice <= 80) type = 2;
	else if (80 < dice) type = 3;
	if (type == 1) {
		traderType = "食物";
		while (commodity.size() < 3) { // 上限3
			Food* foodToAdd = new Food();
			foodToAdd->itemInit();
			takeItem(foodToAdd);
		}
	}
	else if (type == 2) {
		traderType = "藥水";
		while (commodity.size() < 3) {
			Drug* drugToAdd = new Drug();
			drugToAdd->itemInit();
			takeItem(drugToAdd);
		}
	}
	else if (type == 3) {
		traderType = "裝備";
		while (commodity.size() < 3) {
			Equipment* equipmentToAdd = new Equipment();
			equipmentToAdd->itemInit();
			takeItem(equipmentToAdd);
		}
	}
}

void Trader::printCommodity() {
	int idx = 1;
	for (Item* item : commodity) {
		cout << idx << ". " << item->getName() << " 價格: " << item->getPrice() << " | "<< item->getDescription() << endl;
		idx++;
	}
}

void Trader::playerBuy(Player& player) {
	cout << "您的金錢: " << player.getMoney() << endl;
	cout << "商品列表" << endl;
	cout << "0. 退出" << endl;
	printCommodity();
	cout << "請選擇要購買的商品: ";
	int option;
	cin >> option;
	if (option == 0) return;
	if (option < 0 || option > 3) {
		cout << "不要亂輸入!" << endl;
		return;
	}
	if (player.getMoney() < commodity[option - 1]->getPrice()) {
		cout << "沒錢就滾!!" << endl;
		return;
	}
	player.takeItem(commodity[option - 1]);
	cout << player.getName() << " 購買了 " << commodity[option - 1]->getName() << " 花費了 " << commodity[option - 1]->getPrice() << "元" << endl;
	player.addMoney(-commodity[option - 1]->getPrice());
}

void Trader::playerSell(Player& player) {
	cout << "請問你要販售什麼? 我們這裡可以用市價的一半向你收購喔" << endl;
	cout << "0. 退出" << endl;
	player.printBackpackWithPrice();
	cout << "請選擇要販售的商品: ";
	int option;
	cin >> option;
	if (option == 0) return;
	if (option < 0 || option > player.getBackpack().size()) {
		cout << "不要亂輸入!" << endl;
		return;
	}
	cout << player.getName() << " 出售了 " << player.getBackpack()[option - 1].first->getName() << " 獲得 " << int(player.getBackpack()[option - 1].first->getPrice() / 2) << "元" << endl;
	player.sellItem(option - 1);
}


void Trader::interact(Player& player) {
	system("cls");
	cout << "歡迎來到本店，這裡主要販售" << traderType << endl;
	cout << "你可以在這裡進行購買或販售物品" << endl;
	cout << "請輸入要執行的行動: 0. 退出 1. 購買 2. 販售: ";
	int option;
	cin >> option;
	if (option == 0) return;
	if (option == 1) playerBuy(player);
	if (option == 2) playerSell(player);
	
}


void Teacher::npcInit() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, teacherNum-1);
	int index = dist(gen);
	name = get<0>(teacherInfo[index]);
	skill = get<1>(teacherInfo[index]);
	chat = teacherChat[index];
}
void Teacher::interact(Player& player) {
	system("cls");
	cout << "不知道為什麼，你在地下城裡，巧遇了 " << name << endl;
	system("pause");
	for (string sentence : chat) {
		cout << sentence << endl;
		Sleep(2000);
	}
	player.addSkill(skill);
	cout << player.getName() << " 學會了 " << skill->getName() << endl;
}