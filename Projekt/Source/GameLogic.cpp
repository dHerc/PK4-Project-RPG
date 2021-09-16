#include "GameLogic.h"
GameLogic::GameLogic(Character& archer_char, Character& warrior_char, Character& mage_char, Character& assasin_char, Background& bg_class, Menu& menu, Minimenu& minimenu, Equipement& equipement, Story& story, Overlay& overlay, Renderer& renderer, int& lvl_nr, int& state, bool& open_menu, bool& open_equipement,int &difficulty) :archer(archer_char), warrior(warrior_char), mage(mage_char), assasin(assasin_char), background(bg_class), menu(menu), minimenu(minimenu), equipement(equipement), story(story), overlay(overlay), lvl_nr(lvl_nr), state(state), open_menu(open_menu), open_equipement(open_equipement),difficulty(difficulty)
{
	character = &archer;
	srand(time(NULL));
	if (lvl_nr <= 4)
	{
		for (int i = 0;i < 192;i++)
			for (int j = 0; j < 108;j++)
				world[i][j] = 0;
		for (int i = 0;i < 192;i++)
			for (int j = 0; j < 4;j++)
				world[i][j] = 2;
		for (int j = 0; j < 108;j++)
		{
			for (int i = 0;i < 5;i++)
			{
				world[i][j] = 2;
				world[191 - i][j] = 2;
			}
		}
	}
	if (lvl_nr == 5)
	{
		for (int i = 0;i < 960;i++)
			for (int j = 0; j < 216;j++)
				world[i][j] = 0;
		for (int i = 0;i < 960;i++)
			for (int j = 0; j < 4;j++)
				world[i][j] = 1;
		for (int j = 0; j < 216;j++)
		{
			for (int i = 0;i < 5;i++)
			{
				world[i][j] = 2;
				world[955 - i][j] = 2;
			}
		}
		for (int i = 200;i < 230;i++)
			for (int j = 4;j < 15;j++)
			{
				world[i][j] = 204;
			}
		for (int i = 550;i < 580;i++)
			for (int j = 59;j < 70;j++)
			{
				world[i][j] = 205;
			}
		for (int i = 500;i < 530;i++)
			for (int j = 120;j < 131;j++)
			{
				world[i][j] = 206;
			}
		for (int i = 800;i < 830;i++)
			for (int j = 4;j < 15;j++)
			{
				world[i][j] = 203;
			}
		for (int i = 0;i < 50;i++)
		{
			world[305 + i][20] = 1;
			world[360 + i][40] = 1;
			world[415 + i][60] = 1;
			world[360 + i][80] = 1;
			world[415 + i][100] = 1;
			world[545 + i][100] = 1;
		}
		for (int i = 0;i < 100;i++)
		{
			world[465 + i][120] = 1;
			world[495 + i][60] = 1;
		}
	}
	if (lvl_nr == 6)
	{
		for (int i = 0;i < 576;i++)
			for (int j = 0; j < 216;j++)
				world[i][j] = 0;
		for (int i = 0;i < 576;i++)
			for (int j = 0; j < 4;j++)
				world[i][j] = 2;
		for (int j = 0; j < 216;j++)
		{
			for (int i = 0;i < 5;i++)
			{
				world[i][j] = 2;
				world[575 - i][j] = 2;
			}
		}
	}
};
template<class T>
inline void GameLogic::Draw(list<shared_ptr<T>>list)
{
	for (auto& i : list)
	{
		i.get()->Draw();
	}
}
int GameLogic::RenderFrame(float character_offset[2])
{
	renderer.Clear();
	if (state == 7)
	{
		state = 1;
		return 2;
	}
	if (open_menu&&state==1)
		state = 0;
	if (open_equipement&&state==1)
		state = 2;
	if (state == 0)
	{
		if (menu.Draw(state,difficulty)==1)
			return 1;
		if (menu.Draw(state, difficulty) == 2)
			return 3;
	}
	if(state == 1||state>=8)
	{
		background.Draw(lvl_nr);
		character->Draw();
		Draw(enemies);
		Draw(drops);
		Draw(projectiles);
		Draw(npcs);
		if(lvl_nr==6)
			boss.get()->Draw();
		overlay.Draw(actual_class);
		overlay.DrawBar(0, (float)character->health, (float)character->max_health);
		overlay.DrawBar(1, (float)character->mana, (float)character->max_mana);
		overlay.DrawBar(2, (float)character->exp, (float)100.0);
		overlay.DrawGold(character->gold);
		overlay.DrawLvl(character->lvl);
		overlay.DrawSideStacks(character->side_amount);
	}
	if (state > 1 && state < 6)
	{
		equipement.Draw(state, open_menu);
		if (state != 4)
			story.Draw();
	}
	if (state == 6)
	{
		UpdateStats();
		state = 1;
	}
	if (state == 8)
	{
		int action = minimenu.Draw(mini_menu_options);
		if (action == 1)
		{
			state = 10;
		}
		else if (action == 2)
		{
			minimenu.Set_item_list(mini_menu_options[1]);
			state = 9;
		}
		else if (action == 3)
		{
			if (character->gold >= mini_menu_options[2]&&character->side_amount<character->max_side_amount)
			{
				archer.gold -= mini_menu_options[2];
				warrior.gold -= mini_menu_options[2];
				mage.gold -= mini_menu_options[2];
				assasin.gold -= mini_menu_options[2];
				character->side_amount++;
				if (character->char_class == 3)
					character->side_amount = min(character->side_amount + 2, character->max_side_amount);
			}
		}
		else if(action==4)
			state = 1;
	}
	if (state == 9)
	{
		int bought = minimenu.Draw_item_shop();
		if (bought == -1)
			state = 1;
		if (bought>-1)
		{
			int price = minimenu.CheckPrice(bought);
			if (character->gold >=price)
			{
				equipement.AddItem(minimenu.GetItem(bought-1 + mini_menu_options[1]));
				archer.gold -= price;
				warrior.gold -= price;
				mage.gold -= price;
				assasin.gold -= price;
			}
		}
	}
	if (state == 10)
	{
		minimenu.Draw_background();
		story.Draw(mini_menu_options[0]);
		if (minimenu.GetConfirmation())
		{
			state = 1;
			int trigger = story.Trigger(mini_menu_options[0]);
			if (trigger==1)
			{
				lvl_nr++;
				return 2;
			}
			if (trigger == 2)
				ActivateAltars(character_offset);
		}
	}
	return 0;
}
void GameLogic::TriggerEQ(bool mode,int char_pos[2])
{
	equipement.TriggerEQ(actual_class, char_pos, world, archer, mode);
}
void GameLogic::Movement(bool &move_right, bool &move_left,int &turn_right, int &jump, float character_offset[2], int char_pos[2])
{
	if (state != 1)
		return;
	if (move_right)
	{
		if (world[char_pos[0] + 3][char_pos[1]] == 0)
		{
			turn_right = 1;
			character_offset[0] += 0.0104166;
			char_pos[0] += 1;
		}
	}
	if (move_left)
	{
		if (world[char_pos[0] - 4][char_pos[1]] == 0)
		{
			turn_right = 0;
			character_offset[0] -= 0.0104166;
			char_pos[0] -= 1;
		}
	}
	int under_feet = 0;
	for (int i = -2;i < 3;i++)
		under_feet += world[char_pos[0] + i][char_pos[1] - 1];
	if (under_feet == 0)
		v -= 1;
	if (jump == 1 && under_feet != 0)
	{
		v += 16;
		character_offset[1] += 0.0185185;
		char_pos[1] += 1;
		jump = 2;
	}
	for (int i = 0;i < (int)(v / 4);i++)
	{
		character_offset[1] += 0.0185185;
		char_pos[1] += 1;
	}
	for (int i = 0;i > (int)(v / 4);i--)
	{
		for (int i = -2;i < 3;i++)
			under_feet += world[char_pos[0] + i][char_pos[1] - 1];
		if (under_feet == 0)
		{
			character_offset[1] -= 0.0185185;
			char_pos[1] -= 1;
		}
		else
			v = 0;
	}
}
void GameLogic::Enemy_Movement(int char_pos[2])
{
	if (state != 1)
		return;
	for (auto& i : enemies)
	{
		i.get()->Move(char_pos,world);
		int dmg_took;
		i.get()->Attack(char_pos,dmg_took);
		TakeDamage(dmg_took);
	}
}


