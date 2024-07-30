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

	virtual void Fire();

	void Die(Player* WhoHitMe);

	void SetHp(int32 _hp) { _hp = hp; }
	int32 GetHp() { return hp; }

	void SetTarget(Player* InTarget) { target = InTarget; };
protected:
	int32 hp = 100;
	float speed = 10;
	Player* target = nullptr;

	float fireDelayTime = 1;
	float fireDelayCurrTime = 0;
};

