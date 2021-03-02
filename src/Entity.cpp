#include "Entity.h"

Entity::Entity()
{}

Entity::Entity(sf::Vector2f position, char c)
	: Game_Object(position, c), m_first_position(position)
{}

//-------------gets first position-------------
sf::Vector2f Entity::get_first_position() const
{
	return m_first_position;
}

Entity::~Entity()
{}
