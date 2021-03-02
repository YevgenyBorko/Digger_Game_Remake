#include "Demon.h"

Demon::Demon(sf::Vector2f position, char c, bool smart, int direction)
	: Entity(position,c), m_is_smart(smart), m_demon_direction(direction), m_demon_prev_direction(4)
{}

//checks if demon is smart or simple 
bool Demon::get_is_smart() const
{
	return m_is_smart;
}
//----current demon direction------
int Demon::get_demon_direction() const
{
	return m_demon_direction;
}
//---------previus demon direction-------
int Demon::get_demon_prev_direction() const
{
	return m_demon_prev_direction;
}
//----------set currrent direction-------------
void Demon::set_demon_direction(int new_direction)
{
	m_demon_direction = new_direction;
}
//--------------set previus direction--------------
void Demon::set_demon_prev_direction(int new_direction)
{
	m_demon_prev_direction = new_direction;
}

Demon::~Demon()
{}
