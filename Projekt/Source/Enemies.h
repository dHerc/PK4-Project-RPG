#pragma once
#include "Entities.h"
#include "Stats.h"
class Enemies :public Entities, public Stats
{
	void(Enemies::* movement)(int char_pos[2],int world[1920][216]);
	void(Enemies::* attack)(int char_pos[2],int & damage_taken);
	int delay=0;
public:
	Enemies(float& character_offset_x, float& character_offset_y, double pos_x, double pos_y, string pathl, string pathr, int ID, Renderer& renderer, int hp, int dmg, int exp, int gold, int lvl, int move_patern, int attack_patern);
	/**
	 * .
	 * \brief Funkcja wywo³uj¹ca funkcjê poruszania siê przeciwnika
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj¹ca informacje o œwiecie
	 */
	void Move(int char_pos[2],int world[1920][216]);
	/**
	 * .
	 * \brief Funkcja wywo³uj¹ca funkcjê atakowania przeciwnika
	 * \param char_pos pozycja postaci
	 * \param damage_taken obra¿enia otrzymane przez postaæ
	 */
	void Attack(int char_pos[2],int & damage_taken);
	/**
	 * .
	 * \brief Funkcja obs³uguj¹ca brak poruszania siê przeciwnika
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj¹ca informacje o œwiecie
	 */
	void mov_still(int char_pos[2],int world[1920][216]);
	/**
	 * .
	 * \brief Funkcja wywo³uj¹ca bazowe poruszanie siê przeciwnika
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj¹ca informacje o œwiecie
	 */
	void mov_basic(int char_pos[2],int world[1920][216]);
	/**
	 * .
	 * \brief Funkcja wywo³uj¹ca poruszanie siê przeciwnika bez ograniczeñ
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj¹ca informacje o œwiecie
	 */
	void mov_free(int char_pos[2], int world[1920][216]);
	/**
	 * .
	 * \brief Funkcja wywo³uj¹ca brak atakowania przeciwnika
	 * \param char_pos pozycja postaci
	 * \param damage_taken obra¿enia otrzymane przez postaæ
	 */
	void atk_disabled(int char_pos[2],int & damage_taken);
	/**
	 * .
	 * \brief Funkcja wywo³uj¹ca bazowe atakowanie przeciwnika
	 * \param char_pos pozycja postaci
	 * \param damage_taken obra¿enia otrzymane przez postaæ
	 */
	void atk_basic(int char_pos[2], int & damage_taken);
};