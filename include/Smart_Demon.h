#pragma once

#include "Demon.h"
#include "Multimedia_Files.h"

//-----derived from demon------
class Smart_Demon:public Demon
{
public:
	//--------------------C-tor----------------------
	Smart_Demon(sf::Vector2f position, char c, bool smart);
	
	//--------all around functions--------
	void draw(sf::RenderWindow & window);
	void move(int direction);

	//----C-tor----
	~Smart_Demon();
};

