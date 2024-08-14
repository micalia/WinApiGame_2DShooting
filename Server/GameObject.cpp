#include "pch.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

atomic<uint64> GameObject::s_idGenerator = 1;

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

PlayerRef GameObject::CreatePlayer()
{
	PlayerRef player = make_shared<Player>();
	player->info.set_objectid(s_idGenerator++);
	player->info.set_objecttype(Protocol::OBJECT_TYPE_PLAYER);

	return player;
}

EnemyRef GameObject::CreateEnemy()
{
	EnemyRef enemy = make_shared<Enemy>();
	enemy->info.set_objectid(s_idGenerator++);
	enemy->info.set_objecttype(Protocol::OBJECT_TYPE_ENEMY);

	return enemy;
}