void GameLogic::SetEnemies()
{
	if (state != 1)
		return;
	for (auto& i : enemies)
	{
		for (int rows = i.get()->Get_x() - 3;rows < i.get()->Get_x() + 3;rows++)
		{
			for (int columns = i.get()->Get_y()-1;columns < i.get()->Get_y() +8;columns++)
			{
				if(world[rows][columns]==0)
					world[rows][columns] = i.get()->Get_ID();
			}
		}
	}
}
void GameLogic::ResetEnemies()
{
	if (state != 1)
		return;
	for (auto& i : enemies)
	{
		for (int rows = i.get()->Get_x() - 3;rows < i.get()->Get_x() + 3;rows++)
		{
			for (int columns = i.get()->Get_y()-1;columns < i.get()->Get_y() + 8;columns++)
			{
				if(world[rows][columns]==i.get()->Get_ID())
					world[rows][columns] = 0;
			}
		}
	}
}
void GameLogic::Meele(int attack,int char_pos[2],int right)
{
	if (state != 1)
		return;
	int entity_hit[3] = { 0,0,0 };
	if (attack >=50-character->attack_speed/2&&attack <= 50+character->attack_speed/2 )
	{
		if (right)
		{
			if (world[char_pos[0] + range_x][char_pos[1] + 7] < 100 && world[char_pos[0] + range_x][char_pos[1] + 7]>9)
			{
				entity_hit[0]=world[char_pos[0] + range_x][char_pos[1] + 7];
			}
			if (world[char_pos[0] + 7][char_pos[1] + range_y] < 100 && world[char_pos[0] + 7][char_pos[1] + range_y]>9)
			{
				entity_hit[1] = world[char_pos[0] + 7][char_pos[1] + range_y];
			}
			if (world[char_pos[0] + 7][char_pos[1] + 7] < 100 && world[char_pos[0] + 7][char_pos[1] + 7]>9)
			{
				entity_hit[2] = world[char_pos[0] + 7][char_pos[1] + 7];
			}
		}
		else
		{
			if (world[char_pos[0] - range_x][char_pos[1] + 7] < 100 && world[char_pos[0] - range_x][char_pos[1] + 7]>9)
			{
				entity_hit[0] = world[char_pos[0] - range_x][char_pos[1] + 7];
			}
			if (world[char_pos[0] - 7][char_pos[1] + range_y] < 100 && world[char_pos[0] - 7][char_pos[1] + range_y]>9)
			{
				entity_hit[1] = world[char_pos[0] - 7][char_pos[1] + range_y];
			}
			if (world[char_pos[0] - 7][char_pos[1] + 7] < 100 && world[char_pos[0] - 7][char_pos[1] + 7]>9)
			{
				entity_hit[2] = world[char_pos[0] - 7][char_pos[1] + 7];
			}
		}
		if (entity_hit[0] == entity_hit[1]&&entity_hit[0]==entity_hit[2])
		{
			if(entity_hit[0])
			DealDamage(entity_hit[0],0);
		}
		else
		{
			if (entity_hit[0])
				DealDamage(entity_hit[0],0);
			if (entity_hit[1] != entity_hit[0])
			{
				if (entity_hit[1])
					DealDamage(entity_hit[1],0);
			}
			if (entity_hit[2] != entity_hit[1]&&entity_hit[2] != entity_hit[0])
			{
				if (entity_hit[2])
					DealDamage(entity_hit[2],0);
			}
		}
	}
}

