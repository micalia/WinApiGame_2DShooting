#include "pch.h"
#include "SEnemyMissile.h"
#include "SeverTimeManager.h"
#include "GameRoom.h"

SEnemyMissile::SEnemyMissile()
{

}

SEnemyMissile::~SEnemyMissile()
{


}

void SEnemyMissile::Update()
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

void SEnemyMissile::Move()
{
	Vector P0 = Vector(enemyMissileInfo.posx(), enemyMissileInfo.posy());
	Vector vt = Vector(info.dirx(), info.diry()) * speed * currReplicateDelay;
	Vector P = P0 + vt;
	enemyMissileInfo.set_objectid(info.objectid());
	enemyMissileInfo.set_posx(P.x);
	enemyMissileInfo.set_posy(P.y);
	SetPos(P);
	//printf("Missile Pos X : %f/ Pos Y : %f \n", enemyMissileInfo.posx(), enemyMissileInfo.posy());
	MissileBroadcastMove();
}

void SEnemyMissile::MissileBroadcastMove()
{
	if (room)
	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_EnemyMissileMove(enemyMissileInfo);
		room->Broadcast(sendBuffer);
	}
}
