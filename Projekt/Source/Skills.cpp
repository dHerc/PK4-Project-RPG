#include "Skills.h"

void Skills::Bind(int ID)
{
	switch (ID)
	{
	case 0:
		Archer.Bind();
		break;
	case 1:
		Warrior.Bind();
		break;
	case 2:
		Mage.Bind();
		break;
	case 3:
		Assasin.Bind();
		break;
	}
}



