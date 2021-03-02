#pragma once

#include "Level_Upload.h"

class Game_Status
{
public:
	//----------------------------C-tor-----------------------------
	Game_Status(int score, int lives, float basic_speed, float speed);

	//--------all around functions-------
	void set_speed_present(bool set_speed_true);
	bool get_speed_present() const;
	float get_basic_speed() const;
	void set_speed(float speed);
	void set_score(int score);
	void set_life(int lives);
	float get_speed() const;
	int get_score() const;
	int get_lives() const;
	void decrease_life();

	//----C-tor----
	~Game_Status();

private:
	//----Member Variables----
	int m_score,
		m_lives;

	float m_speed,
		  m_basic_speed;

	bool m_speed_present;
};

