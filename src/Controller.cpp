#include "Controller.h"

Controller::Controller()
	: m_current_level(1), m_status( 0, 3 ,100, 100 ),
	  m_num_of_rows(0) , m_num_of_cols(0), m_num_of_stones(0), m_new_level(false)
{}

 //load level in the board
void Controller::load_level()
{
	m_board.load_level(m_current_level, demon_restore);   // load level current level
	m_num_of_rows = m_board.get_num_of_rows();
	m_num_of_cols = m_board.get_num_of_cols();
	m_num_of_stones = m_board.get_level_stones();
	m_window.create(sf::VideoMode::VideoMode(m_num_of_rows * 70, m_num_of_cols * 70 + 40), "Digger"); 
	m_background.setTexture(Multimedia_Files::instance().Get_Texture(Multimedia_Files::background)); // load background
	m_background.setTextureRect(sf::IntRect(0, 0, m_num_of_rows * 70, m_num_of_cols * 70));
}

//main game function control
void Controller::start_game()
{      
	// load music using singleton
	audio_start_game.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::start_game));
	audio_digger_strike.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::digger_strike));
	audio_soundtrack.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::soundtrack));
	audio_game_over.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::game_over_menu));

	audio_soundtrack.play();           // play soundtrack
	audio_soundtrack.setLoop(true);    // loop soundtrack

	m_new_level = m_menu.start(m_window); // start menu
	
	if (m_new_level)
	{
		load_level();    // load level 1
		audio_start_game.play();
	}

	int Level_time = m_board.get_level_Upload_timer();
	int direction = 4;
	int prev_direction = direction;

	while (m_window.isOpen()) // main loop
	{
		m_elapsed_time = Level_clock.getElapsedTime().asSeconds();
		m_elapsed_time = Level_time - m_elapsed_time;

		game_score.setCharacterSize(24);
		lives.setCharacterSize(24);  
		stones.setCharacterSize(24);
		current_level.setCharacterSize(24);
		time.setCharacterSize(24);
		
		game_score.setPosition(0, m_board.get_num_of_cols() * 70);
		lives.setPosition(180, m_board.get_num_of_cols() * 70);      
		stones.setPosition(360, m_board.get_num_of_cols() * 70);   
		current_level.setPosition(540, m_board.get_num_of_cols() * 70);
		time.setPosition(720, m_board.get_num_of_cols() * 70);    
		
		game_score.setFont(Multimedia_Files::instance().GetFont());
		lives.setFont(Multimedia_Files::instance().GetFont());
		stones.setFont(Multimedia_Files::instance().GetFont());
		current_level.setFont(Multimedia_Files::instance().GetFont());
		time.setFont(Multimedia_Files::instance().GetFont());

		if (m_board.get_level_diamonds() == m_board.get_eaten_diamonds()) // if finished a level
		{
			Level_clock.restart();				//restart the clock
			m_board.clear_all();			    //empty the vectors
			m_current_level++;					//next level
			int score = m_status.get_score();   
			m_status.set_score(score + 20);    

			if (m_current_level > 5) // finished the game
			{
				audio_soundtrack.stop();
				m_new_level = m_menu.win(m_window);   //finishing menu
				if (m_new_level)
				{			
					audio_soundtrack.play();
					m_status.set_life(3);
					m_status.set_score(0);
					m_board.set_eaten_diamonds(0);
					m_current_level = 1;
					m_board.clear_all();
					load_level();                 // start a new game

					audio_start_game.play();
					
					m_status.set_speed(m_status.get_basic_speed());
					direction = 4;
				}
			}
			else // load next level
			{
				m_board.clear_all();
				load_level(); 
				Level_time = m_board.get_level_Upload_timer();    //get time
				audio_start_game.play();
				m_status.set_speed(m_status.get_basic_speed());  
			}
			direction = 4;     //stop movement
			m_status.set_speed(m_status.get_basic_speed());
		}

		sf::Event Event;
		while (m_window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::KeyPressed:			   // get direction of digger
				prev_direction = direction;
				switch (Event.key.code)
				{
				case sf::Keyboard::Up: 
					direction = 0;  			
					break;
				case sf::Keyboard::Down: 
					direction = 1;
					break;
				case sf::Keyboard::Left: 
					direction = 2;
					break;
				case sf::Keyboard::Right: 
					direction = 3;
					break;
				case sf::Keyboard::Space:
					direction = 4;
				}
				break;
			}
			if (Event.type == sf::Event::Closed)
				m_window.close();		
		}

		currentSec = clock.getElapsedTime().asSeconds();				  
		if (currentSec - next_sec_digger > (1 / m_status.get_speed()))     //digger speed
		{
			bool collision = false,
				 stone_collision = false,
				 stone_boost = false,
				 time_boost = false;
			
			if (m_board.move_digger(prev_direction, direction, &m_status, &present_clock,
									 collision, stone_collision, stone_boost, time_boost))
			{
				prev_direction = direction;
			}

			if (m_elapsed_time == 0 || collision || m_num_of_stones == 0)
			{
				if (m_elapsed_time == 0 || m_num_of_stones == 0)
				{
					m_board.set_first_position();
					demon_restore = false;
					m_board.load_level(m_current_level, demon_restore);
				}

				if ( collision )
					m_board.set_first_position();

				demon_restore = true;       //if only stones = 0 or time = 0
				Level_time = m_board.get_level_Upload_timer();
				Level_clock.restart();
				m_num_of_stones = m_board.get_level_stones();
				m_status.decrease_life();

				if (m_status.get_lives() != 0 )
					audio_digger_strike.play();

				direction = 4;
			}

			present_speed_timer = present_clock.getElapsedTime();

			if (present_speed_timer.asSeconds() >= 20.f && m_status.get_speed_present()) // speed for 20 seconds
				m_status.set_speed(m_status.get_basic_speed());

			if (stone_collision)
				m_num_of_stones -= 1;

			if (stone_boost)
				m_num_of_stones++;

			if (time_boost && m_elapsed_time > -1 )
				Level_time += 10;

			if (m_elapsed_time <= 10)                //paint time red if time is under 10
				time.setFillColor(sf::Color::Red);
			else
				time.setFillColor(sf::Color::White);

			s_score.str("");
			s_lives.str("");
			s_stones.str("");
			s_time.str("");
			s_current_level.str("");

			s_score << "Score: " << m_status.get_score();
			s_lives << "Lives: " << m_status.get_lives();
			s_stones << "Stones: " << m_num_of_stones;
			s_time << "Time: " << m_elapsed_time;
			s_current_level << "Level: " << m_current_level;

			game_score.setString(s_score.str());
			lives.setString(s_lives.str());
			stones.setString(s_stones.str());
			time.setString(s_time.str());
			current_level.setString(s_current_level.str());

			next_sec_digger = currentSec;
		}
		
		if (currentSec - next_sec_demon > (1 / (m_status.get_basic_speed()-50))) // move demon slower
		{
			m_board.move_demons();
			next_sec_demon = currentSec;
		}

			m_window.clear(sf::Color(0, 0, 0, 0));  //draw black status menu
			m_window.draw(m_background);			//draw background
			m_board.draw(m_window);					//draw all objects (walls/stones/diamonds/presents/digger/demons)
			m_window.draw(game_score);				//draw score
			m_window.draw(lives);					//draw lives
			m_window.draw(stones);					//draw stones
			m_window.draw(current_level);			//draw level
			if (m_elapsed_time > -1)
				m_window.draw(time);				//draw time

			m_window.display();

		if (m_status.get_lives() == 0)  // if lives ended, game is over
		{
			audio_game_over.play();		 // load game over menu
			audio_soundtrack.stop();
			m_new_level = m_menu.lose(m_window);

			if (m_new_level)				// restart the game
			{
				audio_soundtrack.play();
				m_status.set_life(3);
				m_status.set_score(0);
				m_board.set_eaten_diamonds(0);
				m_current_level = 1;
				audio_start_game.play();
				m_board.clear_all();
				load_level();
			}
		}
	}
}

Controller::~Controller()
{}
