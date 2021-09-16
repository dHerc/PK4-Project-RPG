#include "Owned.h"

void Owned::Add_item(Item it)
{
	shared_ptr<Item> p(new Item(it));
	switch (it.Get_type())
	{
	case 0:
		weapons.push_back(move(p));
		break;
	case 1:
		sidearms.push_back(move(p));
		break;
	case 2:
		armours.push_back(move(p));
		break;
	}
}
