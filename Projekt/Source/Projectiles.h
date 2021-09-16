#pragma once
#include "Entities.h"

class Projectiles : public Entities
{
private:
	int damage;
public:
	Projectiles(float& character_offset_x, float& character_offset_y, double pos_x, double pos_y, string pathl, string pathr, Renderer& renderer, bool _right,int damage) :Entities(character_offset_x, character_offset_y, pos_x, pos_y, pathl, pathr, 0, renderer, true),damage(damage) { right = _right; }
	/**
	 * .
	 * \brief Funkcja poruszaj¹ca pociskami
	 * \param world zmienna przechowuj¹ca informacje o œwiecie
	 * \return ID trafionego celu
	 */
	int Move(int world[1920][216]);
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca obra¿enia pocisku
	 * \return obra¿enia pocisku
	 */
	int GetDamage();
};