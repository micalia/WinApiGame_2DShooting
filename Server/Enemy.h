#pragma once
#include "Actor.h"
class Enemy : public Actor
{
	using Super = Actor;
public:
	Enemy();
	virtual ~Enemy();

	virtual void Update();

	Protocol::EnemyInfo enemyInfo;
};

