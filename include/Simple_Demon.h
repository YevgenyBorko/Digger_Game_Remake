#pragma once

#include "Demon.h"
#include "Multimedia_Files.h"

//-----derived from demon------
class Simple_Demon:public Demon
{
public:
	//-----------------------C-tor------------------------
	Simple_Demon(sf::Vector2f position, char c, bool smart);

	//--------all around functions--------
	void draw(sf::RenderWindow & window);
	void move(int direction);

	//-----C-tor----
	~Simple_Demon();
};

