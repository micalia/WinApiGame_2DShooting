#include "pch.h"
#include "SMissile.h"
#include "SeverTimeManager.h"
#include "GameRoom.h"

SMissile::SMissile()
{

}

SMissile::~SMissile()
{

}

void SMissile::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(SeverTimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f) return;

	Move(deltaTime);
	currReplicateDelay += deltaTime;
	if (currReplicateDelay > replicateDelay) {
		currReplicateDelay = 0;
		MissileBroadcastMove();
	}
}

void SMissile::Move(float deltaTime)
{
	Vector P0 = Vector(info.posx(), info.posy());
	Vector vt = Vector(0, -1) * speed * deltaTime;
	Vector P = P0 + vt;
	info.set_posx(P.x);
	info.set_posy(P.y);
	SetPos(P);
	//printf("Missile Pos X : %f/ Pos Y : %f \n", enemyMissileInfo.posx(), enemyMissileInfo.posy());
}

void SMissile::MissileBroadcastMove()
{
	if (room)
	{	
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_PlayerMissileMove(info);
		room->Broadcast(sendBuffer);
	}
}
