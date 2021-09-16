#pragma once
#include"Renderer.h"
using namespace std;
class Texture
{
private:
	unsigned int m_RendererID;
	string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const string& path);
	~Texture();

	/**
	 * .
	 * \brief Funkcja przypisuj¹ca teksturê
	 * \param slot slot do którego ma byæ przypisana
	 */
	void Bind(unsigned slot =0) const;
	/**
	 * .
	 * \brief Funkcja anuluj¹ca przypisanie tekstury
	 */
	void Unbind() const;

	/**
	 * .
	 * \brief Funkcja zwracaj¹ca szerokoœæ tekstury
	 * \return szerokoœæ tekstury
	 */
	inline int GetWidth() const { return m_Width; }
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca wysokoœæ tekstury
	 * \return wysokoœæ tekstury
	 */
	inline int GetHeight() const { return m_Height; }
	/**
	 * .
	 * \brief Funkcja zwracaj¹ca bity na piksel tekstury
	 * \return bity na piksel tekstury
	 */
	inline int GetBPP() const { return m_BPP; }
};