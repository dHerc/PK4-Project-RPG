#include "Item.h"
Item::Item(int stat1, int stat2, string name, int it_type, int item_class, int effectID) :item_texture("Resource/textures/" + name + ".png"), item_description("Resource/textures/" + name + "_desc.png"), path("Resource/textures/" + name + ".png"), desc_path("Resource/textures/" + name + "_desc.png"), item_class(item_class)
{
	stats[0] = stat1;
	stats[1] = stat2;
	switch (it_type)
	{
	case 0:
		type = Weapon;
		break;
	case 1:
		type = Sidearm;
		break;
	case 2:
		type = Armour;
		break;
	default:
		type = Nothing;
		break;
	}
	switch (effectID)
	{
	case 0:
		effect = &Item::no_effect;
		break;
	case 1:
		effect = &Item::bonus_damage_on_grass;
		break;
	}
}
Item::Item(const Item& it) :item_texture(it.path), item_description(it.desc_path), desc_path(it.desc_path), path(it.path), item_class(it.item_class), type(it.type)
{
	stats[0] = it.stats[0];
	stats[1] = it.stats[1];
	effect = it.effect;
}
int Item::Get_type()
{
	return (int)type;
}

int Item::Get_class()
{
	return item_class;
}

int Item::Get_first_stat()
{
	return stats[0];
}

int Item::Get_seccond_stat()
{
	return stats[1];
}

void Item::Bind_texture()
{
	item_texture.Bind();
}

void Item::Bind_description()
{
	item_description.Bind();
}

void Item::Trigger(int char_pos[2], int world[1920][216]
	, Character& character, bool mode)
{
	(this->*effect)(char_pos, world,character,mode);
}

void Item::no_effect(int char_pos[2], int world[1920][216], Character &character,bool mode)
{
}

void Item::bonus_damage_on_grass(int char_pos[2], int world[1920][216], Character &character,bool mode)
{
	if (mode)
	{
		if (world[char_pos[0]][char_pos[1] - 1] == 1)
		{
			character.bonus_damage += stats[0] / 2;
			triggered = true;
		}
	}
	else
	{
		if (triggered)
		{
			character.bonus_damage -= stats[0] / 2;
			triggered = false;
		}
	}
}

