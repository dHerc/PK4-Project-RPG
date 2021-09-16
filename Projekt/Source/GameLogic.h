#pragma once
#include "Graphic_engine/Graphic_engine.h"
#include "Character.h"
#include "Background.h"
#include "Menu.h"
#include "MiniMenu.h"
#include "Enemies.h"
#include "NPC.h"
#include "Drops.h"
#include "Projectiles.h"
#include "Equipement.h"
#include "Overlay.h"
#include "Story.h"
#include "Boss.h"
#include <stdlib.h>
#include <time.h>  
class GameLogic
{
private:
	int v = 0;
	int swap = 0;
	int swap_cd = 0;
	int summonID = 0;
	Character* character;
	Character& archer;
	Character& warrior;
	Character& mage;
	Character& assasin;
	int resurection[4];
	int second = 0;
	int range_x;
	int range_y;
	Background& background;
	Equipement& equipement;
	Story& story;
	Menu& menu;
	Minimenu& minimenu;
	Overlay& overlay;
	Renderer renderer;
	list<shared_ptr<Enemies>> enemies;
	list<shared_ptr<Drops>> drops;
	list<shared_ptr<Projectiles>> projectiles;
	list<shared_ptr<NPC>> npcs;
	shared_ptr<Boss> boss;
	int mini_menu_options[3];
	int actual_class=0; //0-archer,1-warriot,2-mage,3-assasin
	int & lvl_nr;
	int world[1920][216];
	int & state;
	int &difficulty;
	int warrior_dmg_reduction=0;
	bool& open_menu;
	bool& open_equipement;
public:
	
