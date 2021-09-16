#pragma once
#include <GL/glew.h>
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#define ASSERT(x) if (!(x)) __debugbreak();
#ifdef DEBUG
#define GLCall(x) GlCleanError();\
    x;\
    ASSERT(GlLogCall(#x, __FILE__,__LINE__))
#else
#define GLCall(x) x
#endif
void GlCleanError();
bool GlLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    /**
     * .
     * \brief Funkcja czyszcz¹ca renderer
     */
    void Clear() const;
    /**
     * .
     * \brief Funkcja rysuj¹ca
     * \param va vertex array
     * \param ib index buffer
     * \param shader shader
     */
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};