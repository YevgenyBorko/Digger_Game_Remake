#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Game_Object
{
public:
	//---------------C-tors----------------
	Game_Object(sf::Vector2f position, char c);
	Game_Object();

	//------------pure virtual function------------
	virtual void draw(sf::RenderWindow& window) = 0;

	//-----------all around functions---------------
	virtual void set_position(sf::Vector2f new_position);
	sf::Vector2f get_position() const;
	const sf::Sprite& get_pic() const;
	char get_type() const;

	//----C-tor----
	~Game_Object();

protected:
	//---protected Variables---
	sf::Sprite m_object_pic;
	sf::Vector2f m_position;

	char m_type;
};