#ifndef _ROOM_
#define _ROOM_

#include "Monster.h"
#include "Player.h"
#include "TreasureBox.h"
#include "NPC.h"
#include<stdlib.h>
#include<random>
#include<time.h>

class Desert {
protected:
	void dry(Player& player);
	void sandStorm(Player& player);
	void oasis(Player& player); // 綠洲
};

class Forest {
protected:
	void insect(Player& player);
	void wildLife(Player& player);
	void lake(Player& player);
};

class Swamp {
protected:
	void poisonGas(Player& player);
};

class Room : public Desert, public Forest, public Swamp {
private:
	const int roomTypeNum = 2;
	vector<string> roomTypes = { "Normal", "Desert", "Forest", "Swamp" };
	int roomTypeIdx = -1;
	string roomType = "?";
	Monster* monster = NULL;
	TreasureBox* treasureBox = NULL;
	NPC* npc = NULL;
public:
	void roomInit(Player& player);
	void activateRoomEvent(Player& player);
	string getRoomType() const { return roomType; }
	Monster* getMonster() { return monster; }
	TreasureBox* getTreasureBox() const { return treasureBox; }
	NPC* getNPC() const { return npc; }
	void clearMonster() { monster = NULL; }
	void clearTreasureBox() { treasureBox = NULL; }
	void clearNPC() { npc = NULL; }
};


#endif // !_ROOM_

