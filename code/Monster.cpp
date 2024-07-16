#include "Monster.h"
#include "Player.h"

void Monster::monsterInit(Player player) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist1(0, monsterNum-1);
	uniform_int_distribution<> dist2(-2, 2);
	int index = dist1(gen) % monsterNum;
	int levelDiff = dist2(gen); // 與玩家的等級差，-2 ~ 4
	setName(get<0>(monsterBaseInfo[index])); // name, baseHp, bsaeAtk, bsaeDef, baseMp, baseDropExp, description
	setBaseValue(get<1>(monsterBaseInfo[index]), get<2>(monsterBaseInfo[index]), get<3>(monsterBaseInfo[index]), get<4>(monsterBaseInfo[index]));
	setBaseDropExp(get<5>(monsterBaseInfo[index]));
	setLevel(player.getLevel() + levelDiff >= 1 ? player.getLevel() + levelDiff : 1);
	dropExp = baseDropExp * pow(1.4, level - 1);
	initValue();
	setDescription(get<6>(monsterBaseInfo[index]));
	for (Skill* skill : monsterSkill[index])
		addSkill(skill);
}


