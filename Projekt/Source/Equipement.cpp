#include "Equipement.h"
Equipement::Equipement(Owned& inventory, Description& description, Face& face, Skills& skills, Renderer& renderer, bool& right, bool& left, int& up, int& down, bool& confirm) :vb(position, 4 * 4 * sizeof(float)), slot_vb(slot_position, 4 * 4 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"),
texture("Resource/textures/Equipement.png"), empty_slot("Resource/textures/Empty_slot.png"), selected_slot("Resource/textures/Chosen_slot.png"), selection("Resource/textures/Selection.png"),
right(right), left(left), up(up), down(down), confirm(confirm), owned_items(inventory), description(description), face(face), skills(skills)
{
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	slot_va.AddBuffer(slot_vb, layout);
	shader.Bind();
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform2f("u_off", 0, 0);
	shader.SetUniform2f("u_off_moving", 0.0, 0.0);
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();
	allocator<Item> alloc;
	Item empty;
	for (int i = 0;i < 4;i++)
	{
		weapon[i] = allocate_shared<Item>(alloc, empty);
		sidearm[i] = allocate_shared<Item>(alloc, empty);
		armour[i] = allocate_shared<Item>(alloc, empty);
	}
}
void Equipement::Equip(Item it,int char_class)
{
	allocator<Item> alloc;
	switch (it.Get_type())
	{
	case 0:
		weapon[char_class] = allocate_shared<Item>(alloc, it);
		break;
	case 1:
		sidearm[char_class] = allocate_shared<Item>(alloc, it);
		break;
	case 2:
		armour[char_class] = allocate_shared<Item>(alloc, it);
		break;
	default:
		break;
	}
}

void Equipement::Draw(int &state,bool &leave)
{
	if (state < 4)
	{
		Change_slot();
		actual_item = 0;
	}
	if(state!=4)
	{
		va.Bind();
		vb.Bind();
		ib.Bind();
		texture.Bind();
		shader.Bind();
		shader.SetUniform2f("u_off", 0.0, 0.0);
		renderer.Draw(va, ib, shader);
		
		for (int i = 0;i < 4;i++)
		{
			slot_va.Bind();
			slot_vb.Bind();
			ib.Bind();
			shader.Bind();
			empty_slot.Bind();
			shader.SetUniform2f("u_off", -0.9, 0.75 - (i % 4) * 0.5);
			renderer.Draw(slot_va, ib, shader);
			face.Draw(-0.9, 0.75 - (i % 4) * 0.5, i);
		}
		slot_va.Bind();
		slot_vb.Bind();
		ib.Bind();
		shader.Bind();
		for (int i = 0;i < 4;i++)
		{
			empty_slot.Bind();
			shader.SetUniform2f("u_off", -0.6, 0.75 - (i % 4) * 0.5);
			renderer.Draw(slot_va, ib, shader);
			weapon[i]->Bind_texture();
			renderer.Draw(slot_va, ib, shader);
		}
		for (int i = 0;i < 4;i++)
		{
			empty_slot.Bind();
			shader.SetUniform2f("u_off", -0.3, 0.75 - (i % 4) * 0.5);
			renderer.Draw(slot_va, ib, shader);
			sidearm[i]->Bind_texture();
			renderer.Draw(slot_va, ib, shader);
		}
		for (int i = 0;i < 4;i++)
		{
			empty_slot.Bind();
			shader.SetUniform2f("u_off", -0, 0.75 - (i % 4) * 0.5);
			renderer.Draw(slot_va, ib, shader);
			armour[i]->Bind_texture();
			renderer.Draw(slot_va, ib, shader);
		}
		selected_slot.Bind();
		shader.SetUniform2f("u_off", -0.9 + (actual_slot % 4 * 0.3), 0.75 - (actual_slot / 4) * 0.5);
		renderer.Draw(slot_va, ib, shader);
	}
	if (leave)
	{
		if (state == 2)
			state = 3;
		if (state == 4)
			state = 5;
	}
	else
	{
		if (state == 3)
			state = 6;
		if (state == 5)
			state = 2;
	}
	if (confirm)
		wait_for_release = true;
	if (not confirm && wait_for_release)
	{
		state = 4;
		wait_for_release = false;
	}
	if (state == 4)
		Select_slot();
}

void Equipement::Draw_selection()
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	selection.Bind();
	shader.Bind();
	shader.SetUniform2f("u_off", 0.0, 0.0);
	renderer.Draw(va, ib, shader);
}

