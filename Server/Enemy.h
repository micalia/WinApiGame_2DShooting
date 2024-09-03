#pragma once
#include "Actor.h"
class Enemy : public Actor
{
	using Super = Actor;
public:
	Enemy();
	virtual ~Enemy();

	virtual void Update() override;

	Protocol::EnemyInfo enemyInfo;

	void EnemyBroadcastMove();
	void SetEnemyPos(Vector pos);

	void SetSpeed(float speed){ _speed = speed;}
	float GetSpeed() { return _speed; }

	void SetEnemyInfo(EnemyRef InEnemy, Vector InSpawnPos, Protocol::EnemyType InEnemyType, float InSpeed);

	void Move();
private:
	float replicateDelay = 0.1f;
	float currReplicateDelay = 0;

	float _speed = 0;
	float currPosY = 0;
};

