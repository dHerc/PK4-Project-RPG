#pragma once
#include "Graphic_engine/Graphic_engine.h"
class Entities
{
private:
	float position_graphic[16] =
	{
		-0.08f, -0.15f, 0.0f, 0.0f,
		 0.08f, -0.15f, 1.0f, 0.0f,
		 0.08f, 0.15f, 1.0f, 1.0f,
		-0.08f, 0.15f, 0.0f, 1.0f
	};
	float position_scaled[16] =
	{
		-0.02f, -0.15f, 0.0f, 0.0f,
		 0.02f, -0.15f, 1.0f, 0.0f,
		 0.02f, -0.075f, 1.0f, 1.0f,
		-0.02f, -0.075f, 0.0f, 1.0f
	};
	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};
	int ID;
	float& character_offset_x;
	float& character_offset_y;
	float pos_x;
	float pos_y;
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
	Texture texturel;
	Texture texturer;
	Renderer renderer;
public:
	int right;
public:
	Entities(float& char_off_x, float& char_off_y, float pos_x, float pos_y, string path, int ID, Renderer& renderer, bool scaled = false);
	Entities(float& char_off_x, float& char_off_y, float pos_x, float pos_y, string pathl, string pathr, int ID, Renderer& renderer, bool scaled = false);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca jednostkê
	 */
	void Draw();
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca x-ow¹ wspó³rzêdn¹ jednostki
	 * \return x-owa wspó³rzêdna jednostki
	 */
	float Get_x();
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca y-ow¹ wspó³rzêdn¹ jednostki
	 * \return y-owa wspó³rzêdna jednostki
	 */
	float Get_y();
	/**
	 * .
	 * \brief Funkcja ustawiaj¹ca x-ow¹ wpó³rzêdn¹ jednostki
	 * \param x wartoœæ na któr¹ zostanie zmieniona wspó³rzêdna
	 */
	void Set_x(float x);
	/**
	 * .
	 * \brief Funkcja ustawiaj¹ca y-ow¹ wpó³rzêdn¹ jednostki
	 * \param y wartoœæ na któr¹ zostanie zmieniona wspó³rzêdna
	 */
	void Set_y(float y);
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca ID jednostki
	 * \return ID jednostki
	 */
	int Get_ID();
};