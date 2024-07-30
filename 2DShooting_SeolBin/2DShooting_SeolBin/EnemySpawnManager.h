#pragma once
#include "Actor.h"

class Player;

class EnemySpawnManager : public Actor
{
	using Super = Actor;
public:
	EnemySpawnManager();
	virtual ~EnemySpawnManager() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

private:
	Player* target = nullptr;
};

