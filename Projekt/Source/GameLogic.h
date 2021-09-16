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
	 * \brief Funkcja rysuj�ca ca�o�� gry
	 * \param character_offset przemieszczenie postaci
	 * \return stan specjalny (0 - nic / 1 - wyjd� / 2 - id� do nast�pnego poziomu / 3 - restartuj poziom)
	 */
	int RenderFrame(float character_offset[2]);
	template <class T>
	/**
	 * .
	 * \brief Funkcja rysuj�ca list� obiekt�w
	 * \param list lista obiekt�w do narysowania
	 */
	void Draw(list<shared_ptr<T>>);
	/**
	 * .
	 * \brief Funkcja wywo�uj�ca efekt specjalny ekwipunku
	 * \param mode zmienna okre�laj�ca czy efekt ma zpsta� w��czony czy wy��czony
	 * \param char_pos po�o�enie gracza
	 */
	void TriggerEQ(bool mode,int char_pos[2]);
	/**
	 * .
	 * \brief Funkcja obs�uguj�ca poruszanie si� gracza
	 * \param move_right czy gracz chce i�� w prawo
	 * \param move_left czy gracz chce i�� w lewo
	 * \param turn_right czy gracz jest obr�cony w prawo
	 * \param jump czy gracz chce skoczy�
	 * \param character_offset przemieszczenie postaci
	 * \param char_pos pozycja postaci
	 */
	void Movement(bool& move_right, bool& move_left, int& turn_right, int& jump, float character_offset[2], int char_pos[2]);
	/**
	 * .
	 * \ Funkcja obs�uguj�ca poruszanie si� przeciwnik�w
	 * \param char_pos pozycja gracza
	 */
	void Enemy_Movement(int char_pos[2]);
	/**
	 * .
	 * /brief Funckja ustawiaj�ca kolizj� przeciwnik�w
	 */
	void SetEnemies();
	/**
	 * .
	 * /brief Funkcja usuwaj�ca kolizj� przeciwnik�w
	 */
	void ResetEnemies();
	/**
	 * .
	 * \brief Funkcja obs�uguj�ca ataki podstawowe
	 * \param attack zmienna okre�laj�ca aktualny stan ataku
	 * \param char_pos pozycja gracza
	 * \param right czy gracz jest odwr�cony w prawo
	 */
	void Meele(int attack,int char_pos[2],int right);
	/**
	 * .
	 * \brief Funkcja aktuwuj�ca o�tarze po rozwi�zaniu zagadi
	 * \param character_offset przemieszczenie postaci
	 */
	void ActivateAltars(float character_offset[2]); 
	/**
	 * .
	 * \brief Funkcja aktywuj�ca umiej�tno�ci bossa
	 * \param character_offset przemieszczenie postaci
	 */
	void TriggerBoss(float character_offset[2]);
	/**
	 * .
	 * \brief Funkcja sprawdzaj�ca interakcje z NPC
	 * \param attack aktualny stan ataku
	 * \param char_pos pozycja postaci
	 * \param right czy posta� obr�cona jest w prawo
	 */
	void Interact(int attack, int char_pos[2], int right);
	/**
	 * .
	 * \Funkcja pozystkuj�ca informacj� o interakcji
	 * \param ID ID postaci z kt�r� nast�pi�a interakcja
	 */
	void GetInteract(int ID);
	/**
	 * .
	 * \brief Funckja obs�uguj�ca u�ycie broni pobocznej
	 * \param character_offset przemieszczenie postaci
	 * \param side_attack aktualny stan ataku pobocznego
	 * \param char_pos pozycja postaci
	 * \param right czy posta� jest obr�cona w prawo
	 * \param blocking czy posta� blokuje
	 */
	void SideAttack(float character_offset[2], int & side_attack, int char_pos[2], int right,bool blocking);
	/**
	 * .
	 * \brief Funkcja obs�uguj�ca u�ycie umiej�tno�ci
	 * \param character_offset przemieszczenie postaci
	 * \param skill aktualny stan zakl�cia
	 * \param char_pos pozycja postaci
	 * \param right czy postac ob�rcona jest w prawo
	 * \param invisible czy posta� jest niewidzialna
	 */
	void Skill(float character_offset[2], int& skill, int char_pos[2], int right,bool & invisible);
	/**
	 * .
	 * \brief Funkcja zadaj�ca obra�enia przeciwnikom
	 * \param ID ID przeciwnika
	 * \param ranged czy by� to atak dystansowy
	 */
	void DealDamage(int ID,int ranged);
	/**
	 * .
	 * \brief Funkcja zadaj�ca obra�enia aktualnej postaci
	 * \param dmg_took ilo�� otrzymanych obra�e�
	 */
	void TakeDamage(int dmg_took);
	/**
	 * .
	 * \Funkcja sprawdzaj�ca czy gracz mo�e podnie�� jaki� przedmiot
	 * \param char_pos pozycja postaci
	 */
	void CheckPickups(int char_pos[2]);
	/**
	 * .
	 * \Funkcja inicjuj�ca podniesienie przedmiotu
	 * \param ID ID podniesionego przedmiotu
	 */
	void Pickup(int ID);
	/**
	 * .
	 * \brief Funkcja inicjalizuj�ca przeciwnika
	 * \param character_offset przemieszczenie postaci
	 * \param pos_x pozycja x przeciwnika
	 * \param pos_y pozycja y przeciwnika
	 * \param pathl scie�ka do tekstury przeciwnika ob�rconego w lewo
	 * \param pathr scie�ka do tekstury przeciwnika ob�rconego w prawo
	 * \param ID ID przeciwnika
	 * \param hp zdrowie przeciwnika
	 * \param dmg obra�enia przeciwnika
	 * \param exp do�wiadczenie otrzymane za zabicie przeciwnika
	 * \param gold z�oto otrzymane za zabicie przeciwnika
	 * \param lvl poziom przeciwnika
	 * \param move_pattern ID schematu poruszania si� przeciwnika
	 * \param attack_pattern ID schematu ataku przeciwnika
	 */
	void InitializeEnemy(float character_offset[2],double pos_x,double pos_y,string pathl,string pathr,int ID,int hp,int dmg,int exp,int gold,int lvl,int move_pattern,int attack_pattern);
	/**
	 * .
	 * \brief Funkcja inicjalizuj�ca przeciwnik�w
	 * \param character_offset przemieszczenie postaci
	 */
	void InitializeEnemies(float character_offset[2]);
	/**
	 * .
	 * \brief Funkcja inicjalizuj�ca przedmiot do podniesienia
	 * \param character_offset przemieszczenie postaci
	 * \param pos_x pozycja x przedmiotu
	 * \param pos_y pozycja y przedmiotu
	 * \param pathl �cie�ka do tekstury przdmiotu
	 * \param ID ID przedmiotu
	 * \param type typ przedmiotu
	 * \param amount ilo�� lub ID w wypadku przedmiotu ekwipunku
	 */
	void InitializeDrop(float character_offset[2], double pos_x, double pos_y, string pathl, int ID, int type, int amount);
	/**
	 * .
	 * \Funkcja inicjalizuj�ca przedmioty do podniesienia
	 * \param character_offset przemieszczenie przedmiotu
	 */
	void InitializeDrops(float character_offset[2]);
	/**
	 * .
	 * \brief Funkcja inicjalizuj�ca NPC
	 * \param character_offset przemieszczenie postaci
	 * \param pos_x pozycja x NPC
	 * \param pos_y pozycja y NPC
	 * \param pathl �cie�ka do tekstury NPC
	 * \param ID ID NPC
	 * \param interactionID ID interakcji NPC
	 * \param options opcje interakcji NPC
	 */
	void InitializeNPC(float character_offset[2], double pos_x, double pos_y, string pathl, int ID,int interactionID,int options[3]);
	/**
	 * .
	 * \brief Funkcja inicjalizuj�ca NPC
	 * \param character_offset przemieszczenie postaci
	 */
	void InitializeNPCs(float character_offset[2]);
	/**
	 * .
	 * /brief Funkcja uaktualniaj�ca statystyki po zmianie przedmiotu
	 */
	void UpdateStats();
	/**
	 * .
	 * \brief Funkcja odpowiedzialna za zmian� postaci
	 * \param change sygna� inicjalizuj�cy zmian�
	 */
	void Swap(int change);
	/**
	 * .
	 * \brief Funkcja odpowiedzialna za regeneracje postaci
	 */
	void Regen();
	/**
	 * .
	 * /brief Funkcja restartuj�ca aktualny poziom
	 */
	void Restart();
};
