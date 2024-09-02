#include "pch.h"
#include "SBoxCollider.h"
#include "Actor.h"
#include "SSphereCollider.h"

SBoxCollider::SBoxCollider() : SCollider(SColliderType::Box)
{

}

SBoxCollider::~SBoxCollider()
{

}

void SBoxCollider::BeginPlay()
{
	Super::BeginPlay();


}

void SBoxCollider::TickComponent()
{
	Super::TickComponent();


}

bool SBoxCollider::CheckCollision(shared_ptr<SCollider> other)
{
	if (Super::CheckCollision(other) == false)
		return false;

	auto val = shared_from_this();
	switch (other->GetColliderType())
	{
	case SColliderType::Box:
		return CheckCollisionBox2Box(shared_from_this(), static_pointer_cast<SBoxCollider>(other));
	case SColliderType::Sphere:
		return CheckCollisionSphere2Box(static_pointer_cast<SSphereCollider>(other), shared_from_this());
	}

	return false;
}

RECT SBoxCollider::GetRect()
{
	Vector pos = GetOwner()->GetPos();
	Vector size = GetSize();

	RECT rect =
	{
		(int32)(pos.x - (size.x / 2)),
		(int32)(pos.y - (size.y / 2)),
		(int32)(pos.x + (size.x / 2)),
		(int32)(pos.y + (size.y / 2))
	};

	return rect;
}
