#pragma once
#include "Graphic_engine/Graphic_engine.h"
#include "Item.h"
#include "Description.h"
class Minimenu
{
private:
	float position[16] =
	{
		-0.5f, -1.0f, 0.0f, 0.0f,
		 0.5f, -1.0f, 1.0f, 0.0f,
		 0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f,  0.0f, 0.0f, 1.0f
	};
	float button_position[16] =
	{
		-0.1667f, -0.1481f, 0.0f, 0.0f,
		 0.1667f, -0.1481f, 1.0f, 0.0f,
		 0.1667f,  0.0f, 1.0f, 1.0f,
		-0.1667f,  0.0f, 0.0f, 1.0f
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
	int selected_option = 0;
	VertexArray va;
	VertexArray button_va;
	VertexArray slot_va;
	VertexBuffer vb;
	VertexBuffer button_vb;
	VertexBuffer slot_vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
	Texture texture;
	Texture button_1;
	Texture button_2;
	Texture button_3;
	Texture button_1_1;
	Texture selected_button;
	Texture empty_slot;
	Texture selected_slot;
	Renderer& renderer;
	Description& description;
	int& up;
	int& down;
	bool& right;
	bool& left;
	bool& confirm;
	bool& leave;
	int menu_type = 0;
	int confirmation = 0;
	int leaving = 0;
	int go_down = 0;
	int go_up = 0;
	int delay = 0;
	int actual_item = 0;
	list<shared_ptr<Item>> shop_items;
public:
	Minimenu(Renderer& renderer, Description& description, int& up, int& down, bool& right, bool& left, bool& confirm, bool& leave);
	/**
	 * .
	 * \brief Funkcja rysuj�ca minimenu
	 * \param options opcje minimenu
	 * \return zwraca ID wybranej opcji z menu
	 */
	int Draw(int options[3]);
	/**
	 * .
	 * \brief Funkcja rysuj�ca t�o minimenu
	 */
	void Draw_background();
	/**
	 * .
	 * \brief Funkcja rysuj�ca przyciski w minimenu
	 * \param options opcje minimenu
	 */
	void Draw_buttons(int options[3]);
	/**
	 * .
	 * \brief Funkcja rysuj�ca sklep wewn�trz minimenu
	 * \return ID zakupionego przedmiotu 
	 */
	int Draw_item_shop();
	/**
	 * .
	 * \brief Funkcja ustawiaj�ca list� przedmiot�w w sklepie
	 * \param ID ID zestawu przedmiot�w
	 */
	void Set_item_list(int ID);
	/**
	 * .
	 * \Funkcja zwracaj�ca przedmiot na podstawie jego ID
	 * \param ID ID przedmiotu
	 * \return przedmiot o podanym ID
	 */
	Item GetItem(int ID);
	/**
	 * .
	 * \Brief Funkcja zwrracaj�ca cen� przedmiotu o danym ID
	 * \param ID ID przedmiotu
	 * \return cena przedmiotu o podanym ID
	 */
	int CheckPrice(int ID);
	/**
	 * .
	 * \brief Funkcja pozwalaj�ca graczowi porusza� si� po menu sklepu
	 * \param amount ilo�� przedmiot�w w sklepie
	 */
	void ChangeSelectedItem(int amount);
	/**
	 * .
	 * \brief Funkcja sprawdzaj�ca czy gracz wybra� i zaakceptowa� jak�� opcj�
	 * \return informacja czy gracz zaakcpetowa�
	 */
	bool GetConfirmation();
};