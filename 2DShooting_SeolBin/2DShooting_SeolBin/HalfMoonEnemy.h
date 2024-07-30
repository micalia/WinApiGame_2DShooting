#pragma once
#include "Enemy.h"
class HalfMoonEnemy : public Enemy
{
	using Super = Enemy;
public:
	HalfMoonEnemy();
	virtual ~HalfMoonEnemy() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

private:
};

