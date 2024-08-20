#pragma once
#include "Scene.h"

class Actor;
class GameObject;
class UI;
class EnemySpawnManager;

class DevScene : public Scene
{
	using Super = Scene;
public:
	DevScene();
	virtual ~DevScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	bool CanGo(Vec2Int cellPos);
	Vec2 ConvertPos(Vec2Int cellPos);

	class TilemapActor* _tilemapActor = nullptr;

	Vec2 GetRespawnEndPos() { return respawnEndPos; }
	Vec2 GetRespawnStartPos() { return respawnStartPos; }

	EnemySpawnManager* GetEnemySpawnMgr(){return EnemySpawnMgr;}
private:
	Vec2 respawnEndPos = Vec2(242, 540);
	Vec2 respawnStartPos = Vec2(242, 1088);
	EnemySpawnManager* EnemySpawnMgr = nullptr;
};

