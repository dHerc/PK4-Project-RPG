#pragma once
#include "Entities.h"
#include "Item.h"
enum pickup_type
{
	healing = 0,
	mana = 1,
	sidearm_charge = 2,
	gold = 3,
	item = 4
};
class Drops :public Entities
{
private:
	pickup_type type;
	int amount_or_itemID = 1;
public:
	Drops(float& character_offset_x, float& character_offset_y, double pos_x, double pos_y, string path, int ID, Renderer& renderer, int init_type, int amount_or_itemID);
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca typ przedmiotu do podniesienia
	 * \return typ przedmiotu do podniesienia
	 */
	int GetType();
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca iloœæ przedmiotów lub ID przedmiotu w wypadku przedmiotu ekwipunku
	 * \return iloœæ przedmiotów/ID przedmiotu
	 */
	int GetAmountOrID();
};