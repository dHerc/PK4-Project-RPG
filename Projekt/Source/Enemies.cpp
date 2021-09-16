#include "Enemies.h"

Enemies::Enemies(float& character_offset_x, float& character_offset_y, double pos_x, double pos_y, string pathl, string pathr, int ID, Renderer& renderer, int hp, int dmg, int exp, int gold, int lvl, int move_patern, int attack_patern) :Entities(character_offset_x, character_offset_y, pos_x, pos_y, pathl, pathr, ID, renderer), Stats(hp, dmg, exp, gold, lvl)
{
	switch (move_patern)
	{
	case 0:
		movement = &Enemies::mov_still;
		break;
	case 1:
		movement = &Enemies::mov_basic;
		break;
	case 2:
		movement = &Enemies::mov_free;
	}
	switch (attack_patern)
	{
	case 0:
		attack = &Enemies::atk_disabled;
		break;
	case 1:
		attack = &Enemies::atk_basic;
		break;
	default:
		attack = &Enemies::atk_basic;
		break;
	}
};

void Enemies::Move(int char_pos[2], int world[1920][216])
{
	(this->*movement)(char_pos,world);
}

void Enemies::Attack(int char_pos[2],int & damage_taken)
{
	(this->*attack)(char_pos,damage_taken);
}

void Enemies::mov_still(int char_pos[2], int world[1920][216]
)
{
	return;
}

void Enemies::mov_basic(int char_pos[2], int world[1920][216])
{
	int under_feet = 0;
	for (int i = -2;i < 3;i++)
		under_feet += world[(int)Get_x() + i][(int)Get_y() - 2];
	if (under_feet == 0)
	{
		Set_y(Get_y() - 1);
	}
	if (char_pos[0] - Get_x() < 150 || Get_x() - char_pos[0] < 150)
	{
		if (Get_x() > char_pos[0] - 6 && world[(int)Get_x() - 5][(int)Get_y()] == 0)
		{
			Set_x(Get_x() - 0.1);
			right = 0;
		}
		if (Get_x() < char_pos[0] + 6 && world[(int)Get_x() + 4][(int)Get_y()] == 0)
		{
			Set_x(Get_x() + 0.1);
			right = 1;
		}
	}
}

void Enemies::mov_free(int char_pos[2], int world[1920][216])
{
	if (Get_x() > char_pos[0] - 6)
	{
		Set_x(Get_x() - 0.1);
		right = 0;
	}
	if (Get_x() < char_pos[0] + 6)
	{
		Set_x(Get_x() + 0.1);
		right = 1;
	}
	if (Get_y() > char_pos[1] - 6)
	{
		Set_y(Get_y() - 0.1);
		right = 0;
	}
	if (Get_y() < char_pos[1] + 6)
	{
		Set_y(Get_y() + 0.1);
		right = 1;
	}
}

void Enemies::atk_disabled(int char_pos[2], int & damage_taken)
{
	damage_taken = 0;
	return;
}

void Enemies::atk_basic(int char_pos[2], int & damage_taken)
{
	damage_taken = 0;
		if (Get_x() > char_pos[0] - 7 && Get_x() < char_pos[0] + 7)
		{
			if (Get_y() > char_pos[1] - 7 && Get_y() < char_pos[1] + 7)
				if (delay == 0)
				{
					damage_taken = damage;
					delay = 200;
				}
		}
	if(delay>0)
		delay-=attack_speed;
	return;
}
