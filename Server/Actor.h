#pragma once

class Actor : public enable_shared_from_this<Actor>
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update(){};

	static PlayerRef CreatePlayer();
	static EnemyRef CreateEnemy(Protocol::EnemyType enemyType, Vector spawnPos);
	static EnemyMissileRef CreateEnemyMissile(Vector spawnPos, Vector dir);

public:
	Protocol::ObjectInfo info;
	GameRoomRef room;

protected:
	static atomic<uint64> s_idGenerator;
};

