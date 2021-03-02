#pragma once

#include "Present.h"
#include "Multimedia_Files.h"

//------derived from present------
class Speed_Present:public Present
{
public:
	//------------------C-tor-------------------
	Speed_Present(sf::Vector2f position, char c);

	//-----------draw function-----------
	void draw(sf::RenderWindow& window);

	//-----C-tor----
	~Speed_Present();
};

