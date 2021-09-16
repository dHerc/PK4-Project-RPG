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
	 * \brief Funkcja przypisuj�ca vertex buffer
	 */
	void Bind()const;
	/**
	 * .
	 * \brief Funkcja anuluj�ca przypisanie vertex buffer'a
	 */
	void Unbind()const;
};