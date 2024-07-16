#ifndef _SYSTEM_MANAGER_
#define _SYSTEM_MANAGER_

#include <iostream>
#include <windows.h>
#include "Room.h"
#include "Player.h"
#include "Monster.h"
#include "Arena.h"


class SystemManager {

private:
	
	vector<vector<Room>> dungeon;
	const int dungeonLength = 5;
	Player player;
	int playerPosX = 1, playerPosY = 1;
	bool visitMap[100][100];
	int monsterMap[100][100]; // -1未探索 0 無怪物 1 有怪物
	Arena arena;

public:
    void initDungeon();
	void initPlayer();
	bool checkPlayerWin();
	void printPlayerStatus();
	void printRoomStatus();
	void printMap();
	bool playerMove(int direction);
	void activatePlayerMenu();
	void activateActionMenu();
	void winGame();

};


#endif // !_SYSTEM_MANAGER_