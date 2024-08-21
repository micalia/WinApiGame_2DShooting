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

	void EnemyBroadcastMove();
	void SetEnemyPos(Vector pos);

	void SetSpeed(float speed){ _speed = speed;}
	float GetSpeed(){ return _speed;}
private:
	float replicateDelay = 2.0f;
	float currReplicateDelay = 0;

	float _speed = 0;
};

