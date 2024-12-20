#pragma once
#include "Enemy.h"

class Player;

class HalfMoonEnemy : public Enemy
{
	using Super = Enemy;
public:
	//HalfMoonEnemy(const Enemy& enemy);

	void Update() override;
	void FindPlayer();
	//virtual void Damaged() override;
	void Fire();
private:
	shared_ptr<Player> target = nullptr;

	float fireDelayTime = 1.5;
	float fireDelayCurrTime = 0;
};

