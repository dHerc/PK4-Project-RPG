#pragma once
#include "Graphic_engine/Graphic_engine.h"
class Story
{
private:
	float story_equipement_position[16] =
	{
		 0.30f, -0.9259f, 0.0f, 0.0f,
		 0.97f, -0.9259f, 1.0f, 0.0f,
		 0.97f, 0.9259f, 1.0f, 1.0f,
		 0.30f, 0.9259f, 0.0f, 1.0f
	};
	float story_NPC_position[16] =
	{
		-0.5f, -1.0f, 0.0f, 0.0f,
		 0.5f, -1.0f, 1.0f, 0.0f,
		 0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f,  0.0f, 0.0f, 1.0f
	};
	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};
	VertexArray va;
	VertexArray NPC_va;
	VertexBuffer vb;
	VertexBuffer NPC_vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
	shared_ptr<Texture> texture;
	shared_ptr<Texture> NPC_texture;
	shared_ptr<Texture> NPC_wrong;
	int activation[4] = { 0,0,0,0 };
	int ID;
	Renderer renderer;
public:
	/**
	 * .
	 * \brief Konstruktor funkcji odpowiedzialnej za historiê
	 * \param renderer renderer
	 * \param ID ID historii
	 */
	Story(Renderer& renderer, int ID);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca informacje o zadaniu w menu ekwipunku
	 */
	void Draw();
	/**
	 * .
	 * \brief Funkcja odpowiedzialna za uruchamianie zdarzeñ fabularnych
	 * \param trigger_ID
	 * \return ID akcji do wykonia w zwi¹zku ze zdarzeniem fabularnym
	 */
	int Trigger(int trigger_ID);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca informacje o zadaniu w trakcie rozmowy z NPC
	 * \param NPC_ID ID NPC z którym akualnie rozmawia gracz
	 */
	void Draw(int NPC_ID);
};