void GameLogic::ActivateAltars(float character_offset[2])
{
	int options[3] = { 0,0,0 };
	InitializeNPC(character_offset, 215, 10, "Resource/textures/Magic_Ball.png", 210, 0, options);
	InitializeNPC(character_offset, 515, 125, "Resource/textures/Magic_Ball.png", 210, 0, options);
	InitializeNPC(character_offset, 815, 10, "Resource/textures/Magic_Ball.png", 210, 0, options);
	InitializeNPC(character_offset, 565, 65, "Resource/textures/Magic_Ball.png", 210, 0, options);
}

void GameLogic::TriggerBoss(float character_offset[2])
{
	if (lvl_nr == 6)
	{
		if (boss->Trigger(*character))
		{
			InitializeEnemies(character_offset);
		}
		if (boss->health <= 0)
		{
			lvl_nr = 7;
			story.Trigger(12);
			for (int i = -3;i < 4;i++)
				for (int j = -1;j < 7;j++)
					world[300 + i][5 + j] = 0;
			InitializeDrop(character_offset, 320, 5, "Resource/textures/Nature_Dagger.png", 115, 4, -1);
		}
	}
}

void GameLogic::Interact(int attack, int char_pos[2], int right)
{
	if (attack==1)
	{
		if (right)
		{
			if (world[char_pos[0] + 7][char_pos[1] + 7] < 300 && world[char_pos[0] + 7][char_pos[1] + 7]>200)
				GetInteract(world[char_pos[0] + 7][char_pos[1] + 7]);
		}
		else
		{
			if (world[char_pos[0] - 7][char_pos[1] + 7] < 300 && world[char_pos[0] - 7][char_pos[1] + 7]>200)
				GetInteract(world[char_pos[0] - 7][char_pos[1] + 7]);
		}
		attack = 0;
	}
}

