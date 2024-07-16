#include "SystemManager.h"
#include "Creature.h"


void SystemManager::initDungeon() {
	
	dungeon.resize(100);
	for (int i = 1; i <= dungeonLength; i++) {
		dungeon[i].resize(100);
		for (int j = 1; j <= dungeonLength; j++) {
			//dungeon[i][j].roomInit(player); // 房間應該要進去才init，不應該在這裡就先init
			monsterMap[i][j] = -1;
		}
	}
	visitMap[1][1] = true;

}

bool SystemManager::checkPlayerWin() {
	for (int i = 1; i <= dungeonLength; i++) {
		for (int j = 1; j <= dungeonLength; j++) {
			if (monsterMap[i][j] == -1 || monsterMap[i][j] == 1) return false;
		}
	}
	return true;
}

void SystemManager::winGame() {
	system("cls");
	cout << "恭喜你通關地城~" << endl;
	system("pause");
	exit(0);
}


void SystemManager::initPlayer() {
	cout << "請輸入玩家名字: ";
	string name;
	cin >> name;
	player = Player(name);
	system("cls");
}

void SystemManager::printPlayerStatus() {
	cout << "玩家狀態欄(" << player.getName() << "):" << endl;;
	cout << "等級: " << player.getLevel() << " 經驗值: " << player.getExp() << "/" << player.getMaxExp() << endl;
	cout << "生命值: " << player.getHp() << "/" << player.getMaxHp() << " 魔力: " << player.getMp() << "/" << player.getMaxMp() << endl;
	cout << "飢餓值: " << player.getHunger() << "/" << player.getMaxHunger() << " 口渴值: " << player.getThirst() << "/" << player.getMaxThirst() << endl;
	cout << "攻擊力: " << player.getAtk() << " 防禦力: " << player.getDef() << endl;
	cout << "裝備: " << player.getEquipment().getName() << endl;
	cout << "金錢: " << player.getMoney() << endl;
	cout << "Buff: ";
	int* buffStatue = player.getBuffStatue();
	vector<string> buffName = player.getBuffName();
	for (int i = 0; i < buffName.size(); i++) {
		if (buffStatue[i] > 0) cout << buffName[i] << "<" << buffStatue[i] << "> ";
	}
	cout << endl;
	cout << endl;
}

void SystemManager::printRoomStatus() {
	
	cout << "房間概況:" << endl;
	Room& nowRoom = dungeon[playerPosY][playerPosX];
	if (nowRoom.getRoomType() == "?") nowRoom.roomInit(player); // 避免房間顯示炸掉，顯示前，至少先初始化一次
	cout << "環境: " << nowRoom.getRoomType() << endl;
	cout << "|-------------------------|" << endl;
	cout << "|                         |" << endl;
	cout << "|    ";
		
	if (nowRoom.getTreasureBox() == NULL) cout << "  ";
	else cout << "寶";
	cout << "              ";
	if (nowRoom.getMonster() == NULL) cout << "  ";
	else cout << "怪";
	cout<<"   |" << endl;
	cout << "|                         |" << endl;
	cout << "|                         |" << endl;
	cout << "|                 ";
	if (nowRoom.getNPC() == NULL) cout << "   ";
	else cout << "NPC";
	cout<< "     |" << endl;
	cout << "|                         |" << endl;
	cout << "|-------------------------|" << endl;
	cout << endl;
	if (nowRoom.getMonster() == NULL) {
		monsterMap[playerPosY][playerPosX] = 0;
	}
	if (checkPlayerWin()) winGame();
}

void SystemManager::printMap() {
	cout << "地圖( * 為玩家位置):" << endl;
	for (int i = 1; i <= dungeonLength;i++) {
		for (int j = 1; j <= dungeonLength; j++) {
			if (i == playerPosY && j == playerPosX)
				cout << "|*| ";
			else if (visitMap[i][j])
				cout << "|" << dungeon[i][j].getRoomType()[0]<<"| ";
			else
				cout << "|?| ";
		}
		cout << endl;
	}
}

