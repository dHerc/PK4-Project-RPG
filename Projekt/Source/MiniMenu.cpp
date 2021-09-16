#include "MiniMenu.h"
Minimenu::Minimenu(Renderer& renderer, Description& description, int& up, int& down, bool& right, bool& left, bool& confirm, bool& leave) :description(description), vb(position, 4 * 4 * sizeof(float)), button_vb(button_position, 4 * 4 * sizeof(float)), slot_vb(slot_position, 16 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"), up(up), down(down), confirm(confirm), left(left), right(right), leave(leave),
texture("Resource/textures/Mini_menu_back.png"), button_1("Resource/textures/button_1.png"), button_1_1("Resource/textures/button_1_1.png"), button_2("Resource/textures/button_2.png"), button_3("Resource/textures/button_3.png"), selected_button("Resource/textures/selected_button.png"), empty_slot("Resource/textures/Empty_slot.png"), selected_slot("Resource/textures/Chosen_slot.png"), renderer(renderer)
{
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	button_va.AddBuffer(button_vb, layout);
	slot_va.AddBuffer(slot_vb, layout);
	shader.Bind();
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform2f("u_off", 0.0, 0.0);
	shader.SetUniform2f("u_off_moving", 0.0, 0.0);
	va.Unbind();
	button_va.Unbind();
	slot_va.Unbind();
	vb.Unbind();
	button_vb.Unbind();
	slot_vb.Unbind();
	ib.Unbind();
	shader.Unbind();
}
int Minimenu::Draw(int options[3])
{
	if (leave)
		leaving = 1;
	if (up)
		go_up++;
	if (go_up)
		if (go_up == 40 || not up)
		{
			selected_option--;
			go_up = 0;
		}
	if (selected_option == -1)
		selected_option = 2;
	if (down)
		go_down++;
	if (go_down)
		if (go_down == 40 || not down)
		{
			selected_option++;
			go_down = 0;
		}
	if (options[0] && options[1])
	{
		if (selected_option == 3)
			selected_option = 0;
		if (selected_option == -1)
			selected_option = 2;
	}
	else
	{
		selected_option = 0;
	}
	Draw_background();
	Draw_buttons(options);
	if (leaving && not leave)
	{
		leaving = 0;
		return 4;
	}
	if (GetConfirmation())
	{
		switch (selected_option)
		{
		case 0:
			return 1;
		case 1:
			return 2;
		case 2:
			return 3;
		}
	}
	else
		return 0;
}

void Minimenu::Draw_background()
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	texture.Bind();
	shader.Bind();
	shader.SetUniform2f("u_off", 0.0, 0.0);
	renderer.Draw(va, ib, shader);
}

void Minimenu::Draw_buttons(int options[3])
{
	button_va.Bind();
	button_vb.Bind();
	ib.Bind();
	shader.Bind();
	if (options[0])
	{
		if (options[1])
			button_1.Bind();
		else
			button_1_1.Bind();
		shader.SetUniform2f("u_off", 0.0, -0.2);
		renderer.Draw(button_va, ib, shader);
	}
	if (options[1])
	{
	button_2.Bind();
	shader.SetUniform2f("u_off", 0.0, -0.5);
	renderer.Draw(button_va, ib, shader);
	}
	if (options[2])
	{
		button_3.Bind();
		shader.SetUniform2f("u_off", 0.0, -0.8);
		renderer.Draw(button_va, ib, shader);
	}
	selected_button.Bind();
	shader.SetUniform2f("u_off", 0.0, -0.2-selected_option*0.3);
	renderer.Draw(button_va, ib, shader);
}

int Minimenu::Draw_item_shop()
{
	Draw_background();
	if (leave)
		leaving = 1;
	else if (leaving)
		return -1;
	auto it = shop_items.begin();
	int i = 0;
	bool loop = true;
	while (loop)
	{
		if (it == shop_items.end())
			loop = 0;
		else
		{
			if (i >= actual_item && i < actual_item + 5)
			{
				slot_va.Bind();
				slot_vb.Bind();
				ib.Bind();
				shader.Bind();
				empty_slot.Bind();
				shader.SetUniform2f("u_off", -0.4 + 0.2 * (i - actual_item), -0.2);
				renderer.Draw(slot_va, ib, shader);
				it->get()->Bind_texture();
				renderer.Draw(slot_va, ib, shader);
				if (i == actual_item)
				{
					it->get()->Bind_description();
					description.Draw(0.55, -0.1);
				}
			}
			if (confirm)
				confirmation = 1;
			else if (confirmation == 1 && i == actual_item)
			{
				confirmation = 0;
				return i;
			}
			i++;
			it++;
		}
	}
	if (i)
	{
		ChangeSelectedItem(i);
		selected_slot.Bind();
		shader.SetUniform2f("u_off", -0.4, -0.2);
		renderer.Draw(slot_va, ib, shader);
	}
	return -2;
}

void Minimenu::Set_item_list(int ID)
{
	switch (ID)
	{
	case 1:
		for (int i = 0;i < 12;i++)
		{
			Item it(GetItem(i));
			shared_ptr<Item> p(new Item(it));
			shop_items.push_back(move(p));
		}
		break;
	}
			
}

Item Minimenu::GetItem(int ID)
{
	switch (ID)
	{
	case -1:
		return Item(70, 30, "Nature_Dagger", 0, 0, 1);
	case 0:
		return Item(20, 10, "Wooden_Dagger", 0, 0);
	case 1:
		return Item(40, 5, "Wooden_Sword", 0, 1);
	case 2:
		return Item(30, 5, "Wooden_Staff", 0, 2);
	case 3:
		return Item(10, 20, "Wooden_Knife", 0, 3);
	case 4:
		return Item(40, 5, "Shortbow", 1, 0);
	case 5:
		return Item(50, 2, "Wooden_Shield", 1, 1);
	case 6:
		return Item(60, 4, "Light_Book", 1, 2);
	case 7:
		return Item(10, 10, "Wooden_Throwing_Daggers", 1, 3);
	case 8:
		return Item(250, 120, "Light_Armour", 2, 0);
	case 9:
		return Item(600, 90, "Wooden_Armour", 2, 1);
	case 10:
		return Item(110, 200, "Thin_Robe", 2, 2);
	case 11:
		return Item(170, 120, "Thin_Clothes", 2, 3);
	}
}

int Minimenu::CheckPrice(int ID)
{
	if(ID>-1&&ID<12)
		return 0;
}

void Minimenu::ChangeSelectedItem(int amount)
{
	if (not delay)
	{
		if (right)
		{
			actual_item += 1;
			if (actual_item == amount)
				actual_item = 0;
			delay += 40;
		}
		if (left)
		{
			actual_item -= 1;
			if (actual_item == -1)
				actual_item = amount - 1;
			delay += 40;
		}
	}
	if (delay > 0)
		delay--;
}

bool Minimenu::GetConfirmation()
{
	if (confirm)
		confirmation = 1;
	if (confirmation && not confirm)
	{
		confirmation = 0;
		return true;
	}
	return false;

}