void GameLogic::GetInteract(int ID)
{
	auto i = npcs.begin();
	for (i;i != npcs.end(); i++)
	{
		if (i->get()->Get_ID() == ID)
			break;
	}
	if (i != npcs.end())
	{
		if(i->get()->Interact())
		{
			state = 8;
			mini_menu_options[0] = i->get()->Get_menu_story();
			mini_menu_options[1] = i->get()->Get_menu_items();
			mini_menu_options[2] = i->get()->Get_menu_sidearm();
		}
	}
}

void GameLogic::SideAttack(float character_offset[2],int & side_attack, int char_pos[2], int right, bool blocking)
{
	int hit;
	auto i = projectiles.begin();
	for (i;i != projectiles.end(); i++)
	{
		hit = i->get()->Move(world);
		if (hit)
		{
			projectiles.erase(i);
			if (hit > 9 && hit < 100)
			{
				DealDamage(hit, i->get()->GetDamage());
			}
		}
	}
	if (side_attack && character->side_amount > 0)
		side_attack++;
	else
		side_attack = 0;
	if (character->char_class == 0)
	{
		if (side_attack == 25||side_attack == 35)
		{
			if (character->lvl > 2 && rand() % 4 == 0)
				if (side_attack == 25&&archer.stacks>0)
					side_attack = 26;
			
			int damage;
			if (archer.stacks > 0)
			{
				archer.stacks--;
				float dmg = (float)archer.side_damage * 1.5;
				damage = dmg;
			}
			else
			{
				damage = archer.side_damage;
			}
			shared_ptr<Projectiles> p(new Projectiles(character_offset[0], character_offset[1], char_pos[0], char_pos[1] + 3, "Resource/textures/Arrow_Left.png", "Resource/textures/Arrow_Right.png", renderer, right,damage));
			projectiles.push_back(move(p));
			if (side_attack == 25)
			{
				side_attack = 0;
				character->side_amount--;
			}
			if (side_attack == 35)
				side_attack = 0;
		}
	}
	if (character->char_class == 1)
	{
		if(side_attack&&blocking)
			character->damage_reduction = character->side_damage+warrior_dmg_reduction;
		else
			character->damage_reduction = warrior_dmg_reduction;
		if(side_attack)
			if (character->lvl > 2)
			{
				if(not blocking)
				{
					character->side_amount--;
					side_attack = 0;
				}
			}
			else
			{
				if (side_attack >= 60 || not blocking)
				{
					character->side_amount--;
					side_attack = 0;
				}
			}
	}
	if (character->char_class == 2)
	{
		if (side_attack >= 25)
		{
			character->mana = min(character->mana + character->side_damage, character->max_mana);
			if(character->lvl>=1)
				character->health = min(character->health + character->side_damage, character->max_health);
			character->side_amount--;
			side_attack = 0;
		}
	}
	if (character->char_class == 3)
	{
		if (side_attack >= 10)
		{
			shared_ptr<Projectiles> p(new Projectiles(character_offset[0], character_offset[1], char_pos[0], char_pos[1] + 1, "Resource/textures/Thrown_Dagger_Left.png", "Resource/textures/Thrown_Dagger_Right.png", renderer, right,assasin.side_damage));
			projectiles.push_back(move(p));
			if(assasin.stacks==0)
				character->side_amount--;
			side_attack = 0;
		}
	}
}

void GameLogic::Skill(float character_offset[2], int& skill, int char_pos[2], int right,bool &invisible)
{
	if (skill && character->mana >= 20)
		skill++;
	else
		skill = 0;
	if (character->char_class == 0)
	{
		if (skill >= 5)
		{
			if (character->side_amount < character->max_side_amount)
			{
				if (character->lvl >= 2)
					archer.stacks += 2;
				character->side_amount = min(character->side_amount + 2, character->max_side_amount);
				character->mana -= 20;
			}
			skill = 0;
		}
	}
	if (character->char_class == 1)
	{
		if (skill == 2)
		{
			warrior.bonus_damage = warrior.damage / 2;
			if(character->lvl>=2)
				warrior_dmg_reduction = warrior.side_damage/2;
		}
		if (skill >= 300)
		{
			skill = 0;
			character->mana -= 20;
			warrior.bonus_damage = 0;
			warrior_dmg_reduction=0;
		}
	}
	if (character->char_class == 2)
	{
		int damage=mage.side_damage;
		if (skill >= 25)
		{
			if (character->lvl > 2 && rand() % 20 == 0)
			{
				if(skill==25)
					mage.stacks = 7;
			}
			if (mage.stacks > 0 || skill != 25)
				damage = damage / 2;
			shared_ptr<Projectiles> p(new Projectiles(character_offset[0], character_offset[1], char_pos[0], char_pos[1] + 1+rand()%4, "Resource/textures/Fireball_Left.png", "Resource/textures/Fireball_Right.png", renderer, right,damage));
			projectiles.push_back(move(p));
			if (mage.stacks == 0)
			{
				skill = 0;
				character->mana -= 20;
			}
			else
				mage.stacks--;
		}
	}
	if (character->char_class == 3)
	{
		if (skill)
		{
			invisible = 1;
			assasin.damage_reduction = 100000;
			if(character->lvl>=2)
				assasin.bonus_damage = assasin.damage;
			if (character->lvl > 2)
				assasin.stacks = 1;
		}
		if (skill >= 60)
		{
			character->mana -= 20;
			invisible = 0;
			assasin.damage_reduction = 0;
			assasin.bonus_damage = 0;
			assasin.stacks = 0;
			skill = 0;
		}
	}
}

