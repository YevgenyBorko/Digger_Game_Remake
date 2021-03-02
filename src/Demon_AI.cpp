#include "Demon_AI.h"

Demon_AI::Demon_AI()
{
	m_direction = { UP,DOWN,LEFT,RIGHT };
	m_direction_name = { up,down,left,right };
}

						      //demon            //digger
int Demon_AI::bfs(sf::Vector2i start, sf::Vector2i target,
	int num_rows, int num_cols,
	std::vector< std::vector < std::unique_ptr <Obstacle> > > * obstacle_vec)
{
	bool found_destination = false, //check if we got to the digger
		 first = true;

	std::vector <std::vector <Node> > map; // map of the level
	save_start = start;		   //save the first demon position
	m_destination = target;    //digger position
	m_source = start;

	if (m_destination == m_source)
		return 4;

	// initialize all the location in the map that has not been visited
	for (int i = 0; i < num_cols; i++)
	{
		map.push_back({});

		for (int j = 0; j < num_rows; j++)
		{
			map.back().push_back({});
			map[i][j].discovered = false;
		}
	}

	m_que.clear(); 

	m_que.push_back(start); // push the demon to the queue

	while (!m_que.empty() && !found_destination)
	{
		save_start = m_que[0];
		save_double = m_que[0];
		m_que.erase(m_que.begin());

		// we visit all neighbors of the top location of the queue
		for (int i = 0; i < 4 && !found_destination; i++)
		{
			found_destination = check_node(save_start, m_direction[i], obstacle_vec, &map, num_rows, num_cols, i);

			save_start = save_double;
		}
		map[save_double.y][save_double.x].discovered = true;
	}

	// initialize all the location in the map to not be visited for the next time
	for (int i = 0; i < num_cols; i++)
	{
		for (int j = 0; j < num_rows; j++)
		{
			map[i][j].discovered = false;
		}
	}

	if (m_que.size() == 0) // check if we found the target
		return 4;

	sf::Vector2i inverse_vertex = m_que.at(m_que.size() - 1); // store the target position

	direction_type path; // store the direction of the demon

	// check if we got to the source
	while ((inverse_vertex != m_source))
	{
		if (map[inverse_vertex.y][inverse_vertex.x]._direction == LEFT)
		{
			inverse_vertex.x -= 1;
			path = left;
		}
		else if (map[inverse_vertex.y][inverse_vertex.x]._direction == RIGHT)
		{
			inverse_vertex.x += 1;
			path = right;

		}
		else if (map[inverse_vertex.y][inverse_vertex.x]._direction == UP)
		{
			inverse_vertex.y -= 1;
			path = up;

		}
		else
		{
			inverse_vertex.y += 1;
			path = down;
		}

		sf::Vector2i demon_path = map[inverse_vertex.y][inverse_vertex.x]._direction;
	}
	if (path == left)
		return 3;
	if (path == right)
		return 2;
	if (path == up)
		return 1;

	return 0;
}
	//checks every neighbor if its a wall or been visitied, else we push it to the queue
bool Demon_AI::check_node(sf::Vector2i &vertex, sf::Vector2i curr_direction,
	std::vector< std::vector < std::unique_ptr <Obstacle> > > * obstacle_vec,
	std::vector <std::vector <Node> > *map_ptr, int num_rows, int num_cols, int index)
{
	stat_vertex = vertex; 
	// check direction
	for (int i = 0; i < m_direction_name.size(); i++)
		if (m_direction[i] == curr_direction)
		{
			switch (m_direction_name[i])
			{
			case left:
				vertex.x = vertex.x - 1;
				break;
			case right:
				vertex.x = vertex.x + 1;
				break;
			case up:
				vertex.y = vertex.y - 1; 					 
				break;
			case down:
				vertex.y = vertex.y + 1;
				break;
			}
		}
	// check if the location is in the board
	if (vertex.y >= num_cols || vertex.y < 0 || vertex.x >= num_rows || vertex.x < 0)
		return false;

		// check if there is a Game Object in this location on the map
		if (obstacle_vec->at(vertex.x).at(vertex.y) != nullptr)
		{
			// check if its a wall or stone if we already visited this location on the map
			if (obstacle_vec->at(vertex.x).at(vertex.y)->get_type() != '#'
				&& obstacle_vec->at(vertex.x).at(vertex.y)->get_type() != '@'
				&& map_ptr->at(vertex.y).at(vertex.x).discovered == false)
			{
				map_ptr->at(vertex.y).at(vertex.x).discovered = true;
				map_ptr->at(vertex.y).at(vertex.x)._direction = curr_direction * -1;

				m_que.push_back(vertex);
				opposite = { vertex.y, vertex.x };

				if (m_destination == opposite)
					return true;
			}
		}

		if ((obstacle_vec->at(vertex.x).at(vertex.y) == nullptr))
		{
			// check if we already visited this location on the map
			if (map_ptr->at(vertex.y).at(vertex.x).discovered == false)
			{
				map_ptr->at(vertex.y).at(vertex.x).discovered = true;
				map_ptr->at(vertex.y).at(vertex.x)._direction = curr_direction * -1;
				m_que.push_back(vertex);
				sf::Vector2i opposite = { vertex.y,vertex.x };

				if (m_destination == opposite)
					return true;
			}
		}
	return false;
}

Demon_AI::~Demon_AI()
{}



