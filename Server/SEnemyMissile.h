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

	void Move();
	void MissileBroadcastMove();
private:
	float replicateDelay = 0.1f;
	float currReplicateDelay = 0;

	float speed = 200;
};

