#pragma once
#include "Graphic_engine/Graphic_engine.h"
class Menu
{
private:
	float position[16] =
	{
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};
	float button_position[16] =
	{
		-0.3333f, -0.1481f, 0.0f, 0.0f,
		 0.3333f, -0.1481f, 1.0f, 0.0f,
		 0.3333f,  0.1481f, 1.0f, 1.0f,
		-0.3333f,  0.1481f, 0.0f, 1.0f
	};
	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};
	int selected_option = 0;
	VertexArray va;
	VertexArray button_va;
	VertexBuffer vb;
	VertexBuffer button_vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
	Texture texture;
	Texture button_release_1;
	Texture button_release_2;
	Texture button_release_3;
	Texture options_button_release_1;
	Texture options_button_release_2;
	Texture button_press_1;
	Texture button_press_2;
	Texture button_press_3;
	Texture options_button_press_1;
	Texture options_button_press_2;
	Texture indicator_1;
	Texture indicator_2;
	Texture indicator_3;
	Texture indicator_4;
	Texture indicator_5;
	Renderer renderer;
	int& up;
	int& down;
	bool& confirm;
	int menu_type=0;
	int confirmation=0;
	int go_down = 0;
	int go_up = 0;
public:
	Menu(Renderer& renderer, int& up, int& down, bool& confirm);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca menu g³ówne
	 * \param state stan rozgrywki
	 * \param difficulty poziom trudnoœci
	 * \return informuje o wybranej przez gracza opcji
	 */
	int Draw(int& state,int & difficulty);
	/**
	 * .
	 * \brief Rysuje t³o menu
	 */
	void Draw_background();
	/**
	 * .
	 * \brief Funkcja rysuj¹ca przyciski w menu
	 * \param pressed aktualnie wybrany przycisk
	 */
	void Draw_buttons(int pressed);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca przyciski w menu opcji
	 * \param pressed aktulanie wybrany przycisk
	 * \param difficulty poziom trudnoœci
	 */
	void Draw_options_buttons(int pressed,int difficulty);
};