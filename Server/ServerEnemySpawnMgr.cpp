#include "pch.h"
#include "ServerEnemySpawnMgr.h"
#include "SeverTimeManager.h"
#include "Actor.h"
#include "GameRoom.h"
#include "Enemy.h"

ServerEnemySpawnMgr::ServerEnemySpawnMgr()
{

}

ServerEnemySpawnMgr::~ServerEnemySpawnMgr()
{

}

void ServerEnemySpawnMgr::Update()
{
	float deltaTime = GET_SINGLE(SeverTimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f) return;
	currSpawnDelayTime += deltaTime;
	if (currSpawnDelayTime > SpawnDelayTime) {
		currSpawnDelayTime = 0;
		RandomEnemySpawn();
	}
}

void ServerEnemySpawnMgr::RandomEnemySpawn()
{
	int ranPosVal = ServerUtils::RandomIntegerRange(1, 5);
	Vector spawnPos = Vector(80 * ranPosVal, 80);
	
	EnemyRef enemyRef = nullptr;

	int ranEnemyVal = ServerUtils::RandomIntegerRange(0,3);
	switch (ranEnemyVal)
	{
	case 0: 
		enemyRef = Actor::CreateEnemy(Protocol::ENEMY_TYPE_WHITE, spawnPos);
		break;
	default:
		enemyRef = Actor::CreateEnemy(Protocol::ENEMY_TYPE_HALF, spawnPos);
		break;
	}
	enemyRef->info.set_objecttype(Protocol::OBJECT_TYPE_ENEMY);
		
	GRoom->AddObject(enemyRef);
	
}
