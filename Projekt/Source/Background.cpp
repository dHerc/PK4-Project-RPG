#include "Background.h"
Background::Background(float& char_off_x, float& char_off_y, Renderer& renderer, int lvl) :character_offset_x(char_off_x), character_offset_y(char_off_y),
vb(position, 4 * 4 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"), actual_lvl(lvl)
{
	string path;
	if (lvl > -1 && lvl < 5)
		path = "Resource/textures/Tavern_" + to_string(lvl) + ".png";
	if (lvl == 5)
	{
		path = "Resource/textures/World_" + to_string(lvl) + ".png";
	}
	if (lvl == 6)
	{
		path = "Resource/textures/Boss_Fight_Right.png";
		shared_ptr<Texture> background(new Texture(path));
		additional_texture = background;
		path = "Resource/textures/Boss_Fight_Left.png";
	}
	shared_ptr<Texture> background(new Texture(path));
	texture = background;
	if (lvl == 5)
	{
		path = "Resource/textures/World_" + to_string(lvl + 1) + ".png";
		shared_ptr<Texture> background(new Texture(path));
		additional_texture = background;
	}
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	shader.Bind();
	texture.get()->Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform2f("u_off", -character_offset_x, -character_offset_y);
	shader.SetUniform2f("u_off_moving", 0.0, 0.0);
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();
}
void Background::Draw(int lvl)
{
	if (lvl < 5)
	{
		va.Bind();
		vb.Bind();
		ib.Bind();
		texture.get()->Bind();
		shader.Bind();
		shader.SetUniform2f("u_off", -character_offset_x, -character_offset_y);
		renderer.Draw(va, ib, shader);
	}
	if (lvl == 6||lvl ==7)
	{
		va.Bind();
		vb.Bind();
		ib.Bind();
		shader.Bind();
		texture.get()->Bind();
		shader.SetUniform2f("u_off", -character_offset_x, -character_offset_y);
		renderer.Draw(va, ib, shader);
		additional_texture.get()->Bind();
		shader.SetUniform2f("u_off", -character_offset_x + 4.0, -character_offset_y);
		renderer.Draw(va, ib, shader);
	}
	if(lvl==5)
	{
		
		float char_off_x = character_offset_x;
		while (char_off_x+1.0 > 4.0)
		{
			char_off_x -= 4.0;
			lvl++;
		}
		if (actual_lvl != lvl)
		{
			string path;
			path = "Resource/textures/World_" + to_string(lvl) + ".png";
			shared_ptr<Texture> background(new Texture(path));
			texture = background;
			path = "Resource/textures/World_" + to_string(lvl + 1) + ".png";
			shared_ptr<Texture> next_background(new Texture(path));
			additional_texture = next_background;
			actual_lvl = lvl;
		}
		va.Bind();
		vb.Bind();
		ib.Bind();
		shader.Bind();
		texture.get()->Bind();
		shader.SetUniform2f("u_off", -char_off_x, -character_offset_y);
		renderer.Draw(va, ib, shader);
		additional_texture.get()->Bind();
		shader.SetUniform2f("u_off", -char_off_x+4.0, -character_offset_y);
		renderer.Draw(va, ib, shader);
	}
}
