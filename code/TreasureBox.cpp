#include "TreasureBox.h"
#include "Player.h"

void TreasureBox::boxInit() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 100);
	int dice = dist(gen);
	if (dice <= 20) {
		contain = new Equipment();
		contain->itemInit();
	}
	else if (20 < dice && dice <= 70) {
		contain = new Food();
		contain->itemInit();
	}
	else if (70 < dice && dice <= 100) {
		contain = new Drug();
		contain->itemInit();
	}
}

void TreasureBox::openBox(Player& player) {
	player.takeItem(contain);
	cout << player.getName() << " 打開了寶箱，得到了 " << contain->getName() << endl;
}