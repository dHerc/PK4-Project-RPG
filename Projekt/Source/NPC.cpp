#include "NPC.h"
NPC::NPC(float& character_offset_x, float& character_offset_y, double pos_x, double pos_y, string path, int ID, Renderer& renderer, int interactionID, int options[3]) :Entities(character_offset_x, character_offset_y, pos_x, pos_y, path, path, ID, renderer)
{
	menu_options[0] = options[0];
	menu_options[1] = options[1];
	menu_options[2] = options[2];
	switch (interactionID)
	{
	case 0:
		interaction = &NPC::no_interact;
		break;
	case 1:
		interaction = &NPC::open_mini_menu;
		break;
	}
}
bool NPC::Interact()
{
	return (this->*interaction)();
}

bool NPC::no_interact()
{
	return false;
}

bool NPC::open_mini_menu()
{
	return true;
}

int NPC::Get_menu_story()
{
	return menu_options[0];
}

int NPC::Get_menu_items()
{
	return menu_options[1];
}

int NPC::Get_menu_sidearm()
{
	return menu_options[2];
}
