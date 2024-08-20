#include "pch.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"

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
	EnemyRef enemy = make_shared<Enemy>();
	enemy->info.set_objectid(s_idGenerator++);
	printf("Monster s_idGenerator :  %llu \n", s_idGenerator.load());
	enemy->enemyInfo.set_enemytype(enemyType);
	switch (enemyType)
	{
	case Protocol::ENEMY_TYPE_HALF:
		enemy->info.set_name("HalfEnemy");
		break;
	case Protocol::ENEMY_TYPE_WHITE:
		enemy->info.set_name("WhiteEnemy");
		break;
	default:
		enemy->info.set_name("Enemy Name NONE");
		break;
	}
	enemy->info.set_posx(spawnPos.x);
	enemy->info.set_posy(spawnPos.y);

	return enemy;
}
