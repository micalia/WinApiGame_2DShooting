#pragma once
#include "Enemy.h"
class WhiteEnemy : public Enemy
{
	using Super = Enemy;
public:
	virtual void Update() override;
	void Fire();

	//virtual void Damaged() override;
private:
	void MoveLoopingBullet(
		float& x, float& y,    // 탄의 좌표
		float& vx, float& vy,  // 탄의 속도벡터
		float cx, float cy,    // 회전 중심의 좌표
		float r,               // 반경
		float theta,           // 각도(라디안)
		float omega            // 한 번 이동할 때 변화하는 각도(라디안)
	);

private:
	float fireDelayTime = 0.5;//0.1;
	float fireDelayCurrTime = 0;//0;

	float theta = 0.0;
	bool bReverseFire;

	
};

