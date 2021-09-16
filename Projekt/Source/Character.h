#pragma once
#include "Graphic_engine/Graphic_engine.h"
#include "Stats.h"
class Character :public Stats
{
private:
	float character_position[16] =
	{
		-0.08f, -0.15f, 0.0f, 0.0f,
		 0.08f, -0.15f, 1.0f, 0.0f,
		 0.08f, 0.15f, 1.0f, 1.0f,
		-0.08f, 0.15f, 0.0f, 1.0f
	};
	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};
	float character_offset_x;
	float character_offset_y;
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Shader shader;
	Texture texture_r;
	Texture texture_l;
	Texture attack_right_1;
	Texture attack_right_2;
	Texture attack_right_3;
	Texture attack_right_4;
	Texture attack_right_5;
	Texture attack_left_1;
	Texture attack_left_2;
	Texture attack_left_3;
	Texture attack_left_4;
	Texture attack_left_5;
	Texture side_attack_right_1;
	Texture side_attack_right_2;
	Texture side_attack_right_3;
	Texture side_attack_right_4;
	Texture side_attack_right_5;
	Texture side_attack_left_1;
	Texture side_attack_left_2;
	Texture side_attack_left_3;
	Texture side_attack_left_4;
	Texture side_attack_left_5;
	Texture effect_texture_right;
	Texture effect_texture_left;
	int& turn_right;
	int& attack;
	int& side_attack;
	int& skill;
	Renderer renderer;
public:
	Character(float & char_off_x,float & char_off_y,int & tr,int & attack,int & side_attack,int & skill,Renderer & renderer,string character_class,int hp,int base_dmg,int side_amount,int side_dmg,int char_class) :character_offset_x(char_off_x), character_offset_y(char_off_y),
		turn_right(tr),attack(attack),side_attack(side_attack),skill(skill),vb(character_position, 4 * 4 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"), 
		texture_r("Resource/textures/"+character_class+"_right.png"), texture_l("Resource/textures/" + character_class + "_left.png"),
		attack_right_1("Resource/textures/" + character_class + "_attack_right_1.png"), attack_right_2("Resource/textures/" + character_class + "_attack_right_2.png"), attack_right_3("Resource/textures/" + character_class + "_attack_right_3.png"), attack_right_4("Resource/textures/" + character_class + "_attack_right_4.png"), attack_right_5("Resource/textures/" + character_class + "_attack_right_5.png"),
		attack_left_1("Resource/textures/" + character_class + "_attack_left_1.png"), attack_left_2("Resource/textures/" + character_class + "_attack_left_2.png"), attack_left_3("Resource/textures/" + character_class + "_attack_left_3.png"), attack_left_4("Resource/textures/" + character_class + "_attack_left_4.png"), attack_left_5("Resource/textures/" + character_class + "_attack_left_5.png"),effect_texture_right("Resource/textures/" + character_class + "_effect_right.png"), effect_texture_left("Resource/textures/" + character_class + "_effect_left.png"),
		side_attack_right_1("Resource/textures/" + character_class + "_side_attack_right_1.png"), side_attack_right_2("Resource/textures/" + character_class + "_side_attack_right_2.png"), side_attack_right_3("Resource/textures/" + character_class + "_side_attack_right_3.png"), side_attack_right_4("Resource/textures/" + character_class + "_side_attack_right_4.png"), side_attack_right_5("Resource/textures/" + character_class + "_side_attack_right_5.png"),
		side_attack_left_1("Resource/textures/" + character_class + "_side_attack_left_1.png"), side_attack_left_2("Resource/textures/" + character_class + "_side_attack_left_2.png"), side_attack_left_3("Resource/textures/" + character_class + "_side_attack_left_3.png"), side_attack_left_4("Resource/textures/" + character_class + "_side_attack_left_4.png"), side_attack_left_5("Resource/textures/" + character_class + "_side_attack_left_5.png"),
		Stats(hp,base_dmg,100,side_amount,side_dmg,0,0,1,char_class)
	{
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		shader.Bind();
		texture_r.Bind();
		texture_l.Bind();
		shader.SetUniform1i("u_Texture", 0);
		shader.SetUniform2f("u_off", 0.0, -0.46);
		shader.SetUniform2f("u_off_moving", 0.0, 0.0);
		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();
	};
	void Draw();
	void Attack();
	void LvlUp();
};