#pragma once

#include "Game_Object.h"

//---derived from game object---
class Obstacle:public Game_Object
{
public:
	//----------------C-tor--------------
	Obstacle(sf::Vector2f position, char c);

	//--C-tor--
	~Obstacle();
};

