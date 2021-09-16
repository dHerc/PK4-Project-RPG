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
	 * \brief Funkcja rysuj�ca nak�adk� ze statystykami postaci
	 * \param char_nr ID aktualnej postaci
	 */
	void Draw(int char_nr);
	/**
	 * .
	 * \brief Funkcja rysuj�ca paski z informacjami o stanie postaci
	 * \param type typ paska
	 * \param value warto�� aktualna
	 * \param max_value warto�� maksymalna
	 */
	void DrawBar(int type,float value,float max_value);
	/**
	 * .
	 * \brief Funkcja przypisuj�ca tekstur� numeru
	 * \param character numer do przypisania
	 */
	void BindNumber(char character);
	/**
	 * .
	 * \brief Funkcja rysuj�ca ilo�� posiadanego z�ota
	 * \param amount ilo�� posiadanego z�ota
	 */
	void DrawGold(int amount);
	/**
	 * .
	 * /brief Funkcja rysuj�ca aktualny poziom postaci
	 * \param lvl aktualny poziom postaci
	 */
	void DrawLvl(int lvl);
	/**
	 * .
	 * \brief Funkcja rysuj�ca ilo�� posiadanych �adunk�w broni przybocznej
	 * \param amount ilo�� �adunk�w broni przybocznej
	 */
	void DrawSideStacks(int amount);
};