void GameLogic::DealDamage(int ID, int ranged)
{
	if (ID == 99)
	{
		if (ranged)
			boss.get()->health -= ranged;
		else
			boss.get()->health -= character->damage + character->bonus_damage;
	}
	else
	{
		auto i = enemies.begin();
		for (i;i != enemies.end(); i++)
		{
			if (i->get()->Get_ID() == ID)
				break;
		}
		if (i != enemies.end())
		{
			if (ranged)
				i->get()->health -= ranged;
			else
				i->get()->health -= character->damage + character->bonus_damage;
			if (i->get()->health <= 0)
			{
				for (int rows = i->get()->Get_x() - 3;rows < i->get()->Get_x() + 3;rows++)
				{
					for (int columns = i->get()->Get_y() - 1;columns < i->get()->Get_y() + 8;columns++)
					{
						if (world[rows][columns] == i->get()->Get_ID())
							world[rows][columns] = 0;
					}
				}
				character->exp += (i->get()->exp) * (i->get()->lvl) / character->lvl;
				character->LvlUp();
				archer.gold += i->get()->gold;
				warrior.gold += i->get()->gold;
				mage.gold += i->get()->gold;
				assasin.gold += i->get()->gold;
				enemies.erase(i);
			}
		}
	}
}

void GameLogic::TakeDamage(int dmg_took)
{
	if (dmg_took)
	{
		character->health -= max(0,dmg_took * difficulty - character->damage_reduction);
	}
}

void GameLogic::CheckPickups(int char_pos[2])
{
	for (int i = -4;i < 5;i++)
	{
		int tileID = world[char_pos[0] + i][char_pos[1]];
		if (tileID > 100 && tileID < 200)
			Pickup(tileID);
		tileID = world[char_pos[0] + i][char_pos[1]-1];
		if (tileID > 100 && tileID < 200)
			Pickup(tileID);
	}
}

void GameLogic::Pickup(int ID)
{
	auto i = drops.begin();
	for (i;i->get()->Get_ID() != ID; i++) {}
	switch (i->get()->GetType())
	{
	case 0:
		character->health =min(character->health+i->get()->GetAmountOrID(),character->max_health);
		break;
	case 1:
		character->mana = min(character->mana + i->get()->GetAmountOrID(), character->max_mana);
		break;
	case 2:
		if (character->char_class == 3)
		{
			character->side_amount = min(character->side_amount + 3*i->get()->GetAmountOrID(), character->max_side_amount);
		}
		else
			character->side_amount = min(character->side_amount + i->get()->GetAmountOrID(), character->max_side_amount);
		break;
	case 3:
		archer.gold += i->get()->GetAmountOrID();
		warrior.gold += i->get()->GetAmountOrID();
		mage.gold += i->get()->GetAmountOrID();
		assasin.gold += i->get()->GetAmountOrID();
		break;
	case 4:
		equipement.AddItem(minimenu.GetItem(i->get()->GetAmountOrID()));
	}
	for (int j = -1;j < 2;j++)
		for (int k = -1;k < 2;k++)
			if(world[(int)i->get()->Get_x() + j][(int)i->get()->Get_y() + k]==ID)
				world[(int)i->get()->Get_x() + j][(int)i->get()->Get_y() + k] = 0;
	drops.erase(i);
}

void GameLogic::InitializeEnemy(float character_offset[2], double pos_x,double pos_y, string pathl,string pathr, int ID, int hp, int dmg,int exp,int gold,int lvl, int move_pattern, int attack_pattern)
{
	shared_ptr<Enemies> p(new Enemies(character_offset[0], character_offset[1], pos_x, pos_y, pathl,pathr, ID, renderer, hp, dmg, exp,gold,lvl, move_pattern, attack_pattern));
	enemies.push_back(move(p));
}

