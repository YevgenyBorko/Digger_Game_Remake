#pragma once

#include <SFML/Graphics.hpp>
#include "Multimedia_Files.h"

class Menu
{
public:
	//-C-tor-
	Menu();

	//-------all around functions-------
	bool start(sf::RenderWindow& window);
	bool lose(sf::RenderWindow& window);
	bool win(sf::RenderWindow& window);

	//-C-tor-
	~Menu();

private:
	//------------------------------------Member functions------------------------------------
	bool main_game_loop(sf::RenderWindow& window, sf::Vector2f play_position, sf::Vector2f exit_position);
	void draw_play_button(sf::RenderWindow& window, sf::Vector2f position);
	void draw_exit_button(sf::RenderWindow& window, sf::Vector2f position);

	//-------Member Variables------
	sf::Sprite m_menu,
			   m_play_button,
			   m_exit_button;

	sf::Sound m_game_won,
		  	  m_button_sound;
};

