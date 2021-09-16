#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};
class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	/**
	 * .
	 * \brief Funkcja ustawiaj�ca uniform sk�adaj�cy si� z jednego int'a
	 * \param name nawzwa uniformu
	 * \param v warto�� wstawiana
	 */
	void SetUniform1i(const std::string& name, int v);
	/**
	 * .
	 * \brief Funkcja ustawiaj�ca uniform sk�adaj�cy si� z 4 float'�w
	 * \param name nawza uniformu
	 * \param v1 pierwsza warto�� wstawiana
	 * \param v2 druga warto�� wstawiana
	 * \param v3 trzecia warto�� wstawiana
	 * \param v4 czwarta warto�� wstawiana
	 */
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	/**
	 * .
	 * \brief Funkcja ustawiaj�ca uniform sk�adaj�cy si� z 2 float'�w
	 * \param name nawza uniformu
	 * \param v1 pierwsza warto�� wstawiana
	 * \param v2 druga warto�� wstawiana
	 */
	void SetUniform2f(const std::string& name, float v1, float v2);
private:
	/**
	 * .
	 * \brief Funkcja pozyskuj�ca lokacj� uniformu
	 * \param name nazwa uniformu
	 * \return lokacja uniformu
	 */
	int GetUniformLocation(const std::string& name);
	/**
	 * .
	 * \brief Funkcja kompiluj�ca shader
	 * \param type typ kompilowanego shadera
	 * \param source �r�d�o kopmpilowanego shadera
	 * \return  id shadera
	 */
	unsigned int CompileShader(unsigned int type, const std::string& source);
	/**
	 * .
	 * \brief Funkcja tworz�ca shader
	 * \param vertexShader vertex shader
	 * \param fragmentShader fragment shader
	 * \return id shadera
	 */
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	/**
	 * .
	 * \brief Funkcja przekszta�caj�ca plik z shaderem na odpowiednie cz�ci
	 * \param filepath �cie�ka do shaderea
	 * \return �r�d�o shadera
	 */
	ShaderProgramSource ParseShader(const std::string& filepath);
};