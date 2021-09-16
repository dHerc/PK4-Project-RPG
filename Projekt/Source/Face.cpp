#include "Face.h"
Face::Face(Renderer& renderer) :vb(position, 4 * 4 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"), renderer(renderer),
Archer("Resource/textures/Archer_character_face.png"), Warrior("Resource/textures/Warrior_character_face.png"), Mage("Resource/textures/Mage_character_face.png"), Assasin("Resource/textures/Assasin_character_face.png")
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
void Face::Draw(float pos_x, float pos_y,int char_nr)
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	shader.Bind();
	shader.SetUniform2f("u_off", pos_x, pos_y);
	switch (char_nr)
	{
	case 0:
		Archer.Bind();
		break;
	case 1:
		Warrior.Bind();
		break;
	case 2:
		Mage.Bind();
		break;
	case 3:
		Assasin.Bind();
		break;
	}
	renderer.Draw(va, ib, shader);
}
