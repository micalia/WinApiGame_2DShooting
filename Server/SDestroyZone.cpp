#include "pch.h"
#include "SDestroyZone.h"
#include "SEnemyMissile.h"
#include "SCollider.h"
#include "Enemy.h"
#include "SCollisionManager.h"
#include "GameRoom.h"
#include "SMissile.h"

SDestroyZone::SDestroyZone()
{

}

SDestroyZone::~SDestroyZone()
{

}

void SDestroyZone::Update()
{
	Super::Update();
}

void SDestroyZone::OnComponentBeginOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other)
{
	Super::OnComponentBeginOverlap(collider, other);

	
}

void SDestroyZone::OnComponentEndOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other)
{
	Super::OnComponentEndOverlap(collider, other);

	if (other != nullptr) {
		if (dynamic_pointer_cast<SEnemyMissile>(other->GetOwner())
			|| dynamic_pointer_cast<Enemy>(other->GetOwner())
			|| dynamic_pointer_cast<SMissile>(other->GetOwner())
			) {
			other->GetOwner()->RemoveComponent(other);
			GET_SINGLE(SCollisionManager)->RemoveCollider(other);
			GRoom->RemoveObject(other->GetOwner()->GetObjectID());
		}
	}
}
