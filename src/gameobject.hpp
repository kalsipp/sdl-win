#pragma once
#include <string>
#include <SDL.h>
#include <cmath>

#include "mainclass.hpp"
#include "texture.hpp"
#include "spritesheet.hpp"
#include "position.hpp"
#include "collider.hpp"
class Mainclass;
class Spritesheet;
class Gameobject{
public:
	Gameobject(const Mainclass *);
	virtual void update();
	virtual ~Gameobject();
	virtual void move(float, float);
	virtual void update_anim();
	void move_to(float, float);
	void move_to(const Position &); //Move to is a hard position set and sets oldpos = new pos
	void scale(float); 
	Position & position();
	Position position()const;
	Collider & collider();
	const int & z()const;
	float & move_speed();
	Spritesheet * spritesheet();
	void render();
	bool load_from_file(const std::string&);
	bool operator< (const Gameobject& right)const;
protected:
	void init_animations();
	bool anim_tick = false;
	//void update_anim(float, float);
	Position m_position;
	Position m_diff_movement;
	//std::pair<float,float> m_old_movement = {0,0};
	int m_z=0;
	float m_move_speed = 3.0f;

	Collider * m_collider = NULL;
	Spritesheet * m_spritesheet = NULL;
	Spritesheet * m_sheet = NULL;
	const Mainclass * m_mainclass = NULL;

	//Animation cycles
	/*

	*/



};