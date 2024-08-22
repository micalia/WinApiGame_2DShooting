#pragma once
#include "SpriteActor.h"

class Player;

class Enemy : public SpriteActor
{
	using Super = SpriteActor;
public:
	Enemy();
	virtual ~Enemy() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;

	void Die(Player* WhoHitMe);

	void SetHp(int32 _hp) { hp = _hp; }
	int32 GetHp() { return hp; }

	void SetTarget(Player* InTarget) { target = InTarget; }

	void FindPlayer();
	virtual void Damaged(){}

	void SetKillScore(int32 addScore){ _killScore = addScore; }
	int32 GetKillScore(){ return _killScore; }
	
	void Server_AddScore(Player* whoKillMe, int32 addScore);

	Protocol::EnemyInfo enemyInfo;

	void SetServerNewLocation(Vec2 serverNewLocation) { _serverNewLocation = serverNewLocation; }
	Vec2 GetServerNewLocation() { return _serverNewLocation; }

	void SetSpeed(float speed){ _speed  = speed;}
	float GetSpeed(){ return _speed;}

	void OnRep_ServerLoc();
	void SetClientTimeBetweenLastUpdate(float _ClientTimeBetweenLastUpdate) { ClientTimeBetweenLastUpdate = _ClientTimeBetweenLastUpdate;}
protected:
	int32 hp = 0;
	int32 _killScore = 0;
	Player* target = nullptr;

private:
	float _speed = 0;
private:
	Vec2 _serverNewLocation = Vec2(0, 0);
	float ClientTimeSinceUpdate = 0.0f;
	float ClientTimeBetweenLastUpdate = 0.0f;

};