	GameLogic(Character& archer_char, Character& warrior_char, Character& mage_char, Character& assasin_char, Background& bg_class, Menu& menu, Minimenu& minimenu, Equipement& equipement, Story& story, Overlay& overlay, Renderer& renderer, int& lvl_nr, int& state, bool& open_menu, bool& open_equipement,int& difficulty);
	/**
	 * .
	 * \brief Funkcja rysuj¹ca ca³oœæ gry
	 * \param character_offset przemieszczenie postaci
	 * \return stan specjalny (0 - nic / 1 - wyjdŸ / 2 - idŸ do nastêpnego poziomu / 3 - restartuj poziom)
	 */
	int RenderFrame(float character_offset[2]);
	template <class T>
	/**
	 * .
	 * \brief Funkcja rysuj¹ca listê obiektów
	 * \param list lista obiektów do narysowania
	 */
	void Draw(list<shared_ptr<T>>);
	/**
	 * .
	 * \brief Funkcja wywo³uj¹ca efekt specjalny ekwipunku
	 * \param mode zmienna okreœlaj¹ca czy efekt ma zpstaæ w³¹czony czy wy³¹czony
	 * \param char_pos po³o¿enie gracza
	 */
	void TriggerEQ(bool mode,int char_pos[2]);
	/**
	 * .
	 * \brief Funkcja obs³uguj¹ca poruszanie siê gracza
	 * \param move_right czy gracz chce iœæ w prawo
	 * \param move_left czy gracz chce iœæ w lewo
	 * \param turn_right czy gracz jest obrócony w prawo
	 * \param jump czy gracz chce skoczyæ
	 * \param character_offset przemieszczenie postaci
	 * \param char_pos pozycja postaci
	 */
	void Movement(bool& move_right, bool& move_left, int& turn_right, int& jump, float character_offset[2], int char_pos[2]);
	/**
	 * .
	 * \ Funkcja obs³uguj¹ca poruszanie siê przeciwników
	 * \param char_pos pozycja gracza
	 */
	void Enemy_Movement(int char_pos[2]);
	/**
	 * .
	 * /brief Funckja ustawiaj¹ca kolizjê przeciwników
	 */
	void SetEnemies();
	/**
	 * .
	 * /brief Funkcja usuwaj¹ca kolizjê przeciwników
	 */
	void ResetEnemies();
	/**
	 * .
	 * \brief Funkcja obs³uguj¹ca ataki podstawowe
	 * \param attack zmienna okreœlaj¹ca aktualny stan ataku
	 * \param char_pos pozycja gracza
	 * \param right czy gracz jest odwrócony w prawo
	 */
	void Meele(int attack,int char_pos[2],int right);
	/**
	 * .
	 * \brief Funkcja aktuwuj¹ca o³tarze po rozwi¹zaniu zagadi
	 * \param character_offset przemieszczenie postaci
	 */
	void ActivateAltars(float character_offset[2]); 
	/**
	 * .
	 * \brief Funkcja aktywuj¹ca umiejêtnoœci bossa
	 * \param character_offset przemieszczenie postaci
	 */
	void TriggerBoss(float character_offset[2]);
	/**
	 * .
	 * \brief Funkcja sprawdzaj¹ca interakcje z NPC
	 * \param attack aktualny stan ataku
	 * \param char_pos pozycja postaci
	 * \param right czy postaæ obrócona jest w prawo
	 */
	void Interact(int attack, int char_pos[2], int right);
	/**
	 * .
	 * \Funkcja pozystkuj¹ca informacjê o interakcji
	 * \param ID ID postaci z któr¹ nast¹pi³a interakcja
	 */
	void GetInteract(int ID);
	/**
	 * .
	 * \brief Funckja obs³uguj¹ca u¿ycie broni pobocznej
	 * \param character_offset przemieszczenie postaci
	 * \param side_attack aktualny stan ataku pobocznego
	 * \param char_pos pozycja postaci
	 * \param right czy postaæ jest obrócona w prawo
	 * \param blocking czy postaæ blokuje
	 */
	void SideAttack(float character_offset[2], int & side_attack, int char_pos[2], int right,bool blocking);
	/**
	 * .
	 * \brief Funkcja obs³uguj¹ca u¿ycie umiejêtnoœci
	 * \param character_offset przemieszczenie postaci
	 * \param skill aktualny stan zaklêcia
	 * \param char_pos pozycja postaci
	 * \param right czy postac obórcona jest w prawo
	 * \param invisible czy postaæ jest niewidzialna
	 */
	void Skill(float character_offset[2], int& skill, int char_pos[2], int right,bool & invisible);
	/**
	 * .
	 * \brief Funkcja zadaj¹ca obra¿enia przeciwnikom
	 * \param ID ID przeciwnika
	 * \param ranged czy by³ to atak dystansowy
	 */
	void DealDamage(int ID,int ranged);
	/**
	 * .
	 * \brief Funkcja zadaj¹ca obra¿enia aktualnej postaci
	 * \param dmg_took iloœæ otrzymanych obra¿eñ
	 */
	void TakeDamage(int dmg_took);
	/**
	 * .
	 * \Funkcja sprawdzaj¹ca czy gracz mo¿e podnieœæ jakiœ przedmiot
	 * \param char_pos pozycja postaci
	 */
	void CheckPickups(int char_pos[2]);
	/**
	 * .
	 * \Funkcja inicjuj¹ca podniesienie przedmiotu
	 * \param ID ID podniesionego przedmiotu
	 */
	void Pickup(int ID);
	/**
	 * .
	 * \brief Funkcja inicjalizuj¹ca przeciwnika
	 * \param character_offset przemieszczenie postaci
	 * \param pos_x pozycja x przeciwnika
	 * \param pos_y pozycja y przeciwnika
	 * \param pathl scie¿ka do tekstury przeciwnika obórconego w lewo
	 * \param pathr scie¿ka do tekstury przeciwnika obórconego w prawo
	 * \param ID ID przeciwnika
	 * \param hp zdrowie przeciwnika
	 * \param dmg obra¿enia przeciwnika
	 * \param exp doœwiadczenie otrzymane za zabicie przeciwnika
	 * \param gold z³oto otrzymane za zabicie przeciwnika
	 * \param lvl poziom przeciwnika
	 * \param move_pattern ID schematu poruszania siê przeciwnika
	 * \param attack_pattern ID schematu ataku przeciwnika
	 */
	void InitializeEnemy(float character_offset[2],double pos_x,double pos_y,string pathl,string pathr,int ID,int hp,int dmg,int exp,int gold,int lvl,int move_pattern,int attack_pattern);
	/**
	 * .
	 * \brief Funkcja inicjalizuj¹ca przeciwników
	 * \param character_offset przemieszczenie postaci
	 */
	void InitializeEnemies(float character_offset[2]);
	/**
	 * .
	 * \brief Funkcja inicjalizuj¹ca przedmiot do podniesienia
	 * \param character_offset przemieszczenie postaci
	 * \param pos_x pozycja x przedmiotu
	 * \param pos_y pozycja y przedmiotu
	 * \param pathl œcie¿ka do tekstury przdmiotu
	 * \param ID ID przedmiotu
	 * \param type typ przedmiotu
	 * \param amount iloœæ lub ID w wypadku przedmiotu ekwipunku
	 */
	void InitializeDrop(float character_offset[2], double pos_x, double pos_y, string pathl, int ID, int type, int amount);
	/**
	 * .
	 * \Funkcja inicjalizuj¹ca przedmioty do podniesienia
	 * \param character_offset przemieszczenie przedmiotu
	 */
	void InitializeDrops(float character_offset[2]);
	/**
	 * .
	 * \brief Funkcja inicjalizuj¹ca NPC
	 * \param character_offset przemieszczenie postaci
	 * \param pos_x pozycja x NPC
	 * \param pos_y pozycja y NPC
	 * \param pathl œcie¿ka do tekstury NPC
	 * \param ID ID NPC
	 * \param interactionID ID interakcji NPC
	 * \param options opcje interakcji NPC
	 */
	void InitializeNPC(float character_offset[2], double pos_x, double pos_y, string pathl, int ID,int interactionID,int options[3]);
	/**
	 * .
	 * \brief Funkcja inicjalizuj¹ca NPC
	 * \param character_offset przemieszczenie postaci
	 */
	void InitializeNPCs(float character_offset[2]);
	/**
	 * .
	 * /brief Funkcja uaktualniaj¹ca statystyki po zmianie przedmiotu
	 */
	void UpdateStats();
	/**
	 * .
	 * \brief Funkcja odpowiedzialna za zmianê postaci
	 * \param change sygna³ inicjalizuj¹cy zmianê
	 */
	void Swap(int change);
	/**
	 * .
	 * \brief Funkcja odpowiedzialna za regeneracje postaci
	 */
	void Regen();
	/**
	 * .
	 * /brief Funkcja restartuj¹ca aktualny poziom
	 */
	void Restart();
};
