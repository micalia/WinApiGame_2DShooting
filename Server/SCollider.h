#pragma once
#include "SComponent.h"


class SBoxCollider;
class SSphereCollider;

class SCollider : public SComponent
{
public:
	SCollider(SColliderType colliderType);
	virtual ~SCollider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;

	virtual bool CheckCollision(shared_ptr<SCollider> other);

	SColliderType GetColliderType() { return _colliderType; }
	void SetShowDebug(bool show) { _showDebug = show; }

public:
	static bool CheckCollisionBox2Box(shared_ptr<SBoxCollider> b1, shared_ptr<SBoxCollider> b2);
	static bool CheckCollisionSphere2Box(shared_ptr<SSphereCollider> s1, shared_ptr<SBoxCollider> b2);
	static bool CheckCollisionSphere2Sphere(shared_ptr<SSphereCollider> s1, shared_ptr<SSphereCollider> s2);

	void SetCollisionLayer(SCOLLISION_LAYER_TYPE layer) { _collisionLayer = layer; }
	SCOLLISION_LAYER_TYPE GetCollisionLayer() { return _collisionLayer; }

	void ResetCollisionFlag() { _collisionFlag = 0; }
	void AddCollisionFlagLayer(SCOLLISION_LAYER_TYPE layer);
	void RemoveCollisionFlagLayer(SCOLLISION_LAYER_TYPE layer);
	void SetCollisionFlag(uint32 flag) { _collisionFlag = flag; }
	uint32 GetCollisionFlag() { return _collisionFlag; }

protected:
	SColliderType _colliderType;
	bool _showDebug = true;

public:
	unordered_set<shared_ptr<SCollider>> _collisionMap;

protected:
	// 나는 누구인가?
	SCOLLISION_LAYER_TYPE _collisionLayer = CLT_OBJECT;
	// 누구랑 충돌할 것인가?
	uint32 _collisionFlag = 0xFFFFFFFF; // ~(0)
	//vector<COLLISION_LAYER_TYPE> _collideWith;
};

