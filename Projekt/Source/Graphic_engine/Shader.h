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
	 * \brief Funkcja ustawiaj¹ca uniform sk³adaj¹cy siê z jednego int'a
	 * \param name nawzwa uniformu
	 * \param v wartoœæ wstawiana
	 */
	void SetUniform1i(const std::string& name, int v);
	/**
	 * .
	 * \brief Funkcja ustawiaj¹ca uniform sk³adaj¹cy siê z 4 float'ów
	 * \param name nawza uniformu
	 * \param v1 pierwsza wartoœæ wstawiana
	 * \param v2 druga wartoœæ wstawiana
	 * \param v3 trzecia wartoœæ wstawiana
	 * \param v4 czwarta wartoœæ wstawiana
	 */
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	/**
	 * .
	 * \brief Funkcja ustawiaj¹ca uniform sk³adaj¹cy siê z 2 float'ów
	 * \param name nawza uniformu
	 * \param v1 pierwsza wartoœæ wstawiana
	 * \param v2 druga wartoœæ wstawiana
	 */
	void SetUniform2f(const std::string& name, float v1, float v2);
private:
	/**
	 * .
	 * \brief Funkcja pozyskuj¹ca lokacjê uniformu
	 * \param name nazwa uniformu
	 * \return lokacja uniformu
	 */
	int GetUniformLocation(const std::string& name);
	/**
	 * .
	 * \brief Funkcja kompiluj¹ca shader
	 * \param type typ kompilowanego shadera
	 * \param source Ÿród³o kopmpilowanego shadera
	 * \return  id shadera
	 */
	unsigned int CompileShader(unsigned int type, const std::string& source);
	/**
	 * .
	 * \brief Funkcja tworz¹ca shader
	 * \param vertexShader vertex shader
	 * \param fragmentShader fragment shader
	 * \return id shadera
	 */
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	/**
	 * .
	 * \brief Funkcja przekszta³caj¹ca plik z shaderem na odpowiednie czêœci
	 * \param filepath œcie¿ka do shaderea
	 * \return ¿ród³o shadera
	 */
	ShaderProgramSource ParseShader(const std::string& filepath);
};