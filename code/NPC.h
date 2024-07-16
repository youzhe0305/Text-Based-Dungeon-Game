#ifndef _NPC_

#include "Player.h";
#include "Item.h"
#include "Skill.h"

class NPC {
protected:
	string name;
public:
	virtual void npcInit() {};
	virtual void interact(Player& player) {}
};

class Trader : public NPC {

private:
	string traderType;
	vector<Item*> commodity;
public:
	void takeItem(Item* newItem);
	void npcInit();
	void printCommodity();
	void playerBuy(Player& player);
	void playerSell(Player& player);
	void interact(Player& player) override;
};

class Teacher : public NPC {
private:
	Skill* skill;
	vector<string> chat;
	const int teacherNum = 3;
	tuple<string, Skill*> teacherInfo[100]{ // name skill
		tuple<string, Skill*>("馬保國", new LightingFiveWhip()),
		tuple<string, Skill*>("惠惠", new Explosion()),
		tuple<string, Skill*>("桐人", new StarBrustStream()),
	};
	vector<string> teacherChat[100]{
		{"喔，這鬼地方居然還有人", "跟你說阿，我可是渾元形意太極門的掌門人，這個地下城裡的怪物，一個接化發，他們都得倒下","看在有緣的份上，我就教你我的獨門絕招，閃電五連鞭吧" ,},
		{"汝等何人？退到吾身後。", "吾名惠惠。紅魔族首屈一指的魔法師，操縱爆裂魔法之人。", "好好見識吾之力量吧！爆裂魔法！", "(前面的一隻蜘蛛瞬間被轟得灰飛煙滅)", "啊…不好意思，能揹我到安全處嗎…", "用完爆裂魔法，我就沒體力再站起來了…", "(背到安全處後…)", "感謝你的出手相助，就讓我來教教你，最偉大的魔法，爆裂魔法吧!"},
		{"小心!!!", "(桐人你撲倒，同時一支箭從你頭頂飛過)", "你可要注意點阿，這雖然是遊戲，但可不是鬧著玩的", "(語畢，桐人衝向骷髏弓箭手)", "當我拔出第二把劍，所有人都必須倒下", "摸頭還要哭! 星爆氣流斬!!!", "(一陣亂劍過後，怪物應聲倒下)", "我看你一個人在這個地城走也挺不安全的，就讓我教你最快的絕招吧"}
	};

public:
	void npcInit();
	void interact(Player& player) override;
};

#endif // !_NPC_
