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
	 * \brief Funkcja wywo�uj�ca funkcj� poruszania si� przeciwnika
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj�ca informacje o �wiecie
	 */
	void Move(int char_pos[2],int world[1920][216]);
	/**
	 * .
	 * \brief Funkcja wywo�uj�ca funkcj� atakowania przeciwnika
	 * \param char_pos pozycja postaci
	 * \param damage_taken obra�enia otrzymane przez posta�
	 */
	void Attack(int char_pos[2],int & damage_taken);
	/**
	 * .
	 * \brief Funkcja obs�uguj�ca brak poruszania si� przeciwnika
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj�ca informacje o �wiecie
	 */
	void mov_still(int char_pos[2],int world[1920][216]);
	/**
	 * .
	 * \brief Funkcja wywo�uj�ca bazowe poruszanie si� przeciwnika
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj�ca informacje o �wiecie
	 */
	void mov_basic(int char_pos[2],int world[1920][216]);
	/**
	 * .
	 * \brief Funkcja wywo�uj�ca poruszanie si� przeciwnika bez ogranicze�
	 * \param char_pos pozycja postaci
	 * \param world zmienna zawieraj�ca informacje o �wiecie
	 */
	void mov_free(int char_pos[2], int world[1920][216]);
	/**
	 * .
	 * \brief Funkcja wywo�uj�ca brak atakowania przeciwnika
	 * \param char_pos pozycja postaci
	 * \param damage_taken obra�enia otrzymane przez posta�
	 */
	void atk_disabled(int char_pos[2],int & damage_taken);
	/**
	 * .
	 * \brief Funkcja wywo�uj�ca bazowe atakowanie przeciwnika
	 * \param char_pos pozycja postaci
	 * \param damage_taken obra�enia otrzymane przez posta�
	 */
	void atk_basic(int char_pos[2], int & damage_taken);
};