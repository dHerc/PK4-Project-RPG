#pragma once
#include "Enemies.h"
#include "Character.h"
class Boss :public Enemies
{
private:
	int cycle=0;
	bool(Boss::* trigger)(Character & character);
public:
	Boss(float& character_offset_x, float& character_offset_y, double pos_x, double pos_y, string pathl, string pathr, int ID, Renderer& renderer, int hp, int dmg, int exp, int gold, int lvl, int move_patern, int attack_patern, int trigger_type);
	/**
	 * .
	 * \brief Funkcja uruchamiaj�ca umiej�tno�ci specjalne bossa
	 * \param character aktualna posta�
	 * \return true je�eli maj� zosta� przyzwani sojusznicy, false w przeciwnym wypadku
	 */
	bool Trigger(Character & character);
	/**
	 * .
	 * \brief Funkcja uruchamiania dla Mrocznego Maga
	 * \param character aktualna posta� 
	 * \return true je�eli maj� zosta� przyzwani sojusznicy, false w przeciwnym wypadku
	 */
	bool DarkMage(Character& character);
};