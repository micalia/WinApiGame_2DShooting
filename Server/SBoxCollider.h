#pragma once
#include "SCollider.h"

class SBoxCollider : public SCollider, public enable_shared_from_this<SBoxCollider>
{
	using Super = SCollider;

public:
	SBoxCollider();
	virtual ~SBoxCollider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;

	virtual bool CheckCollision(shared_ptr<SCollider> other);

	Vector GetSize() { return _size; }
	void SetSize(Vector size) { _size = size; }

	RECT GetRect();

private:
	Vector _size = {};
};