void Equipement::Change_slot()
{
	if (delay == 0)
	{
		if (right)
		{
			actual_slot += 1;
			if (actual_slot % 4 == 0)
				actual_slot -= 4;
			delay += 20;
		}
		if (left)
		{
			actual_slot -= 1;
			if ((actual_slot + 4) % 4 == 3)
				actual_slot += 4;
			delay += 20;
		}
		if (up)
		{
			actual_slot -= 4;
			if (actual_slot < 0)
				actual_slot += 16;
			delay += 20;
		}
		if (down)
		{
			actual_slot += 4;
			actual_slot = actual_slot % 16;
			delay += 20;
		}
	}
	if(delay>0)
		delay--;
}

void Equipement::ChangeSelectedItem(int amount)
{
	if (not delay)
	{
		if (right)
		{
			actual_item += 1;
			if (actual_item == amount)
				actual_item = 0;
			delay += 20;
		}
		if (left)
		{
			actual_item -= 1;
			if (actual_item == -1)
				actual_item = amount-1;
			delay += 20;
		}
	}
	if (delay > 0)
		delay--;
}

void Equipement::Select_slot()
{
	Draw_selection();
	switch (actual_slot%4)
	{
	case 0:
		Selection_skills(actual_slot / 4);
		break;
	case 1:
		Selection_weapon(actual_slot / 4);
		break;
	case 2:
		Selection_sidearm(actual_slot / 4);
		break;
	case 3:
		Selection_armour(actual_slot / 4);
		break;
	}
}

void Equipement::Selection_skills(int char_class)
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	skills.Bind(char_class);
	shader.Bind();
	shader.SetUniform2f("u_off", 0.0, 0.0);
	renderer.Draw(va, ib, shader);
}

void Equipement::Selection_weapon(int char_class)
{
	slot_va.Bind();
	slot_vb.Bind();
	ib.Bind();
	shader.Bind();
	empty_slot.Bind();
	shader.SetUniform2f("u_off", -0.5,0.4);
	renderer.Draw(slot_va, ib, shader);
	switch (char_class)
	{
	case 0:
		weapon[0]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		weapon[0]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	case 1:
		weapon[1]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		weapon[1]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	case 2:
		weapon[2]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		weapon[2]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	case 3:
		weapon[3]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		weapon[3]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	}
	auto it = owned_items.weapons.begin();
	int i=0;
	bool loop = true;
	while(loop)
	{
		if (it == owned_items.weapons.end())
			loop = 0;
		else
		{
			if (it->get()->Get_class() == char_class)
			{
				if (i >= actual_item && i < actual_item + 5)
				{
					slot_va.Bind();
					slot_vb.Bind();
					ib.Bind();
					shader.Bind();
					empty_slot.Bind();
					shader.SetUniform2f("u_off", 0.2 + 0.2 * (i-actual_item), 0.4);
					renderer.Draw(slot_va, ib, shader);
					it->get()->Bind_texture();
					renderer.Draw(slot_va, ib, shader);
					if (i == actual_item)
					{
						it->get()->Bind_description();
						description.Draw(1.0, 0.05);
					}
				}
				if (confirm && i == actual_item)
					Equip(*it->get(),char_class);
				i++;
			}
				it++;
		}
	}
	if (i)
	{
		ChangeSelectedItem(i);
		selected_slot.Bind();
		shader.SetUniform2f("u_off", 0.2, 0.4);
		renderer.Draw(slot_va, ib, shader);
	}
}

