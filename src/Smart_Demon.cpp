#include "Smart_Demon.h"

Smart_Demon::Smart_Demon(sf::Vector2f position, char c, bool smart)
	: Demon(position,c,smart,4)
{}

//------------draws the smart demon---------------
void Smart_Demon::draw(sf::RenderWindow & window)
{
	//----------------------------uses singletone to load picture----------------------------
	m_object_pic.setTexture(Multimedia_Files::instance().Get_Texture(Multimedia_Files::smart_demon));

	window.draw(m_object_pic);			//draws sprite
}

//-------movement of the demon-------
void Smart_Demon::move(int direction)
{
	switch (direction)
	{
	case 0:
		m_position = { m_position.x  , m_position.y - 1 };    //up
		break;
	case 1:
		m_position = { m_position.x  , m_position.y + 1 };    //down
		break;
	case 2:
		m_position = { m_position.x - 1 , m_position.y };     //left
		break;
	case 3:
		m_position = { m_position.x + 1 , m_position.y };     //right
		break;
	}
	//---updates the image location----
	m_object_pic.setPosition(m_position);
}

Smart_Demon::~Smart_Demon()
{}
