#pragma once
#include "Actor.h"
class Player : public Actor
{
	using Super = Actor;
public:
	Player();
	virtual ~Player();

	virtual void OnComponentBeginOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other) override;

	void Damaged();

	int GetHp() { return _hp; }
	void SetHp(int hp) { _hp = hp; }
public:
	GameSessionRef session;
	string name;

private:
	int _hp = 0;
};

