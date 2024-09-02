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
	EnemyMissile* GetMissileObj(int64 id){ return enemyMissileHashMap.find(id)->second; }

private:
	// 삽입 삭제 탐색이 빈번하게 일어나기 때문에 시간 복잡도가 O(1) HashTable자료구조를 사용함
	unordered_map<int64, EnemyMissile*> enemyMissileHashMap;

	Player* target = nullptr;

	float currSpawnDelayTime = 0;
	float SpawnDelayTime = 4;
};

