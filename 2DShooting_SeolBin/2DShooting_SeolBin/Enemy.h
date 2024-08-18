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
protected:
	int32 hp = 0;
	float speed = 0;
	Player* target = nullptr;
};

