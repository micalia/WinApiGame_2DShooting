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

	void Fire();
private:
	shared_ptr<Player> target = nullptr;

	float fireDelayTime = 1;
	float fireDelayCurrTime = 0;
};

