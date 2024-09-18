#include "pch.h"
#include "Player.h"
#include "SCollider.h"
#include "SEnemyMissile.h"
#include "Enemy.h"
#include "SCollisionManager.h"
#include "GameRoom.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Damaged() {
	int hp = GetHp();
	SetHp(--hp);
	if (GetHp() > 0 && room != nullptr) {
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_PlayerDamaged(info);
		room->Broadcast(sendBuffer);
	}
}

void Player::OnComponentBeginOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other)
{
	Super::OnComponentBeginOverlap(collider, other);

	if (other != nullptr) {
		if (dynamic_pointer_cast<SEnemyMissile>(other->GetOwner())
			//|| dynamic_pointer_cast<Enemy>(other->GetOwner())
			) { 
			other->GetOwner()->RemoveComponent(other);
			GET_SINGLE(SCollisionManager)->RemoveCollider(other);
			GRoom->RemoveObject(other->GetOwner()->GetObjectID());

			_pos = GRoom->GetRespawnStartPos();
			SetPos(_pos);
			Damaged();
		}
	}
}
