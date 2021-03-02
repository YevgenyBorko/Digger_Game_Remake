#include "Board.h"

Board::Board()
	: m_eaten_diamonds(0), m_eaten_stones(0)
{}

//set the eaten diamonds in the level
void Board::set_eaten_diamonds(int num) 
{
	m_eaten_diamonds = num;
}
//-----------rotate the digger--------------
void Board::rotateDigger(int direction) const
{
	switch (direction)
	{
	case 0:
		m_digger->rotate(270);  // rotate up
		m_digger->rotate_to_first_position();
		break;
	case 1:
		m_digger->rotate(90);   // rotate down
		m_digger->rotate_to_first_position();
		break;
	case 2:
		m_digger->rotate(270);  // rotate left
		m_digger->rotate_mirror();
		m_digger->rotate(0);
		break;
	case 3:
		m_digger->rotate(0);    // rotate right
		m_digger->rotate_to_first_position();
		break;
	}
	
}
//get the num of diamonds in a level
int Board::get_level_diamonds() const
{
	return m_level.get_num_diamonds();
}

//get the num of stones in a level
int Board::get_level_stones() const
{
	return m_level.get_num_stones();
}


//get the num of time in the current level
int Board::get_level_Upload_timer() const
{
	return m_level.get_level_time();
}


//get the eaten diamonds in a level
int Board::get_eaten_diamonds() const
{
	return m_eaten_diamonds;
}


//get the num of rows in the file
int Board::get_num_of_rows() const
{
	return m_level.get_num_of_rows(); 
}

//get the num of cols in the file
int Board::get_num_of_cols() const
{
	return m_level.get_num_of_cols(); 
}

//load the game file according to the level name
void Board::load_level(int level, bool demon_restore) 
{
	m_eaten_diamonds = 0;
	std::string level_name = "level" + std::to_string(level) + ".txt";
	m_level.load_level(level_name, m_digger, &m_obstacle, &m_demon, demon_restore);
}

//check the collision between the digger and the diamond/stone/present
bool Board::digger_diamond_stone_present_collision(sf::Vector2f position, Game_Status * stat,
		  	 sf::Clock* present_clock, bool &stone_collision, bool &stone_boost, bool &time_boost) 
{
	unsigned int left = (position.x) / 70,
				 top = (position.y) / 70,
				 right = ((position.x) + 55) / 70,
				 down = ((position.y) + 55) / 70;
		
	
	//if digger went from left to right or from down to up
	if (m_obstacle[left][top] != nullptr)
	{
		char type = m_obstacle[left][top]->get_type();
		if (type == '@' || type == '+' || type == 'D') // if Diamond/present/stone is found
		{															
			// if got on the Diamond/present/stone
			if (m_digger->get_pic().getGlobalBounds().intersects(m_obstacle[left][top]->get_pic().getGlobalBounds()))
			{
				m_obstacle[left][top] = nullptr;

				//if got present
				if (type == '+')
				{	
					int option = m_level.get_array_num(left, top);
					switch (option)
					{
					case 0:                    //stone present bonus
						stone_boost = true;
						m_stone_boost_audio.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::stone_boost));
						m_stone_boost_audio.play();
						break;
					case 1:					   //time present bonus 
						time_boost = true;
						m_time_boost_audio.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::time_boost));
						m_time_boost_audio.play();
						break;
					case 2:						//speed present bonus
						present_clock->restart();
						stat->set_speed_present(true);
						stat->set_speed(stat->get_speed() + (stat->get_speed() * 0.2));
						m_speed_boost_audio.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::speed_boost));
						m_speed_boost_audio.play();
						break;
					case 3:					   //score present bonus 
						int score = stat->get_score();
						stat->set_score(score + 15);
						m_score_boost_audio.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::score_boost));
						m_score_boost_audio.play();
						break;
					}
					return false;
				}
				if (type == '@') // if got stone
				{
					stone_collision = true;
					m_eaten_stones--;
					return false;
				}
				return true;
			}
		}
	}

	//if digger went from right to left or from up to down
	if (m_obstacle[right][down] != nullptr)
	{
		char type = m_obstacle[right][down]->get_type();
		if (type == '@' || type == '+' || type == 'D') // if Diamond/present/stone is found
		{	
			// if got on the Diamond/present/stone
			if (m_digger->get_pic().getGlobalBounds().intersects(m_obstacle[right][down]->get_pic().getGlobalBounds()))
			{
				m_obstacle[right][down] = nullptr;

				//if got present
				if (type == '+')
				{
					int option = m_level.get_array_num(right, down);
					switch (option)
					{
					case 0:                    //stone present bonus
						stone_boost = true;
						m_stone_boost_audio.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::stone_boost));
						m_stone_boost_audio.play();
						break;
					case 1:					   //time present bonus 
						time_boost = true;
						m_time_boost_audio.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::time_boost));
						m_time_boost_audio.play();
						break;
					case 2:						//speed present bonus
						present_clock->restart();
						stat->set_speed_present(true);
						stat->set_speed(stat->get_speed() + (stat->get_speed() * 0.2));
						m_speed_boost_audio.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::speed_boost));
						m_speed_boost_audio.play();
						break;
					case 3:					   //score present bonus 
						int score = stat->get_score();
						stat->set_score(score + 15);
						m_score_boost_audio.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::score_boost));
						m_score_boost_audio.play();
						break;
					}
					return false;
				}
				if (type == '@') // if got stone
				{
					stone_collision = true;
					m_eaten_stones--;
					return false;
				}
				return true;
			}
		}
	}
	return false;
}