void GameLogic::InitializeEnemies(float character_offset[2])
{
	if(lvl_nr <= 2)
		InitializeEnemy(character_offset, 30,4, "Resource/textures/Training_Dummy.png","Resource/textures/Training_Dummy.png", 10,250, 0, 0,10,1, 0, 0);
	if (lvl_nr == 3)
	{
		InitializeEnemy(character_offset, 172, 28, "Resource/textures/Zombie_left.png", "Resource/textures/Zombie_right.png", 11, 200, 10, 50, 10, 1, 1, 1);
		InitializeEnemy(character_offset, 152, 28, "Resource/textures/Zombie_left.png", "Resource/textures/Zombie_right.png", 12, 200, 10, 50, 10, 1, 1, 1);
	}
	if (lvl_nr == 5)
	{
		InitializeEnemy(character_offset, 172, 5, "Resource/textures/Zombie_left.png", "Resource/textures/Zombie_right.png", 11, 200, 10, 50, 10, 1, 1, 1);
		InitializeEnemy(character_offset, 350, 5, "Resource/textures/Zombie_left.png", "Resource/textures/Zombie_right.png", 12, 200, 10, 50, 10, 1, 1, 1);
		InitializeEnemy(character_offset, 550, 70, "Resource/textures/Zombie_left.png", "Resource/textures/Zombie_right.png", 13, 200, 10, 50, 10, 1, 1, 1);
		InitializeEnemy(character_offset, 600, 75, "Resource/textures/Spirit_left.png", "Resource/textures/Spirit_right.png", 14, 100, 20, 50, 10, 1, 2, 1);
		InitializeEnemy(character_offset, 300, 28, "Resource/textures/Spirit_left.png", "Resource/textures/Spirit_right.png", 15, 100, 20, 50, 10, 1, 2, 1);
		InitializeEnemy(character_offset, 400, 130, "Resource/textures/Spirit_left.png", "Resource/textures/Spirit_right.png", 16, 100, 20, 50, 10, 1, 2, 1);
	}
	if (lvl_nr == 6&&summonID==0)
	{
		shared_ptr<Boss> p(new Boss(character_offset[0], character_offset[1], 300, 5, "Resource/textures/DarkMage.png", "Resource/textures/DarkMage.png",99, renderer,2500,0,250,100,2,0,0,1));
		for (int i = -3;i < 4;i++)
			for (int j = -1;j < 7;j++)
				world[300 + i][5 + j] = 99;
		boss = move(p);
		summonID = 10;
	}
	if (lvl_nr == 6 && summonID > 0)
	{
		summonID++;
		InitializeEnemy(character_offset, 100, 5, "Resource/textures/Spirit_left.png", "Resource/textures/Spirit_right.png", summonID, 100, 20, 50, 10, 1, 2, 1);
		summonID++;
		InitializeEnemy(character_offset, 400, 5, "Resource/textures/Spirit_left.png", "Resource/textures/Spirit_right.png", summonID, 100, 20, 50, 10, 1, 2, 1);
		if (summonID > 95)
			summonID = 10;
	}
}

void GameLogic::InitializeDrop(float character_offset[2], double pos_x, double pos_y, string path, int ID, int type, int amount)
{
	shared_ptr<Drops> p(new Drops(character_offset[0], character_offset[1], pos_x, pos_y, path, ID, renderer, type, amount));
	drops.push_back(move(p));
	for(int i=-1;i<2;i++)
		for (int j = -1;j < 2;j++)
			if(world[(int)pos_x + i][(int)pos_y + j]==0)
				world[(int)pos_x+i][(int)pos_y+j] = ID;
}

void GameLogic::InitializeDrops(float character_offset[2])
{
	if (lvl_nr == 1)
	{
		InitializeDrop(character_offset, 130, 4, "Resource/textures/Arrow.png", 102, 2, 5);
		InitializeDrop(character_offset, 140, 4, "Resource/textures/Arrow.png", 103, 2, 5);
		InitializeDrop(character_offset, 150, 4, "Resource/textures/Arrow.png", 104, 2, 5);
		InitializeDrop(character_offset, 160, 4, "Resource/textures/Arrow.png", 105, 2, 5);
	}if (lvl_nr == 2)
	{
		InitializeDrop(character_offset, 130, 4, "Resource/textures/Wooden_Dagger.png", 106, 4, 0);
		InitializeDrop(character_offset, 140, 4, "Resource/textures/Wooden_Sword.png", 107, 4, 1);
		InitializeDrop(character_offset, 150, 4, "Resource/textures/Wooden_Staff.png", 108, 4, 2);
		InitializeDrop(character_offset, 160, 4, "Resource/textures/Wooden_Knife.png", 109, 4, 3);
	}
}

