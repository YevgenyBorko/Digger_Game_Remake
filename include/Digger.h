#pragma once

#include "Entity.h"
#include "Multimedia_Files.h"

//--derived from entity---
class Digger:public Entity
{
public:
	//---------------C-tors----------------
	Digger(sf::Vector2f position, char c);
	Digger();

	//-----------all around functions---------------
	void move(int direction); 
	void draw(sf::RenderWindow & window);
	void set_position(sf::Vector2f new_position);
	void rotate(int rotation);
	void rotate_mirror();
	void rotate_to_first_position();

	//C-tor
	~Digger();
};

