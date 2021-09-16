#pragma once
#include "Graphic_engine/Graphic_engine.h"
class Face
{
private:
	float position[16] =
	{
		-0.08f, -0.15f, 0.0f, 0.0f,
		 0.08f, -0.15f, 1.0f, 0.0f,
		 0.08f, 0.15f, 1.0f, 1.0f,
		-0.08f, 0.15f, 0.0f, 1.0f
	};
	float position_overlay[16] =
	{
		-0.04f, -0.075f, 0.0f, 0.0f,
		 0.04f, -0.075f, 1.0f, 0.0f,
		 0.04f, 0.075f, 1.0f, 1.0f,
		-0.04f, 0.075f, 0.0f, 1.0f
	};
	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
	Texture Archer;
	Texture Warrior;
	Texture Mage;
	Texture Assasin;
	Renderer& renderer;
public:
	Face(Renderer& renderer);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca twarz odpowiedniej postaci
	 * \param pos_x pozycja x
	 * \param pos_y pozycja y
	 * \param char_nr nr postaci do narysowania
	 */
	void Draw(float pos_x, float pos_y,int char_nr);
};
