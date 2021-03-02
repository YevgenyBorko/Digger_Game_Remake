#include "Wall.h"

Wall::Wall(sf::Vector2f position, char c)
	: Obstacle(position,c)
{}

//------function that draws the image-------
void Wall::draw(sf::RenderWindow & window)
{
	//----------------------------uses singletone to load picture----------------------------
	m_object_pic.setTexture(Multimedia_Files::instance().Get_Texture(Multimedia_Files::wall));

	m_object_pic.setPosition(m_position);
	window.draw(m_object_pic);				//draws sprite
}

Wall::~Wall()
{}
