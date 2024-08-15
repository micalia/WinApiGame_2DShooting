#pragma once
#include "Actor.h"
class Player : public Actor
{
public:
	Player();
	virtual ~Player();

public:
	GameSessionRef session;
	string name;
};

