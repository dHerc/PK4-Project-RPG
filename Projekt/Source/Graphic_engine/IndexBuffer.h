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
	 * \brief Funkcja przypisuj¹ca index buffer
	 */
	void Bind() const;
	/**
	 * .
	 * \brief Funkcja anuluj¹ca przypisanie index buffer'a
	 */
	void Unbind() const;
	
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca iloœæ indeksów
	 * \return iloœæ indeksów 
	 */
	inline unsigned int GetCount() const { return m_Count; }
};