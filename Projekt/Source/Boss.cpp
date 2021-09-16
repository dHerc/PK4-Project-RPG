#include "Boss.h"
Boss::Boss(float& character_offset_x, float& character_offset_y, double pos_x, double pos_y, string pathl, string pathr, int ID, Renderer& renderer, int hp, int dmg, int exp, int gold, int lvl, int move_patern, int attack_patern, int trigger_type) :Enemies(character_offset_x, character_offset_y, pos_x, pos_y, pathl, pathr, ID, renderer, hp, dmg, exp, gold, lvl, move_patern, attack_patern)
{
	switch (trigger_type)
	{
	case 1:
		trigger = &Boss::DarkMage;
		break;
	}
}
bool Boss::Trigger(Character & character)
{
	return (this->*trigger)(character);
}

bool Boss::DarkMage(Character& character)
{
	cycle++;
	if (cycle == 120)
		character.health -= 50;
	if (cycle == 240)
	{
		if(character.mana>=20)
			character.mana -= 20;
		else
			character.mana = 0;
	}
	if (cycle == 360)
		return 1;
	if (cycle == 480)
	{
		if (character.side_amount)
			character.side_amount -= 1;
	}
	if (cycle == 600)
	{
		character.health -= 50;
		cycle = 0;
	}
	return 0;
}

