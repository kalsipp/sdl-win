
#pragma once

#include "gameobject.hpp"
#include "collider.hpp"
class Interactable:Gameobject{
public:
	virtual void interact();
	Collider & trigger_collider();
private:
	Collider * m_trigger_collider = NULL;
};
/*
*/