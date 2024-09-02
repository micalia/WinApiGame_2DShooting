#include "pch.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "HalfEnemy.h"
#include "WhiteEnemy.h"
#include "SEnemyMissile.h"
#include "SComponent.h"
#include "SCollider.h"

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

EnemyMissileRef Actor::CreateEnemyMissile(Vector spawnPos, Vector dir)
{
	EnemyMissileRef enemyMissile = make_shared<SEnemyMissile>();
	enemyMissile->info.set_objectid(s_idGenerator++);
	enemyMissile->info.set_objecttype(Protocol::OBJECT_TYPE_ENEMY_MISSILE);
	enemyMissile->info.set_posx(spawnPos.x);
	enemyMissile->info.set_posy(spawnPos.y);
	enemyMissile->info.set_dirx(dir.x);
	enemyMissile->info.set_diry(dir.y);

	enemyMissile->enemyMissileInfo.set_posx(spawnPos.x);
	enemyMissile->enemyMissileInfo.set_posy(spawnPos.y);

	return enemyMissile;
}

void Actor::OnComponentBeginOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other)
{

}

void Actor::OnComponentEndOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other)
{

}

void Actor::AddComponent(shared_ptr<SComponent> component)
{
	if (component == nullptr)
		return;

	component->SetOwner(shared_from_this());
	_components.push_back(component);
}

void Actor::RemoveComponent(shared_ptr<SComponent> component)
{
	auto findIt = std::find(_components.begin(), _components.end(), component);
	if (findIt == _components.end())
		return;

	_components.erase(findIt);
}

shared_ptr<SCollider> Actor::GetCollider()
{
	for (shared_ptr<SComponent> component : _components)
	{
		if (auto actorCollider = dynamic_pointer_cast<SCollider>(component))
		{
			return actorCollider;
		}
	}

	return nullptr;
}