void GameLogic::InitializeNPC(float character_offset[2], double pos_x, double pos_y, string path, int ID,int interactionID,int options[3])
{
	shared_ptr<NPC> p(new NPC(character_offset[0], character_offset[1], pos_x, pos_y, path, ID, renderer,interactionID,options));
	npcs.push_back(move(p));
	for (int i = -3;i < 4;i++)
		for (int j = -1;j < 9;j++)
			world[(int)pos_x + i][(int)pos_y + j] = ID;
}

void GameLogic::InitializeNPCs(float character_offset[2])
{
	int options[3];
	if (lvl_nr == 0)
	{
		options[0] = 1;
		options[1] = 0;
		options[2] = 0;
		InitializeNPC(character_offset, 190, 4, "Resource/textures/Nothing.png", 202, 1, options);
	}
	if (lvl_nr == 1)
	{
		options[0] = 2;
		options[1] = 0;
		options[2] = 0;
		InitializeNPC(character_offset, 190, 4, "Resource/textures/Nothing.png", 202, 1, options);
	}
	if (lvl_nr == 2)
	{
		options[0] = 3;
		options[1] = 0;
		options[2] = 0;
		InitializeNPC(character_offset, 190, 4, "Resource/textures/Nothing.png", 202, 1, options);
	}
	if (lvl_nr == 3)
	{
		options[0] = 4;
		options[1] = 0;
		options[2] = 0;
		InitializeNPC(character_offset, 190, 4, "Resource/textures/Nothing.png", 202, 1, options);
	}
	if(lvl_nr == 4)
	{
		options[0] = 5;
		options[1] = 1;
		options[2] = 5;
		InitializeNPC(character_offset, 160, 4, "Resource/textures/Tavern_keeper.png", 201, 1, options);
		options[0] = 6;
		options[1] = 0;
		options[2] = 0;
		InitializeNPC(character_offset, 190, 4, "Resource/textures/Nothing.png", 202, 1, options);
	}
	if (lvl_nr == 5)
	{
		options[0] = 11;
		options[1] = 0;
		options[2] = 0;
		InitializeNPC(character_offset, 955, 4, "Resource/textures/Nothing.png", 202, 1, options);
		options[0] = 7;
		InitializeNPC(character_offset, 800, 5, "Resource/textures/Spring_altar_left.png", 203, 1, options);
		InitializeNPC(character_offset, 815, 5, "Resource/textures/Spring_altar_middle.png", 203, 1, options);
		InitializeNPC(character_offset, 830, 5, "Resource/textures/Spring_altar_right.png", 203, 1, options);
		options[0] = 8;
		InitializeNPC(character_offset, 200, 5, "Resource/textures/Summer_altar_left.png", 204, 1, options);
		InitializeNPC(character_offset, 215, 5, "Resource/textures/Summer_altar_middle.png", 204, 1, options);
		InitializeNPC(character_offset, 230, 5, "Resource/textures/Summer_altar_right.png", 204, 1, options);
		options[0] = 9;
		InitializeNPC(character_offset, 550, 60, "Resource/textures/Autumn_altar_left.png", 205, 1, options);
		InitializeNPC(character_offset, 565, 60, "Resource/textures/Autumn_altar_middle.png", 205, 1, options);
		InitializeNPC(character_offset, 580, 60, "Resource/textures/Autumn_altar_right.png", 205, 1, options);
		options[0] = 10;
		InitializeNPC(character_offset, 500, 120, "Resource/textures/Winter_altar_left.png", 206, 1, options);
		InitializeNPC(character_offset, 515, 120, "Resource/textures/Winter_altar_middle.png", 206, 1, options);
		InitializeNPC(character_offset, 530, 120, "Resource/textures/Winter_altar_right.png", 206, 1, options);
	}
}

