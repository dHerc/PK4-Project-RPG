#pragma once
#include "Graphic_engine/Graphic_engine.h"
class Skills
{
private:
	Texture Archer;
	Texture Warrior;
	Texture Mage;
	Texture Assasin;
public:
	Skills() :Archer("Resource/textures/Archer_skills.png"), Warrior("Resource/textures/Warrior_skills.png"), Mage("Resource/textures/Mage_skills.png"), Assasin("Resource/textures/Assasin_skills.png") {}
	/**
	 * .
	 * \brief Funkcja rysuj¹ca tablicê umiejêtnoœci dla odpowiednich postaci
	 * \param ID ID postaci
	 */
	void Bind(int ID);
};