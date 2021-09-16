#pragma once
#include "Graphic_engine/Graphic_engine.h"
#include "Face.h"
class Overlay
{
private:
	float position[16] =
	{
		-1.0f, 0.7777f, 0.0f, 0.0f,
		 -0.70f, 0.7777f, 1.0f, 0.0f,
		 -0.70f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};
	float bar_position[16] =
	{
		-0.8918f, 0.9610f, 0.0f, 0.0f,
		-0.7388f, 0.9610f, 1.0f, 0.0f,
		-0.7388f, 0.9944f, 1.0f, 1.0f,
		-0.8918f, 0.9944f, 0.0f, 1.0f
	};
	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};
	float number_position[16] =
	{
		-0.749f, 0.7999f, 0.0f, 0.0f,
		 -0.7245f, 0.7999f, 1.0f, 0.0f,
		 -0.7245f,  0.8444f, 1.0f, 1.0f,
		-0.749f,  0.8444f, 0.0f, 1.0f
	};
	VertexArray va;
	VertexArray bar_va;
	VertexArray number_va;
	VertexBuffer vb;
	VertexBuffer bar_vb;
	VertexBuffer number_vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
	Texture texture;
	Texture hp_bar_texture;
	Texture mp_bar_texture;
	Texture exp_bar_texture;
	Texture side_stacks_texture;
	Texture _0;
	Texture _1;
	Texture _2;
	Texture _3;
	Texture _4;
	Texture _5;
	Texture _6;
	Texture _7;
	Texture _8;
	Texture _9;
	Face& face;
	Renderer& renderer;
public:
	Overlay(Renderer& renderer, Face& face);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca nak³adkê ze statystykami postaci
	 * \param char_nr ID aktualnej postaci
	 */
	void Draw(int char_nr);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca paski z informacjami o stanie postaci
	 * \param type typ paska
	 * \param value wartoœæ aktualna
	 * \param max_value wartoœæ maksymalna
	 */
	void DrawBar(int type,float value,float max_value);
	/**
	 * .
	 * \brief Funkcja przypisuj¹ca teksturê numeru
	 * \param character numer do przypisania
	 */
	void BindNumber(char character);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca iloœæ posiadanego z³ota
	 * \param amount iloœæ posiadanego z³ota
	 */
	void DrawGold(int amount);
	/**
	 * .
	 * /brief Funkcja rysuj¹ca aktualny poziom postaci
	 * \param lvl aktualny poziom postaci
	 */
	void DrawLvl(int lvl);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca iloœæ posiadanych ³adunków broni przybocznej
	 * \param amount iloœæ ³adunków broni przybocznej
	 */
	void DrawSideStacks(int amount);
};