#include "pch.h"
#include "Enemy.h"
#include "GameRoom.h"
#include "SeverTimeManager.h"

Enemy::Enemy() 
{

}

Enemy::~Enemy() 
{

}

void Enemy::Update()
{
	Super::Update();
	float deltaTime = GET_SINGLE(SeverTimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f) return;

	Move(deltaTime);
	currReplicateDelay += deltaTime;
	if (currReplicateDelay > replicateDelay) {
		currReplicateDelay = 0;
		EnemyBroadcastMove();
	}
}

void Enemy::EnemyBroadcastMove()
{
	if (room)
	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_EnemyMove(enemyInfo);
		room->Broadcast(sendBuffer);
	}
}

void Enemy::SetEnemyPos(Vector pos)
{
	enemyInfo.set_posx(pos.x);
	enemyInfo.set_posy(pos.y);

	EnemyBroadcastMove();
}

void Enemy::SetEnemyInfo(EnemyRef InEnemy, Vector InSpawnPos, Protocol::EnemyType InEnemyType, float InSpeed)
{
	info.set_objectid(s_idGenerator++);
	enemyInfo.set_enemytype(InEnemyType);
	info.set_posx(InSpawnPos.x);
	info.set_posy(InSpawnPos.y);
	enemyInfo.set_posx(InSpawnPos.x);
	enemyInfo.set_posy(InSpawnPos.y);
	info.set_speed(InSpeed);
	SetPos(InSpawnPos);
	SetSpeed(InSpeed);
}

void Enemy::Move(float deltaTime)
{
	currPosY = enemyInfo.posy();
	if (info.name() == "HalfEnemy") {
		enemyInfo.set_enemytype(Protocol::ENEMY_TYPE_HALF);
		currPosY += (deltaTime * GetSpeed());
	}
	else if (info.name() == "WhiteEnemy") {
		enemyInfo.set_enemytype(Protocol::ENEMY_TYPE_WHITE);
		currPosY += (deltaTime * GetSpeed());
	}
	enemyInfo.set_posy(currPosY);
	enemyInfo.set_objectid(info.objectid());
	SetPos(Vector(enemyInfo.posx(), enemyInfo.posy()));
}
