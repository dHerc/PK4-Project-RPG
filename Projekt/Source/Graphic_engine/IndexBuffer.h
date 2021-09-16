#pragma once
class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	/**
	 * .
	 * \brief Funkcja przypisuj�ca index buffer
	 */
	void Bind() const;
	/**
	 * .
	 * \brief Funkcja anuluj�ca przypisanie index buffer'a
	 */
	void Unbind() const;
	
	/**
	 * .
	 * \brief Funkcja zwracaj�ca ilo�� indeks�w
	 * \return ilo�� indeks�w 
	 */
	inline unsigned int GetCount() const { return m_Count; }
};