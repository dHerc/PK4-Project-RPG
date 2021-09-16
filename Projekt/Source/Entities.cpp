#include "Entities.h"
Entities::Entities(float& char_off_x, float& char_off_y, float pos_x, float pos_y, string path, int ID, Renderer& renderer, bool scaled) :character_offset_x(char_off_x), character_offset_y(char_off_y),
pos_x(pos_x), pos_y(pos_y), vb((scaled) ? position_scaled : position_graphic, 4 * 4 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"),
texturel(path), texturer(path), ID(ID)
{
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	shader.Bind();
	texturel.Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform2f("u_off", -character_offset_x, -character_offset_y);
	shader.SetUniform2f("u_off_moving", -1.0 + (pos_x / 96.0), -0.87 + (pos_y / 54.0));
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();
}
Entities::Entities(float& char_off_x, float& char_off_y, float pos_x, float pos_y, string pathl, string pathr, int ID, Renderer& renderer, bool scaled) :character_offset_x(char_off_x), character_offset_y(char_off_y),
pos_x(pos_x), pos_y(pos_y), vb((scaled) ? position_scaled : position_graphic, 4 * 4 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"),
texturel(pathl), texturer(pathr), ID(ID)
{
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	shader.Bind();
	texturel.Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform2f("u_off", -character_offset_x, -character_offset_y);
	shader.SetUniform2f("u_off_moving", -1.0 + (pos_x / 96.0), -0.87 + (pos_y / 54.0));
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();
}
void Entities::Draw()
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	if (right)
		texturer.Bind();
	else
		texturel.Bind();
	shader.Bind();
	shader.SetUniform2f("u_off", -character_offset_x, -character_offset_y);
	shader.SetUniform2f("u_off_moving", -1.0 + (float)(pos_x / 96.0), -0.87 + (float)(pos_y / 54.0));
	renderer.Draw(va, ib, shader);
}

float Entities::Get_x()
{
	return pos_x;
}

float Entities::Get_y()
{
	return pos_y;
}

void Entities::Set_x(float x)
{
	pos_x=x;
}

void Entities::Set_y(float y)
{
	pos_y=y;
}

int Entities::Get_ID()
{
	return ID;
}
