#pragma once
#include "Item.h"
class Description
{
	float position[16] =
	{
		-1.0f, -1.0f, 0.0f, 0.0f,
		-0.1f, -1.0f, 1.0f, 0.0f,
		-0.1f, -0.26f, 1.0f, 1.0f,
		-1.0f,  -0.26f, 0.0f, 1.0f
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
	Renderer renderer;
public:
	Description(Renderer& renderer);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca opis przedmiotu
	 * \param off_x pozycja x
	 * \param off_y pozycja y
	 */
	void Draw(float off_x,float off_y);
};