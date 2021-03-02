#pragma once

#include "Menu.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream> 
#include <SFML/System.hpp>
#include <cassert>
#include <fstream>
#include <math.h>
#include <string>
#include <random>
#include <time.h>
#include <sstream>
#include "Multimedia_Files.h"
#include "Game_Status.h"

class Controller
{
public:
	//C-tor
	Controller();

	//-all around functions-
	void start_game();
	void load_level();

	//C-tor
	~Controller();

private:
	//-------Member Variables-----
	Menu m_menu;
	Board m_board;
	Game_Status m_status;

	bool demon_restore = true,
		 m_new_level;

	float next_sec_digger = 0,
		  next_sec_demon = 0,
	   	  currentSec = 0;

	int m_elapsed_time = 0,
	    m_num_of_rows,
		m_num_of_cols,
		m_num_of_stones,
		m_current_level;

	sf::Time present_speed_timer;

	sf::Clock clock,
			  Level_clock,
			  present_clock;

	sf::RenderWindow m_window;

	sf::Sprite m_background;

	sf::Sound audio_start_game,
		 	  audio_digger_strike,
			  audio_soundtrack,
			  audio_game_over;

	std::ostringstream s_score,
					   s_lives,
					   s_stones,
					   s_time,
					   s_current_level;

	sf::Text game_score,
			 lives,
			 stones,
			 time,
			 current_level;
};

