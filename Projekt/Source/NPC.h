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
	 * \brief Funkcja wywo³uj¹ca interakcjê z NPC
	 * \return czy minimenu ma zostaæ otwarte
	 */
	bool Interact();
	/**
	 * .
	 * \brief Funkcja powoduj¹ca brak interakcji
	 * \return false(brak otwarcia minimenu)
	 */
	bool no_interact();
	/**
	 * .
	 * \brief Funkcja powoduj¹ca otwarcie minimenu jako interakcjê
	 * \return true(powoduje otwarcie minimenu) 
	 */
	bool open_mini_menu();
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca informacje o ID fabu³y postaci
	 * \return ID fabu³y postaci 
	 */
	int Get_menu_story();
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca ID przedmiotów w sklepie
	 * \return ID zestawu przedmiotów sprzedawanych przez aktualnego NPC
	 */
	int Get_menu_items();
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca cenê kupna ³adunków broni przybocznej
	 * \return cena ³adunku broni przybocznej
	 */
	int Get_menu_sidearm();
};