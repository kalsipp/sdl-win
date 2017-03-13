#pragma once


class Actor;
#include "actor.hpp"
#include "mainclass.hpp"
//class Mainclass;
class Player:public Actor{
public:
	Player(Mainclass *);
	virtual void update();

private:

	


};