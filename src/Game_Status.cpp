#include "Game_Status.h"

Game_Status::Game_Status(int score, int lives, float basic_speed, float speed)
	: m_score(score), m_lives(lives), m_basic_speed(basic_speed), m_speed(speed), m_speed_present(false)
{}

//-------get the digger score-------
int Game_Status::get_score() const
{
	return m_score;
}

//-------sets the digger score-------
void Game_Status::set_score(int score) 
{
	m_score = score;
}

//-------get the digger life-------
int Game_Status::get_lives()  const
{
	return m_lives;
}

//-------sets the digger life-------
void Game_Status::set_life(int lives) 
{
	m_lives = lives;
}

//-------decrease life by 1-------
void Game_Status::decrease_life() 
{
	this->m_lives = this->m_lives - 1;
}

//-----------gets speed present-----------
bool Game_Status::get_speed_present() const
{
	return m_speed_present;
}

//-------------sets speed present---------------
void Game_Status::set_speed_present(bool set_speed_true) 
{ 
	m_speed_present = set_speed_true;
}

//-------get digger speed----------
float Game_Status::get_speed() const
{
	return m_speed;
}

//----sets digger or demon speed------
void Game_Status::set_speed(float speed)
{
	m_speed = speed;
}

//-----------gets basic speed------------
float Game_Status::get_basic_speed() const
{
	return m_basic_speed;
}

Game_Status::~Game_Status()
{}
