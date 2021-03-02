#include "Menu.h"

Menu::Menu()
{
	//--------------------------uses singletone to load pictures and audio----------------------------
	m_play_button.setTexture(Multimedia_Files::instance().Get_Texture(Multimedia_Files::play_button));
	m_exit_button.setTexture(Multimedia_Files::instance().Get_Texture(Multimedia_Files::exit_button));
	m_button_sound.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::button_sound));
	m_game_won.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::game_won));
}
//--------------------------------function to control all menus---------------------------------
bool Menu::main_game_loop(sf::RenderWindow & window, sf::Vector2f play_position, sf::Vector2f exit_position)
{
	bool play = false;

	window.create(sf::VideoMode::VideoMode(1000, 800), "Digger");

	while (window.isOpen())
	{
		window.clear();
		
		window.draw(m_menu);
		draw_play_button(window, play_position);
		draw_exit_button(window, exit_position);
		
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			switch (Event.type)
			{

			case sf::Event::MouseButtonPressed:
				if (Event.mouseButton.button == sf::Mouse::Left)	// if left mouse pressed
				{
					int x = Event.mouseButton.x,
						y = Event.mouseButton.y;
																	// if 'play' button was pressed
					if (x > (play_position.x + 21) && x < (play_position.x + 130) && y >(play_position.y + 24) &&
						y < (play_position.y + 130))
					{
						window.close();
						play = true;
					}
																	// if 'exit' was pressed
					if (x > (exit_position.x + 21) && x < (exit_position.x + 130) && y > (exit_position.y + 24) &&
						y < (exit_position.y + 130))
					{
						window.close();
						play = false;
					}
				}
				break;
			case sf::Event::MouseMoved:							// makes the sound button
				int x = sf::Mouse::getPosition(window).x,
					y = sf::Mouse::getPosition(window).y;

				if (x > (play_position.x + 21) && x < (play_position.x + 130) && y >(play_position.y + 24) &&
					y < (play_position.y + 130))
				{
					m_button_sound.play();
				}
				if (x > (exit_position.x + 21) && x < (exit_position.x + 130) && y >(exit_position.y + 24) &&
					y < (exit_position.y + 130))
				{
					m_button_sound.play();
				}
				break;
			}
		}
													//scales up the button
		int x = sf::Mouse::getPosition(window).x,
			y = sf::Mouse::getPosition(window).y;

		if (x > (play_position.x + 21) && x < (play_position.x + 130) && y >(play_position.y + 24) &&
			y < (play_position.y + 130))
		{
			m_play_button.setScale(1.36, 1.43);
			draw_play_button(window, { play_position.x - 30, play_position.y - 30});
		}
		m_play_button.setScale(1, 1);

		if (x > (exit_position.x + 21) && x < (exit_position.x + 130) && y >(exit_position.y + 24) &&
			y < (exit_position.y + 130))
		{
			m_exit_button.setScale(1.36, 1.43);
			draw_exit_button(window, { exit_position.x - 30, exit_position.y -30 });
		}
		m_exit_button.setScale(1, 1);
		window.display();

	}
	return play;
}

//-------------start game menu------------
bool Menu::start(sf::RenderWindow & window)
{
	bool play = false;
	m_menu.setTexture(Multimedia_Files::instance().Get_Texture(Multimedia_Files::start_menu));
	play = main_game_loop(window, { 770,230 }, { 770,420 });

	return play;
}

//-------------win game menu---------
bool Menu::win(sf::RenderWindow & window)
{ 
	bool play = false;
	m_menu.setTexture(Multimedia_Files::instance().Get_Texture(Multimedia_Files::game_win)); 
	m_game_won.play();
	m_game_won.setLoop(true);
	play = main_game_loop(window, { 150,600 }, { 770,600 });
	m_game_won.stop();
	return play;
}

//------------lose game menu------------
bool Menu::lose(sf::RenderWindow & window)
{
	bool play = false;
	m_menu.setTexture(Multimedia_Files::instance().Get_Texture(Multimedia_Files::game_over));
	play = main_game_loop(window, { 150,600 }, { 770,600 });

	return play;
}

//--------------------function to draw the play button---------------------
void Menu::draw_play_button(sf::RenderWindow & window, sf::Vector2f position)
{
	m_play_button.setPosition(position);
	window.draw(m_play_button);
}

//--------------------function to draw the exit button--------------------
void Menu::draw_exit_button(sf::RenderWindow & window, sf::Vector2f position)
{
	m_exit_button.setPosition(position);
	window.draw(m_exit_button);
}

Menu::~Menu()
{}

