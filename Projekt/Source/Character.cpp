#include "Character.h"

void Character::Draw()
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	Attack();
	if (turn_right)
	{
		if(attack==0&&side_attack==0)
			texture_r.Bind();
		else if(attack>0 && attack <= 20)
			attack_right_1.Bind();
		else if(attack>20 && attack <= 40)
			attack_right_2.Bind();
		else if(attack>40 && attack <= 60)
			attack_right_3.Bind();
		else if(attack>60 && attack <= 90)
			attack_right_4.Bind();
		else
			attack_right_5.Bind();
		if (side_attack != 0)
		{
			if (side_attack > 0 && side_attack <= 5)
				side_attack_right_1.Bind();
			else if (side_attack > 5 && side_attack <= 10)
				side_attack_right_2.Bind();
			else if (side_attack > 10 && side_attack <= 15)
				side_attack_right_3.Bind();
			else if (side_attack > 15 && side_attack <= 20)
				side_attack_right_4.Bind();
			else
				side_attack_right_5.Bind();
		}
	}
	else
	{
		if(attack==0&&side_attack==0)
			texture_l.Bind();
		else if (attack > 0 && attack <= 20)
			attack_left_1.Bind();
		else if (attack > 20 && attack <= 40)
			attack_left_2.Bind();
		else if (attack > 40 && attack <= 60)
			attack_left_3.Bind();
		else if (attack > 60 && attack <= 90)
			attack_left_4.Bind();
		else
			attack_left_5.Bind();
		if (side_attack != 0)
		{
			if (side_attack > 0 && side_attack <= 5)
				side_attack_left_1.Bind();
			else if (side_attack > 5 && side_attack <= 10)
				side_attack_left_2.Bind();
			else if (side_attack > 10 && side_attack <= 15)
				side_attack_left_3.Bind();
			else if (side_attack > 15 && side_attack <= 20)
				side_attack_left_4.Bind();
			else
				side_attack_left_5.Bind();
		}
	}
	shader.Bind();
	renderer.Draw(va, ib, shader);
	if (skill)
	{
		if (turn_right)
			effect_texture_right.Bind();
		else
			effect_texture_left.Bind();
		renderer.Draw(va, ib, shader);
	}

}
void Character::Attack()
{
	if (attack != 0)
		attack+=attack_speed;
	if (attack >= 160)
		attack = 0;
}

void Character::LvlUp()
{
	int tmp;
	while (exp >= 100)
	{
		exp -= 100;
		tmp = exp;
		tmp *= lvl;
		lvl++;
		tmp /= lvl;
		exp = tmp;
	}
}
