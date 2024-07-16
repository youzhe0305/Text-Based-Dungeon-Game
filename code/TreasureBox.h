#ifndef _TREASURE_BOX_
#define _TREASURE_BOX_
#include "Item.h"

class Player;

class TreasureBox {
private:
	Item* contain;
public:
	void boxInit();
	void openBox(Player& player);
};

#endif // !_TREASURE_BOX_
