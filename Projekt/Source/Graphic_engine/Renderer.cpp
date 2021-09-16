#include "Renderer.h"
void GlCleanError()
{
    while (glGetError() != GL_NO_ERROR);
}
bool GlLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::string fl = file;
        std::cout << "OpenGL error nr " << std::hex << error << std::dec << " by " << function << " in " << fl.substr(46, 100) << " line nr " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
