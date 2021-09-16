#include "Drops.h"
Drops::Drops(float& character_offset_x, float& character_offset_y, double pos_x, double pos_y, string path, int ID, Renderer& renderer, int init_type, int amount_or_itemID) :Entities(character_offset_x, character_offset_y, pos_x, pos_y, path, ID, renderer, true), amount_or_itemID(amount_or_itemID)
{
	switch (init_type)
	{
	case 0:
		type = healing;
		break;
	case 1:
		type = mana;
		break;
	case 2:
		type = sidearm_charge;
		break;
	case 3:
		type = gold;
		break;
	case 4:
		type = item;
		break;
	}
}
int Drops::GetType()
{
	return (int)type;
}

int Drops::GetAmountOrID()
{
	return amount_or_itemID;
}
