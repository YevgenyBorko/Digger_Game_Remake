#pragma once

#include "Game_Object.h"

//---derived from game object---
class Entity:public Game_Object
{
public:
	//---------------C-tors----------------
	Entity(sf::Vector2f position, char c);
	Entity();

	//---------get first position----------
	sf::Vector2f get_first_position() const;

	//-------pure virtual function-------
	virtual void move(int direction) = 0;

	//C-tor
	~Entity();

protected:
	//-----protected Variable-----
	sf::Vector2f m_first_position;
};

