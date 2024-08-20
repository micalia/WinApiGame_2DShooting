#pragma once
class ServerEnemySpawnMgr
{
public:
	ServerEnemySpawnMgr();
	virtual ~ServerEnemySpawnMgr();

	void Update();

private:
	void RandomEnemySpawn();

private:
	float currSpawnDelayTime = 0;
	float SpawnDelayTime = 4;

};

