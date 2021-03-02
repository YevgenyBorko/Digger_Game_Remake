#pragma once

#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>

class Multimedia_Files
{
public:
	static Multimedia_Files & instance();
	const sf::Font & GetFont() const;
	
	enum Picture_Type {
		digger,
		wall,
		diamond,
		stone,
		score_present,
		speed_present,
		stone_present,
		time_present,
		simple_demon,
		smart_demon,
		start_menu,
		game_over,
		game_win,
		play_button,
		exit_button,
		background
	};

	enum Audio_Type {
		game_over_menu,
		game_won,
		start_game,
		soundtrack,
		diamond_collision,
		digger_strike,
		button_sound,
		stone_boost,
		speed_boost,
		score_boost,
		time_boost,
		stone_collision
	};

	const sf::Texture &Get_Texture(Picture_Type enum_pic) const;
	const sf::SoundBuffer& Get_Audio(Audio_Type audio) const;

	//------C-tor-----
	~Multimedia_Files();

private:
	//----------Member Variables---------
	std::vector <sf::SoundBuffer> m_music;
	std::vector<sf::Texture> m_object_picture;
	sf::Font m_font;

	Multimedia_Files(const Multimedia_Files&) = delete;
	Multimedia_Files();
};

