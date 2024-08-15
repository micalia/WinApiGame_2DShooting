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

EnemyRef Actor::CreateEnemy()
{
	EnemyRef enemy = make_shared<Enemy>();
	enemy->info.set_objectid(s_idGenerator++);
	enemy->info.set_objecttype(Protocol::OBJECT_TYPE_ENEMY);

	return enemy;
}
