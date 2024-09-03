#include "pch.h"
#include "SDestroyZone.h"
#include "SEnemyMissile.h"
#include "SCollider.h"
#include "Enemy.h"
#include "SCollisionManager.h"
#include "GameRoom.h"

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

	if (other != nullptr) {
		if (dynamic_pointer_cast<SEnemyMissile>(other->GetOwner())) {
			GET_SINGLE(SCollisionManager)->RemoveCollider(other);
			GRoom->RemoveObject(other->GetOwner()->GetObjectID());
		}
		//if (dynamic_cast<Enemy*>(other->GetOwner())
		//	|| dynamic_cast<SEnemyMissile*>(other->GetOwner()) 
		//	) {
		//	GET_SINGLE(SCollisionManager)->RemoveCollider(other);
		//	//TODO : 이 콜라이더를 소유한 액터를 파괴한다
		//	/* GET_SINGLE(SceneManager)->GetCurrentScene()->RemoveActor(other->GetOwner());*/
		//}
	}
}