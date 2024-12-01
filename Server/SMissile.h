#pragma once
#include "Actor.h"
class SMissile : public Actor
{
	using Super = Actor;
public:
	SMissile();
	virtual ~SMissile();

	virtual void Update() override;

	void Move(float deltaTime);
	void MissileBroadcastMove();
private:
	float replicateDelay = 0;
	float currReplicateDelay = 0;

	float speed = 300;
};