//------check the collision between a Digger and a wall-------
bool Board::digger_wall_collision(int x, int y, char type) const
{
	if (m_digger->get_pic().getGlobalBounds().intersects(m_obstacle[x][y]->get_pic().getGlobalBounds()) && type != '@')
		return true;

	return false;
}

//----------check the collision between a demon and a wall----------
bool Board::demon_wall_collision(int x, int y, int demon_index) const
{
	if (m_demon[demon_index]->get_pic().getGlobalBounds().intersects(m_obstacle[x][y]->get_pic().getGlobalBounds()))
		return true;

	return false;
}


//--------------------------check wall colision with the digger or demon-----------------------------
bool Board::wall_collision(sf::Vector2f position, int direction, bool digger, int demon_index)  const
{
		unsigned int x = (position.x) / 70,    
				     y = (position.y) / 70;       

		if (direction == 1)
			y++;
		if (direction == 3)
			x++;

		int width = m_level.get_num_of_cols(),
			height = m_level.get_num_of_rows();

		//---------------run on wall collison check------------------
		for (int i = x - 1; i <= x + 1 && i != -1 && i != height; i++)
		{
			if (y <= width - 1 && m_obstacle[i][y] != nullptr)
			{
				char type = m_obstacle[i][y]->get_type();
				if (type == '#' || type == '@')				//if got to stone/wall
					if (digger)
					{
						if (digger_wall_collision(i, y, type))
							return true;
					}
					else  // if demon
						if (demon_wall_collision(i, y, demon_index))
							return true;
			}
		}
		
		//---------------run on wall collison check------------------
		for (int i = y - 1; i <= y + 1 && i != -1 && i != width; i++)
		{
			if (x <= height - 1 && m_obstacle[x][i] != nullptr)
			{
				char type = m_obstacle[x][i]->get_type();
				if (type == '#' || type == '@')				//if got to stone/wall
				{
					if (digger)
					{
						if (digger_wall_collision(x, i, type))
							return true;
					}
					else // if demon
						if (demon_wall_collision(x, i, demon_index))
							return true;
				}
			}
		}
	return false;
}

//----------------------------------------------digger movement function-----------------------------------------------
bool Board::move_digger(int prev_direction, int direction, Game_Status * stat, sf::Clock* present_clock, bool &collision,
						 bool &stone_collision, bool &stone_boost, bool &time_boost) 
{
	bool user_direction = false;
	sf::Vector2f prev_pos = m_digger->get_position();

	m_digger->move(direction);

	//checks if there is a wall collision 
	if (wall_collision(sf::Vector2f(m_digger->get_pic().getGlobalBounds().left, 
		m_digger->get_pic().getGlobalBounds().top), direction, true, 0))
	{
		m_digger->set_position(prev_pos - sf::Vector2f(27.5f, 27.5f));  
		if (prev_direction != direction)
		{
			m_digger->move(prev_direction);    //happens because of a wall collision
			
				if (wall_collision(sf::Vector2f(m_digger->get_pic().getGlobalBounds().left,   //uses the previous direction
					m_digger->get_pic().getGlobalBounds().top), prev_direction, true, 0))
				{
					m_digger->set_position(prev_pos - sf::Vector2f(27.5f, 27.5f));	  
				}
		}
	}
	else
	{
		rotateDigger(direction);
		user_direction = true;
	}
	
	//-------------------------check collision with diamond/stone/present------------------------
	if (digger_diamond_stone_present_collision(sf::Vector2f(m_digger->get_pic().getGlobalBounds().left,
		m_digger->get_pic().getGlobalBounds().top), stat, present_clock, stone_collision, stone_boost, time_boost))
	{
		m_eaten_diamonds++;
		int score = stat->get_score();
		stat->set_score(score + 15);
		m_diamond_collision_audio.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::diamond_collision));
		m_diamond_collision_audio.play();
	}

	if (stone_collision)
	{
		m_eaten_stones++;
		m_stone_collision_audio.setBuffer(Multimedia_Files::instance().Get_Audio(Multimedia_Files::stone_collision));
		m_stone_collision_audio.play();
	}

	if (get_level_diamonds() == get_eaten_diamonds())
		m_eaten_stones = 0;

	if (m_eaten_stones == get_level_stones())
	{
		set_first_position();   
	}

	for (int i = 0; i < m_demon.size(); i++) // check the collision with demons

	{
		if (m_demon[i] != nullptr)
			if (digger_demon_collision(m_digger->get_pic(), m_demon[i]->get_pic()))             
				collision = true;
	}

	return user_direction;
}

