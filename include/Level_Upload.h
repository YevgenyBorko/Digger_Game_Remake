#pragma once

#include "Digger.h"
#include <vector>
#include <memory>
#include "Demon.h"
#include "Obstacle.h"
#include "Game_Object.h"
#include "Diamond.h"
#include "Wall.h"
#include "Stone.h"
#include "Present.h"
#include "Speed_Present.h"
#include "Score_Present.h"
#include "Time_Present.h"
#include "Stone_Present.h"
#include "Smart_Demon.h"
#include "Simple_Demon.h"
#include "iostream"
#include <fstream>

class Level_Upload
{
public:
	//----C-tor----
	Level_Upload();

	//-------------------------all around functions-------------------------
	void load_level(std::string level_name, std::unique_ptr <Digger>& digger,
		std::vector< std::vector < std::unique_ptr <Obstacle> > >* obstacle_vec,
		std::vector < std::unique_ptr <Demon> >* demon_vec, bool demon_restore);
	int get_array_num(int x, int y) const;
	int get_num_diamonds() const;
	int get_num_of_rows() const;
	int get_num_of_cols() const;
	int get_num_stones() const;
	int get_level_time() const;

	//----C-tor----
	~Level_Upload();

private:
	//------------------------------------Member functions------------------------------------
	void insert_to_obstacle(std::vector< std::vector < std::unique_ptr <Obstacle> > >* obstacle_vec,
							int rand_num_array[50][50], char type, int x, int y);
	void insert_demon_to_vec(std::vector < std::unique_ptr <Demon> >* demon_vec,
							 char type, int x, int y, int& counter) const;
	void update_digger(std::unique_ptr <Digger>& digger, char type, int x, int y) const;

	//-------Member Variables------
	int rand_num_array[50][50] = {},
		m_level_diamond_num,
		m_rows,
		m_cols,
		m_stones,
		m_level_time;
};

