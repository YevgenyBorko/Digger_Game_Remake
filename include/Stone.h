#pragma once

#include "Obstacle.h"
#include "Multimedia_Files.h"

//--derived from obstacle--
class Stone:public Obstacle
{
public:
	//---------------C-tor----------------
	Stone(sf::Vector2f position, char c);

	//-----------draw function-----------
	void draw(sf::RenderWindow& window);

	//C-tor
	~Stone();
};