//---demons movement---
void Board::move_demons() 
{
	for (int i = 0; i < m_demon.size(); i++)
	{
		if (!m_demon[i]->get_is_smart()) // if he's not smart
			move_simple_demon(i);
		else
		{
			int demon_x = m_demon[i]->get_position().x / 70,
				demon_y = m_demon[i]->get_position().y / 70;

			int digger_x = m_digger->get_position().x / 70,     
				digger_y = m_digger->get_position().y / 70;

			m_demon[i]->set_demon_direction(m_demon_ai.bfs({ demon_x, demon_y }, { digger_y ,digger_x },
				m_level.get_num_of_rows(), m_level.get_num_of_cols(), & m_obstacle));
			
			if (m_demon[i]->get_demon_direction() == 4)
				m_demon[i]->set_demon_direction(m_demon[i]->get_demon_prev_direction());

			prev_pos = m_demon[i]->get_position();
			m_demon[i]->move(m_demon[i]->get_demon_direction()); 

			if (wall_collision(m_demon[i]->get_position(), m_demon[i]->get_demon_direction(), false, i))
			{  
				m_demon[i]->set_position(prev_pos);
				if (m_demon[i]->get_demon_direction() == m_demon[i]->get_demon_prev_direction())
				{
					//if demon's direction is up or down than set it left
					if (m_demon[i]->get_demon_direction() == 1 || m_demon[i]->get_demon_direction() == 0)
						m_demon[i]->set_demon_prev_direction(2);    //left

					//if demon's direction is left or right than set it down
					if (m_demon[i]->get_demon_direction() == 2 || m_demon[i]->get_demon_direction() == 3)
						m_demon[i]->set_demon_prev_direction(1);    //down
				}
				prev_pos = m_demon[i]->get_position();
				m_demon[i]->move(m_demon[i]->get_demon_prev_direction());
				if (wall_collision(m_demon[i]->get_position(), m_demon[i]->get_demon_prev_direction(), false, i))
				{  
					m_demon[i]->set_position(prev_pos);
					m_demon[i]->set_demon_direction(m_demon[i]->get_demon_prev_direction());
				}
			}
			else
				if (m_demon[i]->get_demon_direction() != 4)
					m_demon[i]->set_demon_prev_direction(m_demon[i]->get_demon_direction());
		}
	}

}
//----------movement of the simple demon------------
void Board::move_simple_demon(int demon_index) const
{
	if (m_demon[demon_index] != nullptr)
	{
		sf::Vector2f prev_pos = m_demon[demon_index]->get_position();

		int x = m_demon[demon_index]->get_position().x / 70,
			y = m_demon[demon_index]->get_position().y / 70;   

		m_demon[demon_index]->move(m_demon[demon_index]->get_demon_direction());
		if (wall_collision(m_demon[demon_index]->get_position(), m_demon[demon_index]->get_demon_direction(),
			false, demon_index) )
		{
			m_demon[demon_index]->set_position(prev_pos);
			m_demon[demon_index]->set_demon_direction(rand() % 4);    //set random demon direction
		}
	}
}
//---------------------check digger and demon collision---------------------
bool Board::digger_demon_collision(sf::Sprite digger, sf::Sprite demon) const
{
	if (digger.getGlobalBounds().intersects(demon.getGlobalBounds()))
		return true;

	return false;
}

//draw all obstacles, demons and digger
void Board::draw(sf::RenderWindow & window) 
{
	//---------------draw all obsitcles--------------------
	for (unsigned int i = 0; i < m_obstacle.size(); i++)
		for (unsigned int j = 0; j < m_obstacle[0].size(); j++)
			if (m_obstacle[i][j] != nullptr)
				m_obstacle[i][j]->draw(window); 

	//-----digger draw-----
	m_digger->draw(window);    

	//--------------------------draw all demons-----------------------
	for (unsigned int i = 0; i < m_demon.size() && m_demon.size() > 0; i++)
		if (m_demon[i] != nullptr)
			m_demon[i]->draw(window);
}


//--clear all vectors --
void Board::clear_all() 
{ 
	for (int i = 0; i < m_obstacle.size(); i++)
		for (int j = 0; j < m_obstacle[0].size(); j++)
			m_obstacle[i][j] = nullptr;

	for (int i = 0; i < m_demon.size(); i++)
		m_demon[i] = nullptr;

	m_demon.resize(0);

	m_digger.reset();
}


//---set first position of all characters----
void Board::set_first_position()
{
	m_eaten_stones = 0;
	for (int j = 0; j < m_demon.size(); j++)
	{
		m_demon[j]->set_position(m_demon[j]->get_first_position());
	}

	m_digger->set_position(m_digger->get_first_position());
	m_digger->rotate(0);
}


Board::~Board()
{}