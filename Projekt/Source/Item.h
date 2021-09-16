#pragma once
#include "Graphic_engine/Graphic_engine.h"
#include "Character.h"
enum item_type
{
	Weapon=0,
	Sidearm=1,
	Armour=2,
	Nothing=3 
};
class Item
{
private:
	int stats[2] = { 0,0 };
	Texture item_texture;
	Texture item_description;
	item_type type;
	int item_class; //0-archer,1-warrior,2-mage,3-assasin
	string path = "Resource/textures/Nothing.png";
	string desc_path= "Resource/textures/Nothing.png";
	void(Item::* effect)(int char_pos[2], int world[1920][216],Character &character,bool mode);
	bool triggered = false;
public:
	Item() : item_texture("Resource/textures/Nothing.png"),item_description("Resource/textures/Nothing.png"),type(Nothing),item_class(4) {effect = &Item::no_effect;};
	Item(int stat1, int stat2, string name, int it_type, int item_class, int effectID = 0);
	Item(const Item& it);
	/**
	 * .
	 * \brief Funkcja zwracaj�ca typ przedmiotu
	 * \return typ przedmiotu
	 */
	int Get_type();
	/**
	 * .
	 * \brief Funkcja zwracaj�ca klas� danego przedmiotu
	 * \return klasa danego przedmiotu
	 */
	int Get_class();
	/**
	 * .
	 * \brief Funkcja zwracaj�ca pierwsz� statystyk� danego przedmiotu
	 * \return pierwsza statystyka danego przedmiotu
	 */
	int Get_first_stat();
	/**
	 * .
	 * \brief Funkcja zwracaj�ca drug� statystyk� danego przedmiotu
	 * \return druga statystyka danego przedmiotu
	 */
	int Get_seccond_stat();
	/**
	 * .
	 * \brief funkcja przypisuj�ca tekstur� danego przedmiotu
	 */
	void Bind_texture();
	/**
	 * .
	 * \brief funkcja przypisauj�ca opis danego przedmiotu
	 */
	void Bind_description();
	/**
	 * .
	 * \brief Funkcja wywo�uj�ca efekt specjalny ekwipunku
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj�ca informacje o �wiecie
	 * \param character aktualna posta�
	 * \param mode tryb(w��cz/wy��cz)
	 */
	void Trigger(int char_pos[2], int world[1920][216], Character& character, bool mode);
	/**
	 * .
	 * \brief Funkcja nie wywo�uj�ca �adnego specjalnego efektu
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj�ca informacje o �wiecie
	 * \param character aktualna posta�
	 * \param mode tryb(w��cz/wy��cz)
	 */
	void no_effect(int char_pos[2], int world[1920][216], Character &character,bool mode);
	/**
	 * .
	 * \brief Funkcja wywo�uj�ca efekt specjalny zwiekszaj�cy obra�enia w trakcie stania na trawie
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj�ca informacje o �wiecie
	 * \param character aktualna posta�
	 * \param mode tryb(w��cz/wy��cz)
	 */
	void bonus_damage_on_grass(int char_pos[2], int world[1920][216], Character &character,bool mode);

};