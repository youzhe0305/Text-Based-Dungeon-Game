#include "SystemManager.h"
using namespace std;


signed main() {
	SystemManager sm;
	sm.initDungeon();
	
	sm.initPlayer();
	while (1) {
		system("cls");
		sm.printPlayerStatus();
		sm.printMap();
		sm.printRoomStatus();
		sm.activateActionMenu();
	}

}