#pragma once
#include "Entities.h"

class NPC :public Entities
{
private:
	bool(NPC::* interaction)();
	int menu_options[3];
public:
	NPC(float& character_offset_x, float& character_offset_y, double pos_x, double pos_y, string path, int ID, Renderer& renderer, int interactionID, int options[3]);
	/**
	 * .
	 * \brief Funkcja wywo�uj�ca interakcj� z NPC
	 * \return czy minimenu ma zosta� otwarte
	 */
	bool Interact();
	/**
	 * .
	 * \brief Funkcja powoduj�ca brak interakcji
	 * \return false(brak otwarcia minimenu)
	 */
	bool no_interact();
	/**
	 * .
	 * \brief Funkcja powoduj�ca otwarcie minimenu jako interakcj�
	 * \return true(powoduje otwarcie minimenu) 
	 */
	bool open_mini_menu();
	/**
	 * .
	 * \brief Funkcja zwracaj�ca informacje o ID fabu�y postaci
	 * \return ID fabu�y postaci 
	 */
	int Get_menu_story();
	/**
	 * .
	 * \brief Funkcja zwracaj�ca ID przedmiot�w w sklepie
	 * \return ID zestawu przedmiot�w sprzedawanych przez aktualnego NPC
	 */
	int Get_menu_items();
	/**
	 * .
	 * \brief Funkcja zwracaj�ca cen� kupna �adunk�w broni przybocznej
	 * \return cena �adunku broni przybocznej
	 */
	int Get_menu_sidearm();
};