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

	currReplicateDelay += deltaTime;
	if (currReplicateDelay > replicateDelay) {
		Move();
		currReplicateDelay = 0;
	}
}

void SMissile::Move()
{
	Vector P0 = Vector(info.posx(), info.posy());
	Vector vt = Vector(0, -1) * speed * currReplicateDelay;
	Vector P = P0 + vt;
	info.set_posx(P.x);
	info.set_posy(P.y);
	SetPos(P);
	//printf("Missile Pos X : %f/ Pos Y : %f \n", enemyMissileInfo.posx(), enemyMissileInfo.posy());
	MissileBroadcastMove();
}

void SMissile::MissileBroadcastMove()
{
	if (room)
	{	
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_PlayerMissileMove(info);
		room->Broadcast(sendBuffer);
	}
}
