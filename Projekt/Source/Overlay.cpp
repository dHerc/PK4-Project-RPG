#include "Overlay.h"
Overlay::Overlay(Renderer& renderer, Face& face) :vb(position, 4 * 4 * sizeof(float)), bar_vb(bar_position, 4 * 4 * sizeof(float)), number_vb(number_position, 4 * 4 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"),
texture("Resource/textures/character_overlay.png"), hp_bar_texture("Resource/textures/hp_bar.png"), mp_bar_texture("Resource/textures/mp_bar.png"), exp_bar_texture("Resource/textures/exp_bar.png"), side_stacks_texture("Resource/textures/Arrow.png"),
_0("Resource/textures/0.png"), _1("Resource/textures/1.png"), _2("Resource/textures/2.png"), _3("Resource/textures/3.png"), _4("Resource/textures/4.png"), _5("Resource/textures/5.png"), _6("Resource/textures/6.png"), _7("Resource/textures/7.png"), _8("Resource/textures/8.png"), _9("Resource/textures/9.png"),
renderer(renderer), face(face)
{
layout.Push<float>(2);
layout.Push<float>(2);
va.AddBuffer(vb, layout);
bar_va.AddBuffer(bar_vb, layout);
number_va.AddBuffer(number_vb, layout);
shader.Bind();
texture.Bind();
shader.SetUniform1i("u_Texture", 0);
shader.SetUniform2f("u_off", 0.0, 0.0);
shader.SetUniform2f("u_off_moving", 0.0, 0.0);
number_va.Unbind();
vb.Unbind();
ib.Unbind();
shader.Unbind();
}

void Overlay::Draw(int char_nr)
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	texture.Bind();
	shader.Bind();
	shader.SetUniform2f("u_off", 0.0, 0.0);
	renderer.Draw(va, ib, shader);
	face.Draw(-0.95,0.905,char_nr);
}

void Overlay::DrawBar(int type, float value, float max_value)
{
	float base_4 = bar_position[4], base_8 = bar_position[8];
	float shift = (1 - (value / max_value)) * (float)0.1530;
	bar_position[4] -= shift;
	bar_position[8] -= shift;
	bar_va.Bind();
	bar_vb.Bind();
	ib.Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, 16*sizeof(float), bar_position, GL_DYNAMIC_DRAW));
	switch(type)
	{
	case 0:
		hp_bar_texture.Bind();
		shader.SetUniform2f("u_off", 0.0, 0.0);
		break;
	case 1:
		mp_bar_texture.Bind();
		shader.SetUniform2f("u_off", 0.0, -0.0444);
		break;
	case 2:
		exp_bar_texture.Bind();
		shader.SetUniform2f("u_off", 0.0, -0.0888);
		break;
	}
	shader.Bind();
	renderer.Draw(bar_va, ib, shader);
	bar_position[4] = base_4;
	bar_position[8] = base_8;
}

void Overlay::BindNumber(char character)
{
	switch (character)
	{
	case 0:
		_0.Bind();
		break;
	case 1:
		_1.Bind();
		break;
	case 2:
		_2.Bind();
		break;
	case 3:
		_3.Bind();
		break;
	case 4:
		_4.Bind();
		break;
	case 5:
		_5.Bind();
		break;
	case 6:
		_6.Bind();
		break;
	case 7:
		_7.Bind();
		break;
	case 8:
		_8.Bind();
		break;
	case 9:
		_9.Bind();
		break;
	}
}

void Overlay::DrawGold(int amount)
{
	number_va.Bind();
	number_vb.Bind();
	ib.Bind();
	shader.Bind();
	float offset=0.0;
	string number = to_string(amount);
	for (int i = 0;i < number.size();i++)
	{
		BindNumber(number[i] - '0');
		shader.SetUniform2f("u_off", offset, 0.0);
		offset += 0.02;
		renderer.Draw(number_va, ib, shader);
	}
}

void Overlay::DrawLvl(int lvl)
{
	float offset = -0.20;
	string number = to_string(lvl);
	for (int i = 0;i < number.size();i++)
	{
		BindNumber(number[i] - '0');
		shader.SetUniform2f("u_off", offset, -0.02);
		offset += 0.02;
		renderer.Draw(number_va, ib, shader);
	}
}

void Overlay::DrawSideStacks(int amount)
{
	float offset = -0.15;
	for (int i = 0;i < amount;i++)
	{
		side_stacks_texture.Bind();
		shader.SetUniform2f("u_off", offset, -0.00);
		offset += 0.01;
		renderer.Draw(number_va, ib, shader);
	}
}
