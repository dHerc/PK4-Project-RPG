#pragma once

class Stats
{
public:
	int health;
	int max_health;
	int damage;
	int attack_speed = 5;
	int mana = 0;
	int max_mana = 0;
	int exp;
	int gold;
	int lvl;
	int side_damage = 0;
	int side_amount=0;
	int max_side_amount = 0;
	int damage_reduction = 0;
	int bonus_damage = 0;
	int char_class;
	int stacks = 0;
	Stats(int max_hp, int dmg, int exp, int gold, int lvl, int enemy_class = 0) :health(max_hp), max_health(max_hp), damage(dmg), exp(exp), gold(gold), lvl(lvl),char_class(enemy_class) {};
	Stats(int max_hp, int dmg,int max_mana,int max_side_amount,int side_dmg,int exp,int gold,int lvl,int char_class) :health(max_hp), max_health(max_hp), damage(dmg), mana(max_mana),max_mana(max_mana),max_side_amount(max_side_amount),side_damage(side_dmg), exp(exp),gold(gold),lvl(lvl),char_class(char_class) {};
};

