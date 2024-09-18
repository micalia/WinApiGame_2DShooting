#include "pch.h"
#include "Player.h"
#include "SCollider.h"
#include "SEnemyMissile.h"
#include "Enemy.h"
#include "SCollisionManager.h"
#include "GameRoom.h"
#include "SeverTimeManager.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Update()
{
	Super::Update();
	
	float deltaTime = GET_SINGLE(SeverTimeManager)->GetDeltaTime();
	if(deltaTime > 0.1) return;
	if(bRespawn) {
		currBlinkTime += deltaTime;
		if (currBlinkTime > blinkTime) {
			currBlinkTime = 0;
			blinkCurrCount++;
			bTransparent = (bTransparent == true) ? false : true;
			if (blinkCurrCount > blinkCount) {
				blinkCurrCount = 0;
				bTransparent = false;
				bRespawn = false;
			}
		}
	}
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

	if (bRespawn == false && other != nullptr) {
		if (dynamic_pointer_cast<SEnemyMissile>(other->GetOwner())
			//|| dynamic_pointer_cast<Enemy>(other->GetOwner())
			) { 
			other->GetOwner()->RemoveComponent(other);
			GET_SINGLE(SCollisionManager)->RemoveCollider(other);
			GRoom->RemoveObject(other->GetOwner()->GetObjectID());

			_pos = GRoom->GetRespawnStartPos();
			SetPos(_pos);
			Damaged();
			bRespawn = true;
		}
	}
}