void Equipement::Selection_sidearm(int char_class)
{
	slot_va.Bind();
	slot_vb.Bind();
	ib.Bind();
	shader.Bind();
	empty_slot.Bind();
	shader.SetUniform2f("u_off", -0.5, 0.4);
	renderer.Draw(slot_va, ib, shader);
	switch (char_class)
	{
	case 0:
		sidearm[0]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		sidearm[0]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	case 1:
		sidearm[1]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		sidearm[1]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	case 2:
		sidearm[2]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		sidearm[2]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	case 3:
		sidearm[3]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		sidearm[3]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	}
	auto it = owned_items.sidearms.begin();
	int i = 0;
	bool loop = true;
	while (loop)
	{
		if (it == owned_items.sidearms.end())
			loop = 0;
		else
		{
			if (it->get()->Get_class() == char_class)
			{
				if (i >= actual_item && i < actual_item + 5)
				{
					slot_va.Bind();
					slot_vb.Bind();
					ib.Bind();
					shader.Bind();
					empty_slot.Bind();
					shader.SetUniform2f("u_off", 0.2 + 0.2 * (i - actual_item), 0.4);
					renderer.Draw(slot_va, ib, shader);
					it->get()->Bind_texture();
					renderer.Draw(slot_va, ib, shader);
					if (i == actual_item)
					{
						it->get()->Bind_description();
						description.Draw(1.0, 0.05);
					}
				}
				if (confirm && i == actual_item)
					Equip(*it->get(), char_class);
				i++;
			}
			it++;
		}
	}
	if (i)
	{
		ChangeSelectedItem(i % 10);
		selected_slot.Bind();
		shader.SetUniform2f("u_off", 0.2, 0.4);
		renderer.Draw(slot_va, ib, shader);
	}
}

void Equipement::Selection_armour(int char_class)
{
	slot_va.Bind();
	slot_vb.Bind();
	ib.Bind();
	shader.Bind();
	empty_slot.Bind();
	shader.SetUniform2f("u_off", -0.5, 0.4);
	renderer.Draw(slot_va, ib, shader);
	switch (char_class)
	{
	case 0:
		armour[0]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		armour[0]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	case 1:
		armour[1]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		armour[1]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	case 2:
		armour[2]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		armour[2]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	case 3:
		armour[3]->Bind_texture();
		renderer.Draw(slot_va, ib, shader);
		armour[3]->Bind_description();
		description.Draw(0.1, 0.05);
		break;
	}
	auto it = owned_items.armours.begin();
	int i = 0;
	bool loop = true;
	while (loop)
	{
		if (it == owned_items.armours.end())
			loop = 0;
		else
		{
			if (it->get()->Get_class() == char_class)
			{
				if (i >= actual_item && i < actual_item + 5)
				{
					slot_va.Bind();
					slot_vb.Bind();
					ib.Bind();
					shader.Bind();
					empty_slot.Bind();
					shader.SetUniform2f("u_off", 0.2 + 0.2 * (i - actual_item), 0.4);
					renderer.Draw(slot_va, ib, shader);
					it->get()->Bind_texture();
					renderer.Draw(slot_va, ib, shader);
					if (i == actual_item)
					{
						it->get()->Bind_description();
						description.Draw(1.0, 0.05);
					}
				}
				if (confirm && i == actual_item)
					Equip(*it->get(), char_class);
				i++;
			}
			it++;
		}
	}
	if (i)
	{
		ChangeSelectedItem(i % 10);
		selected_slot.Bind();
		shader.SetUniform2f("u_off", 0.2, 0.4);
		renderer.Draw(slot_va, ib, shader);
	}
}

void Equipement::AddItem(Item it)
{
	owned_items.Add_item(it);
}

void Equipement::TriggerEQ(int char_nr, int char_pos[2], int world[1920][216], Character& character, bool mode)
{
	weapon[0].get()->Trigger(char_pos,world,character,mode);
}
