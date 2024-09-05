#include "pch.h"
#include "SCollider.h"
#include "SSphereCollider.h"
#include "SBoxCollider.h"
#include "Actor.h"
#include "Player.h"

SCollider::SCollider(SColliderType colliderType) : _colliderType(colliderType)
{
}

SCollider::~SCollider()
{

}

void SCollider::BeginPlay()
{
	Super::BeginPlay();
}

void SCollider::TickComponent()
{
	Super::TickComponent();
}

bool SCollider::CheckCollision(shared_ptr<SCollider> other)
{
	/*if (dynamic_cast<Player*>(other->GetOwner())) {
		int a = 1;
	}*/
	uint8 layer = other->GetCollisionLayer();
	if (_collisionFlag & (1 << layer))
		return true;

	return false;
}

// https://m.blog.naver.com/winterwolfs/10165506488
bool SCollider::CheckCollisionBox2Box(shared_ptr<SBoxCollider> b1, shared_ptr<SBoxCollider> b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();
	RECT intersect = {};

	return ::IntersectRect(&intersect, &r1, &r2);

	//Vec2 p1 = b1->GetOwner()->GetPos();
	//Vec2 s1 = b1->GetSize();

	//Vec2 p2 = b2->GetOwner()->GetPos();
	//Vec2 s2 = b2->GetSize();

	//float minX_1 = p1.x - s1.x / 2;
	//float maxX_1 = p1.x + s1.x / 2;
	//float minY_1 = p1.y - s1.y / 2;
	//float maxY_1 = p1.y + s1.y / 2;

	//float minX_2 = p2.x - s2.x / 2;
	//float maxX_2 = p2.x + s2.x / 2;
	//float minY_2 = p2.y - s2.y / 2;
	//float maxY_2 = p2.y + s2.y / 2;

	//if (maxX_2 < minX_1)
	//	return false;

	//if (maxX_1 < minX_2)
	//	return false;

	//if (maxY_1 < minY_2)
	//	return false;

	//if (maxY_2 < minY_1)
	//	return false;	

	//return true;
}

bool SCollider::CheckCollisionSphere2Box(shared_ptr<SSphereCollider> s1, shared_ptr<SBoxCollider> b2)
{
	return false;
}

bool SCollider::CheckCollisionSphere2Sphere(shared_ptr<SSphereCollider> s1, shared_ptr<SSphereCollider> s2)
{
	Vector p1 = s1->GetOwner()->GetPos();
	float r1 = s1->GetRadius();

	Vector p2 = s2->GetOwner()->GetPos();
	float r2 = s2->GetRadius();

	Vector dir = p1 - p2;
	float dist = dir.Length();

	return dist <= r1 + r2;
}

void SCollider::AddCollisionFlagLayer(SCOLLISION_LAYER_TYPE layer)
{
	_collisionFlag |= (1 << layer);
}

void SCollider::RemoveCollisionFlagLayer(SCOLLISION_LAYER_TYPE layer)
{
	_collisionFlag &= ~(1 << layer);
}
