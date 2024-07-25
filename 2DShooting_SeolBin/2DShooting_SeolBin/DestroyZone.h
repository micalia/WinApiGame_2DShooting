#pragma once
#include "Actor.h"
class DestroyZone : public Actor
{
	using Super = Actor;
public:
	DestroyZone();
	virtual ~DestroyZone() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
};

