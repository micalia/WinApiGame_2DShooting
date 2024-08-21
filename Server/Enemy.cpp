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
	float deltaTime = GET_SINGLE(SeverTimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f) return;

	currReplicateDelay += deltaTime;
	if (currReplicateDelay > replicateDelay) {
		if (info.objectid() == 2) {
			printf("enemyID : %d / posX : %f / posY : %f \n", enemyInfo.objectid(), enemyInfo.posx(), enemyInfo.posy());

		}
		float currPosY = enemyInfo.posy();
		if (info.name() == "HalfEnemy") {
			enemyInfo.set_enemytype(Protocol::ENEMY_TYPE_HALF);
			currPosY += (currReplicateDelay * GetSpeed());
		}
		else if (info.name() == "WhiteEnemy") {
			enemyInfo.set_enemytype(Protocol::ENEMY_TYPE_WHITE);
			currPosY += (currReplicateDelay * GetSpeed());
		}
		enemyInfo.set_posy(currPosY);
		enemyInfo.set_objectid(info.objectid());
		EnemyBroadcastMove();
		currReplicateDelay = 0;
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
