#pragma once
class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	/**
	 * .
	 * \brief Funkcja przypisująca vertex buffer
	 */
	void Bind()const;
	/**
	 * .
	 * \brief Funkcja anulująca przypisanie vertex buffer'a
	 */
	void Unbind()const;
};