#include "Menu.h"
Menu::Menu(Renderer& renderer, int& up, int& down, bool& confirm) :vb(position, 4 * 4 * sizeof(float)), button_vb(button_position, 4 * 4 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"), up(up), down(down), confirm(confirm),
texture("Resource/textures/Background.png"),
button_release_1("Resource/textures/button_release_1.png"), button_release_2("Resource/textures/button_release_2.png"), button_release_3("Resource/textures/button_release_3.png"), options_button_release_1("Resource/textures/options_button_release_1.png"), options_button_release_2("Resource/textures/options_button_release_2.png"),
button_press_1("Resource/textures/button_press_1.png"), button_press_2("Resource/textures/button_press_2.png"), button_press_3("Resource/textures/button_press_3.png"), options_button_press_1("Resource/textures/options_button_press_1.png"), options_button_press_2("Resource/textures/options_button_press_2.png"),
indicator_1("Resource/textures/indicator_1.png"), indicator_2("Resource/textures/indicator_2.png"), indicator_3("Resource/textures/indicator_3.png"), indicator_4("Resource/textures/indicator_4.png"), indicator_5("Resource/textures/indicator_5.png")
{
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	button_va.AddBuffer(button_vb, layout);
	shader.Bind();
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform2f("u_off", 0.0, 0.0);
	shader.SetUniform2f("u_off_moving", 0.0, 0.0);
	va.Unbind();
	button_va.Unbind();
	vb.Unbind();
	button_vb.Unbind();
	ib.Unbind();
	shader.Unbind();
}
int Menu::Draw(int& state,int & difficulty)
{
	if (confirm)
		confirmation = 1;
	if (up)
		go_up++;
	if(go_up)
		if (go_up == 40||not up)
		{
			selected_option--;
			go_up = 0;
		}
	if (selected_option == -1)
		selected_option = 2;
	if (down)
		go_down++;
	if(go_down)
		if (go_down == 40||not down)
		{
			selected_option++;
			go_down = 0;
		}
	if (selected_option == 3)
		selected_option = 0;
	Draw_background();
	if (menu_type == 0)
	{
		if (selected_option == 0)
			Draw_buttons(0);
		else if (selected_option == 1)
			Draw_buttons(1);
		else
			Draw_buttons(2);
		if (not confirm&&confirmation)
		{
			if (selected_option == 0)
				state = 1;
			if (selected_option == 1)
			{
				menu_type = 1;
				selected_option = 0;
			}
			if (selected_option == 2)
				return 1;
			confirmation = 0;
		}
	}
	if (menu_type == 1)
	{
		if (selected_option == 0)
			Draw_options_buttons(0,difficulty);
		else if (selected_option == 1)
			Draw_options_buttons(1,difficulty);
		else
			Draw_options_buttons(2,difficulty);
		if (not confirm&&confirmation)
		{
			if (selected_option == 0)
				return 2;
			if (selected_option == 1)
			{
				difficulty++;
				if (difficulty == 6)
					difficulty = 1;
			}
			if (selected_option == 2)
			{
				menu_type = 0;
				selected_option = 0;
			}
			confirmation = 0;
		}
	}
	return 0;
}

void Menu::Draw_background()
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	texture.Bind();
	shader.Bind();
	shader.SetUniform2f("u_off", 0.0, 0.0);
	renderer.Draw(va, ib, shader);
}

void Menu::Draw_buttons(int pressed)
{
	button_va.Bind();
	button_vb.Bind();
	ib.Bind();
	shader.Bind();
	if (pressed == 0)
	{
		button_press_1.Bind();
		shader.SetUniform2f("u_off", 0.0, 0.6);
		renderer.Draw(button_va, ib, shader);
	}
	else
	{
		button_release_1.Bind();
		shader.SetUniform2f("u_off", 0.0, 0.6);
		renderer.Draw(button_va, ib, shader);
	}
	if (pressed == 1)
	{
		button_press_2.Bind();
		shader.SetUniform2f("u_off", 0.0, 0.1);
		renderer.Draw(button_va, ib, shader);
	}
	else
	{
		button_release_2.Bind();
		shader.SetUniform2f("u_off", 0.0, 0.1);
		renderer.Draw(button_va, ib, shader);
	}
	if (pressed == 2)
	{
		button_press_3.Bind();
		shader.SetUniform2f("u_off", 0.0, -0.4);
		renderer.Draw(button_va, ib, shader);
	}
	else
	{
		button_release_3.Bind();
		shader.SetUniform2f("u_off", 0.0, -0.4);
		renderer.Draw(button_va, ib, shader);
	}
}

void Menu::Draw_options_buttons(int pressed,int difficulty)
{
	if (pressed == 0)
	{
		button_va.Bind();
		button_vb.Bind();
		ib.Bind();
		options_button_press_1.Bind();
		shader.Bind();
		shader.SetUniform2f("u_off", 0.0, 0.6);
		renderer.Draw(button_va, ib, shader);
	}
	else
	{
		button_va.Bind();
		button_vb.Bind();
		ib.Bind();
		options_button_release_1.Bind();
		shader.Bind();
		shader.SetUniform2f("u_off", 0.0, 0.6);
		renderer.Draw(button_va, ib, shader);
	}
	if (pressed == 1)
	{
		button_va.Bind();
		button_vb.Bind();
		ib.Bind();
		options_button_press_2.Bind();
		shader.Bind();
		shader.SetUniform2f("u_off", 0.0, 0.1);
		renderer.Draw(button_va, ib, shader);
	}
	else
	{
		button_va.Bind();
		button_vb.Bind();
		ib.Bind();
		options_button_release_2.Bind();
		shader.Bind();
		shader.SetUniform2f("u_off", 0.0, 0.1);
		renderer.Draw(button_va, ib, shader);
	}
	switch (difficulty)
	{
	case 1:
		indicator_1.Bind();
		break;
	case 2:
		indicator_2.Bind();
		break;
	case 3:
		indicator_3.Bind();
		break;
	case 4:
		indicator_4.Bind();
		break;
	case 5:
		indicator_5.Bind();
		break;
	}
	renderer.Draw(button_va, ib, shader);
	if (pressed == 2)
	{
		button_va.Bind();
		button_vb.Bind();
		ib.Bind();
		button_press_3.Bind();
		shader.Bind();
		shader.SetUniform2f("u_off", 0.0, -0.4);
		renderer.Draw(button_va, ib, shader);
	}
	else
	{
		button_va.Bind();
		button_vb.Bind();
		ib.Bind();
		button_release_3.Bind();
		shader.Bind();
		shader.SetUniform2f("u_off", 0.0, -0.4);
		renderer.Draw(button_va, ib, shader);
	}
}
