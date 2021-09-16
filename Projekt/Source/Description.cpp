#include "Description.h"
Description::Description(Renderer& renderer) :vb(position, 16 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"), renderer(renderer)
{
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	shader.Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform2f("u_off", 0, 0);
	shader.SetUniform2f("u_off_moving", 0.0, 0.0);
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();
}
void Description::Draw(float off_x,float off_y)
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	shader.Bind();
	shader.SetUniform2f("u_off", off_x, off_y);
	renderer.Draw(va, ib, shader);
}
