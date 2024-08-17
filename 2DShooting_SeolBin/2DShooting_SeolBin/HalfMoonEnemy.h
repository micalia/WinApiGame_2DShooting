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

	void Fire();

	void SetDamagedSprite();
	void SetDefaultSprite();

	virtual void Damaged() override;
private:
	float fireDelayTime = 2.5;
	float fireDelayCurrTime = 0;

private:
	bool bDamaged;
	float damagedStateTime = 0.3;
	float currDamagedStateTime = 0;

};

