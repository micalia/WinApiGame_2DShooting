#pragma once
#include "Actor.h"
class SEnemyMissile : public Actor
{
	using Super = Actor;
public:
	SEnemyMissile();
	virtual ~SEnemyMissile();

	virtual void Update() override;

	Protocol::EnemyMissileInfo enemyMissileInfo;
};

