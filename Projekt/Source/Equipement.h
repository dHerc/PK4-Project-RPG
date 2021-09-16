#pragma once
#include "Graphic_engine/Graphic_engine.h"
#include "Item.h"
#include "Owned.h"
#include "Character.h"
#include "Description.h"
#include "Face.h"
#include "Skills.h"
class Equipement
{
private:
	float position[16] =
	{
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};
	float slot_position[16] =
	{
		-0.08f, -0.15f, 0.0f, 0.0f,
		 0.08f, -0.15f, 1.0f, 0.0f,
		 0.08f, 0.15f, 1.0f, 1.0f,
		-0.08f, 0.15f, 0.0f, 1.0f
	};
	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};
	VertexArray va;
	VertexArray slot_va;
	VertexBuffer vb;
	VertexBuffer slot_vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
	Texture texture;
	Texture selection;
	Texture empty_slot;
	Texture selected_slot;
	int actual_slot = 0;
	int actual_item = 0;
	bool &right;
	bool &left;
	int &up;
	int &down;
	bool &confirm;
	int delay = 0;
	bool wait_for_release = false;
	Renderer renderer;
	Owned& owned_items;
	Description& description;
	Face& face;
	Skills& skills;
public:
	shared_ptr<Item> weapon[4];
	shared_ptr<Item> armour[4];
	shared_ptr<Item> sidearm[4];
	Equipement(Owned& inventory, Description& description, Face& face, Skills& skills, Renderer& renderer, bool& right, bool& left, int& up, int& down, bool& confirm);
	/**
	 * .
	 * \brief Funkcja wyposa¿aj¹ca postaæ w odpowiedni przedmiot
	 * \param it przedmiot do wyposa¿enia
	 * \param char_class ID postaci której ma byæ wyposa¿ony
	 */
	void Equip(Item it,int char_class);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca ekwipunek
	 * \param state aktualny stan
	 * \param leave zmienna obs³uguj¹ca przycisk wyjœcia
	 */
	void Draw(int &state, bool &leave);
	/**
	 * .
	 * /brief Funkcja rysuj¹ca menu wyboru ekwipunku
	 */
	void Draw_selection();
	/**
	 * .
	 * \brief Funkcja odpowiedzialna za zmianê wybranego pola
	 */
	void Change_slot();
	/**
	 * .
	 * \brief Funkcja pozwalaj¹ca na wybór pomiêdzy posiadanymi elementami ekwipunku
	 * \param amount iloœæ dotêpnych elementów ekwipunku
	 */
	void ChangeSelectedItem(int amount);
	/**
	 * .
	 * \brief Funkcja pozwalaj¹ca wybraæ odpowiednie pole w ekwipunku
	 */
	void Select_slot();
	/**
	 * .
	 * \brief Funkcja rysuj¹ca wybrane menu umiejêtnoœci
	 * \param char_class ID postaci której ma dotyczyæ okno
	 */
	void Selection_skills(int char_class);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca posiadane bronie
	 * \param char_class ID postaci której bronie maj¹ zostaæ pokazane
	 */
	void Selection_weapon(int char_class);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca posiadane bronie poboczne
	 * \param char_class ID postaci której bronie poboczne maj¹ zostaæ pokazane
	 */
	void Selection_sidearm(int char_class);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca posiadane zbroje
	 * \param char_class ID postaci której zbroje maj¹ zostaæ pokazane
	 */
	void Selection_armour(int char_class);
	/**
	 * .
	 * \brief Funkcja dodaj¹ca przedmiot do posiadanych przedmiotów
	 * \param it przedmiot do dodania
	 */
	void AddItem(Item it);
	void TriggerEQ(int char_nr, int char_pos[2], int world[1920][216], Character& character, bool mode);
};
