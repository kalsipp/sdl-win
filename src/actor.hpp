#pragma once
#include "mainclass.hpp"
#include "gameobject.hpp"

class Gameobject;
class Actor:public Gameobject{
public:
	Actor(const Mainclass *);
	virtual void update_anim();
	void dynamic_movement(const std::pair<float,float> &);
protected:
	float m_idle_anim_speed = 600;
	float m_moving_anim_speed = 300;
	static const std::vector<int> ANIMATION_UP;
	static const std::vector<int> ANIMATION_DOWN;
	static const std::vector<int> ANIMATION_LEFT;
	static const std::vector<int> ANIMATION_RIGHT;
};