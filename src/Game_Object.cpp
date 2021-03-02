#include "Game_Object.h"

Game_Object::Game_Object(sf::Vector2f position, char c)
	: m_position(position),m_type(c)
{}

Game_Object::Game_Object()
	: m_type( 0 )
{}

//---------gets the object picture----------
const sf::Sprite& Game_Object::get_pic() const
{
	return m_object_pic;
}

//-------get the object type------
char Game_Object::get_type() const
{
	return m_type;
}

//---------------set the object position--------------
void Game_Object::set_position(sf::Vector2f new_position)
{
	m_position = new_position;
}


//-----------get the object position----------
sf::Vector2f Game_Object::get_position() const
{
	return m_position;
}

Game_Object::~Game_Object()
{}
