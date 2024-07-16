#ifndef _ARENA_
#define _ARENA_

#include "Player.h"
#include "Monster.h"

class Arena {
private:
	bool endGameInMiddle = false;
public:
	void printPlayerInfo(Player& player);
	void printMonsterSimpleInfo(Monster& monster);
	bool activatePlayerAction(Player& player, Monster& monster);
	void monsterAutoAction(Player& player, Monster& monster);
	void battle(Player& player, Monster& monster);


};


#endif // !_ARENA_
