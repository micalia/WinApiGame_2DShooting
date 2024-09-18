#pragma once
#include "Actor.h"
class Player : public Actor
{
	using Super = Actor;
public:
	Player();
	virtual ~Player();

	virtual void Update() override;
	virtual void OnComponentBeginOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other) override;

	void Damaged();


	int GetHp() { return _hp; }
	void SetHp(int hp) { _hp = hp; }
public:
	GameSessionRef session;
	string name;

private:
	int _hp = 0;

	bool bRespawn = false;

	int blinkCount = 18;
	int blinkCurrCount = 0;
	float blinkTime = 0.2;
	float currBlinkTime = 0;
	bool bTransparent = false;
};

