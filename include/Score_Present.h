#pragma once

#include "Present.h"
#include "Multimedia_Files.h"

//------derived from present------
class Score_Present:public Present
{
public:
	//------------------C-tor-------------------
	Score_Present(sf::Vector2f position, char c);

	//-----------draw function-----------
	void draw(sf::RenderWindow& window);

	//-----C-tor----
	~Score_Present();
};

