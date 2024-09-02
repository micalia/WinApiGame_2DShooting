#include "pch.h"
#include "SSphereCollider.h"
#include "Actor.h"
#include "SBoxCollider.h"

SSphereCollider::SSphereCollider() : SCollider(SColliderType::Sphere)
{

}

SSphereCollider::~SSphereCollider()
{

}

void SSphereCollider::BeginPlay()
{
	Super::BeginPlay();


}

void SSphereCollider::TickComponent()
{
	Super::TickComponent();


}

bool SSphereCollider::CheckCollision(shared_ptr<SCollider> other)
{
	if (Super::CheckCollision(other) == false)
		return false;
		
	switch (other->GetColliderType())
	{
	case SColliderType::Box:
		return CheckCollisionSphere2Box(shared_from_this(), static_pointer_cast<SBoxCollider>(other));
	case SColliderType::Sphere:
		return CheckCollisionSphere2Sphere(shared_from_this(), static_pointer_cast<SSphereCollider>(other));
	}

	return false;
}
