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
	 * \brief Funkcja przypisuj�ca tekstur�
	 * \param slot slot do kt�rego ma by� przypisana
	 */
	void Bind(unsigned slot =0) const;
	/**
	 * .
	 * \brief Funkcja anuluj�ca przypisanie tekstury
	 */
	void Unbind() const;

	/**
	 * .
	 * \brief Funkcja zwracaj�ca szeroko�� tekstury
	 * \return szeroko�� tekstury
	 */
	inline int GetWidth() const { return m_Width; }
	/**
	 * .
	 * \brief Funkcja zwracaj�ca wysoko�� tekstury
	 * \return wysoko�� tekstury
	 */
	inline int GetHeight() const { return m_Height; }
	/**
	 * .
	 * \brief Funkcja zwracaj�ca bity na piksel tekstury
	 * \return bity na piksel tekstury
	 */
	inline int GetBPP() const { return m_BPP; }
};