bool SystemManager::playerMove(int direction) {
	if (direction == 1) {
		if (playerPosY <= 1) return false;
		playerPosY--;
	}
	else if (direction == 2) {
		if (playerPosY >= dungeonLength) return false;
		playerPosY++;
	}
	else if (direction == 3) {
		if (playerPosX <= 1) return false;
		playerPosX--;
	}
	else if (direction == 4) {
		if (playerPosX >= dungeonLength) return false;
		playerPosX++;
	}

	return true;
}

void SystemManager::activatePlayerMenu() {
	cout << "1. 開啟背包" << endl;
	cout << "2. 開啟技能列表" << endl; // 待完成
	int option;
	cin >> option;
	if (option == 1) {
		system("cls");
		cout << "背包物品: " << endl;
		cout << "0. 退出" << endl;
		player.printBackpack();
		cout << "請輸入要使用的物品: ";
		int itemOption;
		cin >> itemOption;
		player.useBackpackItem(itemOption-1); // 1 base
	}
	else if (option == 2) {
		system("cls");
		int idx = 1;
		cout << "技能列表: " << endl;
		player.printSkillList();
		system("pause");
	}
	else {
		cout << "不要亂輸入值阿阿阿!" << endl;
		return;
	}

}


void SystemManager::activateActionMenu(){

	Room& nowRoom = dungeon[playerPosY][playerPosX];
	
	cout << "0. 開啟選單" << endl;
	cout << "1. 移動" << endl;
	cout << "2. 攻擊怪物" << endl;
	cout << "3. 開啟寶箱" << endl;
	cout << "4. 與NPC對話" << endl;
	int option;
	cout << "請輸入要選擇的選項(1~4): ";
	cin >> option;
	if (option == 0) {
		activatePlayerMenu();
	}
	else if (option == 1) {
		int direction;
		cout << "0. 返回 1. 上 2. 下 3. 左 4. 右" << endl;
		cout << "請輸入要選擇的選項(1~4): ";
		cin >> direction;
		while (direction != 0 && direction != 1 && direction != 2 && direction != 3 && direction != 4) {
			cout << "不要亂輸入阿!!!" << endl;
			//cout << "1. 上 2. 下 3. 左 4. 右" << endl;
			cout << "請輸入要選擇的選項(1~4): ";
			cin >> direction;
		}
		if (direction == 0) return;
		while (!playerMove(direction)) {
			cout << "撞牆啦!!!"<<endl;
			//cout << "1. 上 2. 下 3. 左 4. 右" << endl;
			cout << "請輸入要選擇的選項(1~4): ";
			cin >> direction;
		}
		visitMap[playerPosY][playerPosX] = true;
		Room& nowRoom = dungeon[playerPosY][playerPosX];
		if (nowRoom.getRoomType() == "?") nowRoom.roomInit(player); // 邊移動邊做初始化
		nowRoom.activateRoomEvent(player);
		system("pause");
		return;
	}
	else if (option == 2) {
		if (nowRoom.getMonster() == NULL) {
			cout << "這個房間沒有怪物" << endl;
			Sleep(1000);
			return;
		}
		arena.battle(player, *nowRoom.getMonster());
		if ( nowRoom.getMonster()->getHp() <= 0) nowRoom.clearMonster();
		if (checkPlayerWin()) {
			winGame();
		}
	}
	else if (option == 3) {
		if (nowRoom.getTreasureBox() == NULL) {
			cout << "這個房間沒有寶箱" << endl;
			Sleep(1000);
			return;
		}
		nowRoom.getTreasureBox()->openBox(player);
		nowRoom.clearTreasureBox();
		system("pause");
	}
	else if (option == 4) {
		if (nowRoom.getNPC() == NULL) {
			cout << "這個房間沒有NPC" << endl;
			Sleep(1000);
			return;
		}
		nowRoom.getNPC()->interact(player);
		system("pause");
	}
	else {
		cout << "不要亂輸入值阿阿阿!" << endl;
		return;
	}

}