void GameLogic::UpdateStats()
{
	if (equipement.weapon[0]->Get_type() != 3)
	{
		archer.damage = equipement.weapon[0].get()->Get_first_stat();
		archer.attack_speed = equipement.weapon[0].get()->Get_seccond_stat();
	}
	if (equipement.sidearm[0]->Get_type() != 3)
	{
		archer.side_damage = equipement.sidearm[0].get()->Get_first_stat();
		archer.max_side_amount = equipement.sidearm[0].get()->Get_seccond_stat();
	}
	if (equipement.armour[0]->Get_type() != 3)
	{
		archer.max_health = equipement.armour[0].get()->Get_first_stat();
		archer.max_mana = equipement.armour[0].get()->Get_seccond_stat();
	}
	if (equipement.weapon[1]->Get_type() != 3)
	{
		warrior.damage = equipement.weapon[1].get()->Get_first_stat();
		warrior.attack_speed = equipement.weapon[1].get()->Get_seccond_stat();
	}
	if (equipement.sidearm[1]->Get_type() != 3)
	{
		warrior.side_damage = equipement.sidearm[1].get()->Get_first_stat();
		warrior.max_side_amount = equipement.sidearm[1].get()->Get_seccond_stat();
	}
	if (equipement.armour[1]->Get_type() != 3)
	{
		warrior.max_health = equipement.armour[1].get()->Get_first_stat();
		warrior.max_mana = equipement.armour[1].get()->Get_seccond_stat();
	}
	if (equipement.weapon[2]->Get_type() != 3)
	{
		mage.damage = equipement.weapon[2].get()->Get_first_stat();
		mage.attack_speed = equipement.weapon[2].get()->Get_seccond_stat();
	}
	if (equipement.sidearm[2]->Get_type() != 3)
	{
		mage.side_damage = equipement.sidearm[2].get()->Get_first_stat();
		mage.max_side_amount = equipement.sidearm[2].get()->Get_seccond_stat();
	}
	if (equipement.armour[2]->Get_type() != 3)
	{
		mage.max_health = equipement.armour[2].get()->Get_first_stat();
		mage.max_mana = equipement.armour[2].get()->Get_seccond_stat();
	}
	if (equipement.weapon[3]->Get_type() != 3)
	{
		assasin.damage = equipement.weapon[3].get()->Get_first_stat();
		assasin.attack_speed = equipement.weapon[3].get()->Get_seccond_stat();
	}
	if (equipement.sidearm[3]->Get_type() != 3)
	{
		assasin.side_damage = equipement.sidearm[3].get()->Get_first_stat();
		assasin.max_side_amount = equipement.sidearm[3].get()->Get_seccond_stat();
	}
	if (equipement.armour[3]->Get_type() != 3)
	{
		assasin.max_health = equipement.armour[3].get()->Get_first_stat();
		assasin.max_mana = equipement.armour[3].get()->Get_seccond_stat();
	}
}

void GameLogic::Swap(int change)
{
	if (not swap_cd)
	{
		if (change)
			swap = 1;
		else if (swap == 1)
			swap = 2;
	}
	else
		swap_cd--;
	if (character->health <= 0)
		swap = 2;
	if (swap == 2)
	{
		switch (actual_class)
		{
		case 0:
			character = &warrior;
			actual_class = 1;
			range_x = 10;
			range_y = 10;
			break;
		case 1:
			character = &mage;
			actual_class = 2;
			range_x = 8;
			range_y = 8;
			break;
		case 2:
			character = &assasin;
			actual_class = 3;
			range_x = 9;
			range_y = 7;
			break;
		case 3:
			character = &archer;
			actual_class = 0;
			range_x = 7;
			range_y = 7;
			break;
		}
		swap_cd = 100;
		swap = 0;
	}
}

void GameLogic::Regen()
{
	if (second == 60)
	{
		if (archer.health > 0)
			archer.health = min(archer.max_health, archer.health + 4);
		if (warrior.health > 0)
			warrior.health = min(warrior.max_health, warrior.health + 10);
		if (mage.health > 0)
			mage.health = min(mage.max_health, mage.health + 2);
		if (assasin.health > 0)
			assasin.health = min(assasin.max_health, assasin.health + 5);

			archer.mana = min(archer.max_mana, archer.mana + 1);
			warrior.mana = min(warrior.max_mana, warrior.mana + 1);
			mage.mana = min(mage.max_mana, mage.mana + 5);
			assasin.mana = min(assasin.max_mana, assasin.mana + 1);

		if (archer.health <= 0)
		{
			resurection[0]++;
			if (resurection[0] == 180)
				archer.health = archer.max_health;
		}
		if (warrior.health <= 0)
		{
			resurection[1]++;
			if (resurection[1] == 180)
				warrior.health = warrior.max_health;
		}
		if (mage.health <= 0)
		{
			resurection[2]++;
			if (resurection[2] == 180)
				mage.health = mage.max_health;
		}
		if (assasin.health <= 0)
		{
			resurection[3]++;
			if (resurection[3] == 180)
				assasin.health = assasin.max_health;
		}

		second = 0;
	}
	else
		second++;
	if (archer.health <= 0 && warrior.health <= 0)
		if (mage.health <= 0 && assasin.health <= 0)
		{
			archer.health = archer.max_health;
			warrior.health = warrior.max_health;
			mage.health = mage.max_health;
			assasin.health = assasin.max_health;
			Restart();
		}
}

void GameLogic::Restart()
{
	state = 7;
}
