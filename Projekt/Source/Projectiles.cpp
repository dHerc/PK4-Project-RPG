#include "Projectiles.h"

int Projectiles::Move(int world[1920][216])
{
	
	if (right)
	{
		if (world[(int)Get_x() + 1][(int)Get_y()])
			return world[(int)Get_x() + 1][(int)Get_y()];
		if (world[(int)Get_x() + 2][(int)Get_y()])
			return world[(int)Get_x() + 2][(int)Get_y()];
		Set_x(Get_x() + 2);
	}
	else
	{
		if (world[(int)Get_x() - 1][(int)Get_y()])
			return world[(int)Get_x() - 1][(int)Get_y()];
		if (world[(int)Get_x() - 2][(int)Get_y()])
			return world[(int)Get_x() - 2][(int)Get_y()];
		Set_x(Get_x() - 2);
	}
	return 0;
}

int Projectiles::GetDamage()
{
	return damage;
}
