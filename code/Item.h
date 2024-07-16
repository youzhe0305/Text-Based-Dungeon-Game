#ifndef _ITEM_
#define _ITEM_

#include<iostream>
#include <tuple>
using namespace std;

class Player;

class Item {
private:

	int price = 0;
	string name = "";
	string description = "";

public:
	string getName() const { return name; }
	void setName(string newName) { name = newName; }
	string getDescription() const { return description; }
	void setDescription(string newDescription) { description = newDescription; }
	int getPrice() const { return price; }
	void setPrice(int newPrice) { price = newPrice; }
	virtual void useItem(Player& player) {}
	virtual void itemInit() {};
};

class Food : public Item {
private:
	int saturation = 0;
	int water = 0;
	const int foodNum = 10;
	tuple<string, int, int, string, int> foodInfo[100] = {
		// name, saturation, water, description, price
		tuple<string, int, int, string, int>("黑麵包", 30, 0, "看起來會崩斷牙齒的硬麵包，飽食度+30", 20),
		tuple<string, int, int, string, int>("水袋", 0, 30, "稍微混濁的水裝在羊皮袋裡，口渴值+30", 20),
		tuple<string, int, int, string, int>("啤酒", 20, 20, "散發淡淡的小麥香，有液態麵包之稱，飽食度+20、口渴值+20", 50),
		tuple<string, int, int, string, int>("蜂蜜", 20, 10, "散發甜甜香氣的琥珀色液體，食用後會讓人感到幸福，飽食度+20、口渴值+10", 50),
		tuple<string, int, int, string, int>("熟牛肉", 50, 0, "江湖豪傑都愛的二斤熟牛肉，搭配啤酒將是絕配，飽食度+50", 80),
		tuple<string, int, int, string, int>("蘋果", 20, 20, "賢狼赫蘿的最愛，清脆的口感搭上四溢的甜香，讓人欲罷不能，飽食度+20，口渴值+20", 50),
		tuple<string, int, int, string, int>("煙燻乾酪", 30, 0, "傳統歐風美食，搭配麵包食用更佳，飽食度+30", 30),
		tuple<string, int, int, string, int>("蓮花酥", 40, 0, "璃月傳統點心，外型有如花瓣綻開於掌心，包裹在酥炸外皮中的是香甜軟糯的內餡，飽食度+40", 100),
		tuple<string, int, int, string, int>("吻仔魚丼飯", 60, 30, "讓大天使虹夏念念不忘的江之島美食，鮮味綻放在口中時，就像倘佯在大海中，飽食度+60，口渴值+30", 300),
		tuple<string, int, int, string, int>("自製可樂", 0, 50, "氣泡在舌尖跳動，嚥入喉頭讓全身透心涼，能讓詐欺師淺霧幻背叛的飲品，口渴值+50", 80),
	};	
public:
	Food() : Item() {}
	Food(int index);
	void useItem(Player& player) override;
	void itemInit() override;
};

class Drug : public Item {
private:
	int hp = 0;
	int mp = 0;
	bool buffClear = false;
	const int drugNum = 5;
	tuple<string, int, int, bool, string, int> drugInfo[100]{ // name, hp, mp, buffClear, description
		tuple<string, int, int, bool, string, int>("治療藥水", 60, 0, false, "民間製藥術做成的治療藥水，生命值+60", 50),
		tuple<string, int, int, bool, string, int>("高級治療藥水", 150, 0, false, "大陸魔法協會調製的治療藥水，生命值+150", 120),
		tuple<string, int, int, bool, string, int>("魔力藥水", 50, 0, false, "民間製藥術做成的魔力藥水，魔力+50", 50),
		tuple<string, int, int, bool, string, int>("高級魔力藥水", 0, 120, false, "大陸魔法協會調製的魔力藥水，魔力+150", 120),
		tuple<string, int, int, bool, string, int>("淨化藥水", 0, 0, true, "聖堂牧師加持的藥水，可以清除身上的buff與debuff", 100)
	};
public:
	Drug() : Item() {}
	Drug(int index);
	void useItem(Player& player) override;
	void itemInit() override;
};

class Equipment : public Item { // 目前只實作武器的部分
public:
	int atk = 0;
	int def = 0;
	const int equipmentNum = 10;
	tuple<string, int, int, string, int> equipmentInfo[100]{
		tuple<string, int, int, string, int>("鐵劍", 10, 0, "鐵制長劍，攻擊力+10", 100),
		tuple<string, int, int, string, int>("木盾", 0, 10, "木製盾牌，防禦力+10", 100),
		tuple<string, int, int, string, int>("輕便拳套", 5, 5, "皮製拳套，攻擊力+5、防禦力+5", 100),
		tuple<string, int, int, string, int>("白狼銀劍", 15, 10, "利維亞的傑洛特的寶劍，專門用來對付怪物，冷冽的銀氣將成為怪物的恐懼，攻擊力+15、防禦力+10", 400),
		tuple<string, int, int, string, int>("打狗棒", 15, 10, "丐幫幫主的象徵，用青竹製成的竹棒，質地柔韌，能使用靈活的打法，攻擊力+15、防禦力+10", 400),
		tuple<string, int, int, string, int>("破油紙扇", 15, 0, "妙手書生朱聰的兵器，能精準擊中敵方穴位，攻擊力+15", 200),
		tuple<string, int, int, string, int>("誓約勝利之劍(咖哩棒)", 50, 20, "呆毛王的聖劍，將使用者的魔力變換為光從劍尖放出，能夠一刀斬毀城池，攻擊力+40、防禦力+20", 1500),
		tuple<string, int, int, string, int>("星空太刀", 15, 5, "用搔鳥的鱗與喙製成的輕而堅的太刀，攻擊力+15、防禦力+5", 300),
		tuple<string, int, int, string, int>("噴射大劍", 25, 15, "傳奇獵人使用的大劍，透過噴射動力加速斬擊，能劈碎所有東西，攻擊力+25、防禦力+15", 800),
		tuple<string, int, int, string, int>("逐暗者與闡釋者", 30, 10, "黑衣劍士不小心落下的雙刀，能夠大幅發揮使用者的能力，攻擊力+30、防禦力+10", 800),
	};
public:
	Equipment() : Item() {}
	Equipment(int index);
	void operator = (Equipment& equipment2);
	void useItem(Player& player) override;
	void itemInit() override;
};

#endif // !1_ITEM_


