#include "Room.h"


void Desert::dry(Player& player) {
	player.setThirst(player.getThirst() - 50);
	cout << player.getName() << " 被沙漠中的烈日侵襲，身體大量喪失水分，損失 50點 口渴值" << endl;
};
void Desert::sandStorm(Player& player) {
	player.addHp(-30);
	cout << player.getName() << " 受到了沙塵暴的侵襲，損失了30點血量" << endl;
}
void Desert::oasis(Player& player) {
	player.addMp(50);
	player.setThirst(player.getThirst() + 20);
	cout << player.getName() << " 遇見了綠洲，綠洲的四周長滿了以魔力維生的植物" << endl;
	cout << player.getName() << " 喝了一口水，感覺全身通滿了魔力，恢復了 50 點魔力及 20 點口渴值" << endl;
}

void Forest::insect(Player& player) {
	player.setBuff(Creature::Buff::POISON, 1);
	cout << player.getName() << " 被毒蟲咬傷，中毒+1" << endl;
}
void Forest::wildLife(Player& player) {
	player.addHp(-30);
	cout << player.getName() << " 被蟒蛇咬傷，損失了30點血量" << endl;
}
void Forest::lake(Player& player) {
	player.setThirst(player.getThirst() + 20);
	cout << player.getName() << " 遇見了清澈的湖泊，喝了一口水，恢復了 20 點口渴值" << endl;
}

void Swamp::poisonGas(Player& player) {
	player.setBuff(Creature::Buff::POISON, 2);
	cout << player.getName() << " 吸入了有毒的沼氣，中毒+2" << endl;
}

void Room::roomInit(Player& player) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist1(0, 3);
	uniform_int_distribution<> dist2(1, 100);

	int index = dist1(gen);
	roomType = roomTypes[index];
	roomTypeIdx = index;
	int monsterHappenRate = dist2(gen);
	if (monsterHappenRate <= 70) { 
		monster = new Monster;
		monster->monsterInit(player);
	}
	int treasureBoxHappenRate = dist2(gen);
	if (treasureBoxHappenRate <= 50) {
		treasureBox = new TreasureBox;
		treasureBox->boxInit();
	}
	int npcHappenRate = dist2(gen);
	if (npcHappenRate <= 40) {
		int typeRate = dist2(gen);
		
		if (typeRate <= 30) {// 30%
			npc = new Teacher;
			npc->npcInit();
		}
		else if (30 < typeRate && typeRate <= 100) { // 70%
			npc = new Trader;
			npc->npcInit();
		}

	}
	

}

void Room::activateRoomEvent(Player& player) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 100);
	int dice = dist(gen);
	if (roomTypeIdx == 0) {
		cout << player.getName() << " 進入了普通的房間" << endl;
	}
	else if (roomTypeIdx == 1) {
		cout << player.getName() << " 進入了黃沙滿布的的房間" << endl;
		if (dice <= 20) oasis(player);
		if (20 < dice && dice <= 80) dry(player);
		if (40 <= dice && dice <= 60) sandStorm(player);
	}
	else if (roomTypeIdx == 2) { 
		cout << player.getName() << " 進入了綠意盎然的房間" << endl;
		if (dice <= 20) insect(player);
		if (20 < dice && dice <= 50) wildLife(player);
		if (dice >= 80) lake(player);
	}
	else if (roomTypeIdx == 3) {
		cout << player.getName() << " 一腳踏入了爛泥" << endl;
		if (dice <= 50) poisonGas(player);
	}
}