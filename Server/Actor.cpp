#include "pch.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "HalfEnemy.h"
#include "WhiteEnemy.h"

atomic<uint64> Actor::s_idGenerator = 1;

Actor::Actor()
{

}

Actor::~Actor()
{

}

PlayerRef Actor::CreatePlayer()
{
	PlayerRef player = make_shared<Player>();
	player->info.set_objectid(s_idGenerator++);
	player->info.set_objecttype(Protocol::OBJECT_TYPE_PLAYER);

	return player;
}

EnemyRef Actor::CreateEnemy(Protocol::EnemyType enemyType, Vector spawnPos)
{
	switch (enemyType)
	{
	case Protocol::ENEMY_TYPE_HALF: 
	{
		HalfEnemyRef halfEnemy = make_shared<HalfEnemy>();
		float speed = 50;
		halfEnemy->SetEnemyInfo(halfEnemy, spawnPos, enemyType, speed);
		halfEnemy->info.set_name("HalfEnemy");
		return halfEnemy;
	}
		break;
	case Protocol::ENEMY_TYPE_WHITE:
	{
		WhiteEnemyRef whiteEnemy = make_shared<WhiteEnemy>();
		float speed = 50;
		whiteEnemy->SetEnemyInfo(whiteEnemy, spawnPos, enemyType, speed);
		whiteEnemy->info.set_name("WhiteEnemy");
		return whiteEnemy;
	}
		break;
	default:
		break;
	}

	return nullptr;
}
