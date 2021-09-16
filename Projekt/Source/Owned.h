#pragma once
#include <algorithm>
#include <list>
#include "Item.h"
class Owned
{
public:
	list<shared_ptr<Item>> weapons;
	list<shared_ptr<Item>> sidearms;
	list<shared_ptr<Item>> armours;
	Owned() {};
	/**
	 * .
	 * \brief funkcja dodaj¹ca nowy przedmiot do posiadanych
	 * \param it przedmiot do dodania
	 */
	void Add_item(Item it);
};