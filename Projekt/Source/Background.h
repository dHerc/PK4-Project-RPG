#pragma once
#include "Graphic_engine/Graphic_engine.h"
class Background
{
private:
	float position[16] =
	{
		-2.0f, -2.0f, 0.0f, 0.0f,
		 2.0f, -2.0f, 1.0f, 0.0f,
		 2.0f,  2.0f, 1.0f, 1.0f,
		-2.0f,  2.0f, 0.0f, 1.0f
	};
	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};
	float& character_offset_x;
	float& character_offset_y;
	int lvl;
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
	shared_ptr<Texture> texture;
	shared_ptr<Texture> additional_texture;
	Renderer renderer;
	int actual_lvl;

public:
	Background(float& char_off_x, float& char_off_y, Renderer& renderer, int lvl);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca t³o
	 * \param lvl nr aktualnego poziomu
	 */
	void Draw(int lvl);
};