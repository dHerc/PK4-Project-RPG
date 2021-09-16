#include "Story.h"
Story::Story(Renderer& renderer, int ID) :vb(story_equipement_position, 16 * sizeof(float)), NPC_vb(story_NPC_position, 16 * sizeof(float)), ib(indices, 6), shader("Resource/shaders/basic.shader"), ID(ID)
{
	shared_ptr<Texture> NPC(new Texture("Resource/textures/NPC_Story_" + to_string(ID) + ".png"));
	NPC_texture = NPC;
	shared_ptr<Texture> wrong(new Texture("Resource/textures/NPC_Story_Wrong.png"));
	NPC_wrong = wrong;
	shared_ptr<Texture> text(new Texture("Resource/textures/Story_" + to_string(ID) + ".png"));
	texture = text;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	NPC_va.AddBuffer(NPC_vb, layout);
	shader.Bind();
	texture.get()->Bind();
	NPC_texture.get()->Bind();
	NPC_wrong.get()->Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform2f("u_off", 0.0, 0.0);
	shader.SetUniform2f("u_off_moving", 0.0, 0.0);
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();
}
void Story::Draw()
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	texture.get()->Bind();
	shader.Bind();
	renderer.Draw(va, ib, shader);
}

int Story::Trigger(int trigger_ID)
	{
	if(trigger_ID>6&&trigger_ID<11)
	{
		int sum=0;
		for (int i = 0;i < 4;i++)
			sum += activation[i];
		if (activation[(trigger_ID + 1) % 4] == 1 || sum == 0)
			activation[(trigger_ID + 2) % 4] = 1;
		else
		{
			for (int i = 0;i < 4;i++)
				activation[i] = 0;
		}
		activation[(trigger_ID + 2) % 4] = 1;
		sum = 0;
		for (int i = 0;i < 4;i++)
			sum += activation[i];
		if (sum == 4)
		{
			shared_ptr<Texture> NPC(new Texture("Resource/textures/NPC_Story_11.png"));
			NPC_texture = NPC;
			ID = 11;
			return 2;
		}
			return 0;
	}
	if (trigger_ID == ID)
	{
		ID++;
		shared_ptr<Texture> text(new Texture("Resource/textures/Story_" + to_string(ID) + ".png"));
		texture = text;
		shared_ptr<Texture> NPC(new Texture("Resource/textures/NPC_Story_" + to_string(ID) + ".png"));
		NPC_texture = NPC;
		if (trigger_ID > 0 && trigger_ID < 5)
			return 1;
		if (trigger_ID == 6||trigger_ID==11)
			return 1;
		return 0;
	}
	return 0;
}

void Story::Draw(int NPC_ID)
{
	NPC_va.Bind();
	NPC_vb.Bind();
	ib.Bind();
	shader.Bind();
	if (NPC_ID > 6 && NPC_ID < 11)
	{
		shared_ptr<Texture> NPC(new Texture("Resource/textures/NPC_Story_" + to_string(NPC_ID) + ".png"));
		NPC_texture = NPC;
		NPC_texture.get()->Bind();
		renderer.Draw(NPC_va, ib, shader);
	}
	else
	{
		if (ID == NPC_ID)
		{
			NPC_texture.get()->Bind();
		}
		else
		{
			NPC_wrong.get()->Bind();
		}
		renderer.Draw(NPC_va, ib, shader);
	}
}
