#pragma once
#include "Actor.h"

class Player;

class Enemy : public Actor
{
	using Super = Actor;
public:
	Enemy();
	virtual ~Enemy();

	virtual void Update() override;

	Protocol::EnemyInfo enemyInfo;

	virtual void Damaged();

	void Die(shared_ptr<Player> WhoHitMe);

	void SetHp(int32 _hp) { 
		hp = _hp; 
		enemyInfo.set_hp(hp);
	}
	int32 GetHp() { return hp; }

	void EnemyBroadcastMove();
	void SetEnemyPos(Vector pos);

	void SetSpeed(float speed){ _speed = speed;}
	float GetSpeed() { return _speed; }

	void SetEnemyInfo(EnemyRef InEnemy, Vector InSpawnPos, Protocol::EnemyType InEnemyType, float InSpeed);

	void Move(float deltaTime);
	virtual void OnComponentBeginOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other);
	virtual void OnComponentEndOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other);
	
protected:
	int32 hp = 0;
private:
	float replicateDelay = 0.1f;
	float currReplicateDelay = 0;

	float _speed = 0;
	float currPosY = 0;
};

