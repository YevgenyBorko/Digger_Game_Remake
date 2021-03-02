#include "Score_Present.h"

Score_Present::Score_Present(sf::Vector2f position, char c)
	: Present(position, c)
{}

//---------function that draws the image---------
void Score_Present::draw(sf::RenderWindow& window)
{
	//----------------------------uses singletone to load picture----------------------------
	m_object_pic.setTexture(Multimedia_Files::instance().Get_Texture(Multimedia_Files::score_present));

	m_object_pic.setPosition(m_position);
	window.draw(m_object_pic);				//draws sprite
}

Score_Present::~Score_Present()
{}
