#pragma once

#include "SCollider.h"
class SSphereCollider : public SCollider, public enable_shared_from_this<SSphereCollider>
{
	using Super = SCollider;

public:
	SSphereCollider();
	virtual ~SSphereCollider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;

	virtual bool CheckCollision(shared_ptr<SCollider> other);

	float GetRadius() { return _radius; }
	void SetRadius(float radius) { _radius = radius; }

private:
	float _radius = 0.f;
};

