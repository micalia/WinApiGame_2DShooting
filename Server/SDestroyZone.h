#pragma once
#include "Actor.h"
class SDestroyZone : public Actor
{
	using Super = Actor;
public:
	SDestroyZone();
	virtual ~SDestroyZone() override;

	virtual void Update() override;
	virtual void OnComponentBeginOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other) override;
	virtual void OnComponentEndOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other) override;
};

