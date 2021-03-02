#include "Time_Present.h"

Time_Present::Time_Present(sf::Vector2f position, char c)
	: Present(position, c)
{}

//---------function that draws the image---------
void Time_Present::draw(sf::RenderWindow& window)
{
	//----------------------------uses singletone to load picture----------------------------
	m_object_pic.setTexture(Multimedia_Files::instance().Get_Texture(Multimedia_Files::time_present));

	m_object_pic.setPosition(m_position);
	window.draw(m_object_pic);				//draws sprite
}

Time_Present::~Time_Present()
{}
