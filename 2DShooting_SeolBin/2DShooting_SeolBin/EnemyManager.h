#pragma once
#include "Actor.h"

class Player;
class EnemyMissile;

class EnemyManager : public Actor
{
	using Super = Actor;
public:
	EnemyManager();
	virtual ~EnemyManager() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	void RandomEnemySpawn();

	void EnemyMissileSpawn(Protocol::ObjectInfo info);

	void HalfEnemySpawn(Protocol::ObjectInfo info);
	void WhiteEnemySpawn(Protocol::ObjectInfo info);

	void AddMissile(int64 id, EnemyMissile* missilePtr);
	void RemoveMissile(int64 id);
	EnemyMissile* GetMissileObj(int64 id){	
		auto findIt = enemyMissileHashMap.find(id);
		if(findIt != enemyMissileHashMap.end())
			return findIt->second;
		return nullptr;
	}

private:
	unordered_map<int64, EnemyMissile*> enemyMissileHashMap;

	Player* target = nullptr;

	float currSpawnDelayTime = 0;
	float SpawnDelayTime = 4;
};

