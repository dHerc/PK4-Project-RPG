#pragma once
#include "VertexBuffer.h"
class VertexBufferLayout;
class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	/**
	 * .
	 * \brief Funkcja dodaj�ca vertex buffer do vertex array'a
	 * \param vb dodawany vertex buffer
	 * \param layout odpowiedni vertex buffer layout
	 */
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	/**
	 * .
	 * \brief Funkcja przypisuj�ca vertex array
	 */
	void Bind() const;
	/**
	 * .
	 * \Funkcja anuluj�ca przypisanie vertex array'a
	 */
	void Unbind() const;
};