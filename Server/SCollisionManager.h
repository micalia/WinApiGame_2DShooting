#pragma once

class SCollider;

class SCollisionManager
{
	DECLARE_SINGLE(SCollisionManager);

public:
	void Init();
	void Update();

	void AddCollider(shared_ptr<SCollider> collider);
	void RemoveCollider(shared_ptr<SCollider> collider);

private:
	vector<shared_ptr<SCollider>> _colliders;
};

