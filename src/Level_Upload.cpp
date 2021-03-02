#include "Level_Upload.h"

Level_Upload::Level_Upload()
	: m_level_diamond_num(0), m_rows(0), m_cols(0), m_stones(0), m_level_time(0)
{}

//-----gets the num of rows in the file---
int Level_Upload::get_num_of_rows() const
{
	return m_rows;
}

//-----gets the num cols in the file----
int Level_Upload::get_num_of_cols() const
{
	return m_cols;
}

//----------------------------loads the vectors from the file--------------------------
void Level_Upload::load_level(std::string level_name, std::unique_ptr <Digger> & digger,
	std::vector < std::vector < std::unique_ptr <Obstacle> > > * obstacle_vec,
	std::vector < std::unique_ptr <Demon> > *demon_vec, bool demon_restore) 
{
	m_level_diamond_num = 0;
	std::ifstream levelfile;
	int x = 0, y = 0, stones = 0, level_time = 0;
	levelfile.open(level_name);

	char current;
	if (levelfile.is_open())
	{
		levelfile >> x >> y >> stones >> level_time;
		levelfile.get(current); // used to get the newline char to start getting symbols from the board
	}
	
	m_rows = y;
	m_cols = x;
	m_stones = stones;
	m_level_time = level_time;

		obstacle_vec->resize(y);
		for (int i = 0; i < y; ++i)
			obstacle_vec->at(i).resize(x);

	int smart_demon_counter = 0;    //gets the counter because of the bfs algorithm 

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			levelfile.get(current);
			if (current != ' ' && current != '\n')
			{
				if (current == '/' )						// digger
					update_digger(digger, current, j, i);
				else
					if (current == '!' && demon_restore)	// demon
						insert_demon_to_vec(demon_vec, current, j, i, smart_demon_counter); 
					else									// wall/diamond/stone/present
						insert_to_obstacle(obstacle_vec, rand_num_array, current, j, i);
			}
		}
		levelfile.get(current); // for the '\n'
	}
	levelfile.close();
}


//---------------------------------updtes the digger location------------------------------------
void Level_Upload::update_digger(std::unique_ptr <Digger> &digger, char type, int x, int y) const
{
	sf::Vector2f fixed_location((x * 70.f) + 10.f, (y * 70.f) + 10.f); 

	digger = std::make_unique <Digger>(fixed_location, type); // place the digger
	digger->set_position(fixed_location);
}

//-----------------------------------inserts a demon to the vector--------------------------------
void Level_Upload::insert_demon_to_vec(std::vector < std::unique_ptr <Demon> > *demon_vec, char type,
										int x, int y, int &counter) const
{
	sf::Vector2f fixed_location(x * 70.f, y * 70.f);           
	
	int random = rand() % 2;
		
	if (random == 0 && counter < 2) //limits the creation of smart demons to 2
	{
		demon_vec->push_back(std::make_unique<Smart_Demon>(fixed_location, type, true));
		counter++;
	}
	else // create simple demon
		demon_vec->push_back(std::make_unique<Simple_Demon>(fixed_location, type, false));
}

//---------------------------------inserts a wall/diamond/stone/present---------------------------------------
void Level_Upload::insert_to_obstacle(std::vector< std::vector < std::unique_ptr <Obstacle> > > * obstacle_vec,
									  int rand_num_array[50][50], char type, int x, int y) 
{
	sf::Vector2f fixed_location(x * 70.f, y * 70.f);               

	switch(type)
	{
		case 'D':       // make a diamond
			m_level_diamond_num++;
			obstacle_vec->at(x).at(y) = std::make_unique<Diamond>(fixed_location, type);
			break;
		case '#':		// make a wall
			obstacle_vec->at(x).at(y) = std::make_unique<Wall>(fixed_location, type);
			break;
		case '@':		// make a stone
			obstacle_vec->at(x).at(y) = std::make_unique<Stone>(fixed_location, type);
			break;
		case '+':	    // make a present 
			int present_choice = rand() % 4;
			rand_num_array[x][y] = present_choice;   //stores the index of present choice to use at board
			switch (present_choice)
			{
				case 0 : 
					obstacle_vec->at(x).at(y) = std::make_unique<Stone_Present>(fixed_location, type);
					break;
				case 1 :
					obstacle_vec->at(x).at(y) = std::make_unique<Time_Present>(fixed_location, type);
					break;
				case 2:
					obstacle_vec->at(x).at(y) = std::make_unique<Speed_Present>(fixed_location, type);
					break;
				case 3:
					obstacle_vec->at(x).at(y) = std::make_unique<Score_Present>(fixed_location, type);
					break;
			}
			break;
	}
}

//--gets the num of diamonds in a level---
int Level_Upload::get_num_diamonds() const
{
	return m_level_diamond_num;
}


//-------gets rand array index of presents--------
int Level_Upload::get_array_num(int x, int y) const
{
	return rand_num_array[x][y];
}

//--gets the num of stones in the level--
int Level_Upload::get_num_stones() const
{
	return m_stones;
}

//----------gets level time-------------
int Level_Upload::get_level_time() const
{
	return m_level_time;
}


Level_Upload::~Level_Upload()
{}
