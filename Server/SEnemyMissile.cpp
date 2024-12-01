#include "pch.h"
#include "SEnemyMissile.h"
#include "SeverTimeManager.h"
#include "GameRoom.h"

SEnemyMissile::SEnemyMissile()
{
	//printf("SEnemyMissile() \n");
}

SEnemyMissile::~SEnemyMissile()
{
	//printf("~SEnemyMissile() \n");

}

void SEnemyMissile::Update()
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

void SEnemyMissile::Move(float deltaTime)
{
	Vector P0 = Vector(enemyMissileInfo.posx(), enemyMissileInfo.posy());
	Vector vt = Vector(info.dirx(), info.diry()) * speed * deltaTime;
	Vector P = P0 + vt;
	enemyMissileInfo.set_objectid(info.objectid());
	enemyMissileInfo.set_posx(P.x);
	enemyMissileInfo.set_posy(P.y);
	SetPos(P);
	//printf("Missile Pos X : %f/ Pos Y : %f \n", enemyMissileInfo.posx(), enemyMissileInfo.posy());
}

void SEnemyMissile::MissileBroadcastMove()
{
	if (room)
	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_EnemyMissileMove(enemyMissileInfo);
		room->Broadcast(sendBuffer);
	}
}
