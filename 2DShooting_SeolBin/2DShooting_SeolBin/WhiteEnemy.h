#pragma once
#include "Enemy.h"
class WhiteEnemy : public Enemy
{
	using Super = Enemy;
public:
	WhiteEnemy();
	virtual ~WhiteEnemy() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;

	void Fire();

	void MoveLoopingBullet(
		float& x, float& y,    // 탄의 좌표
		float& vx, float& vy,  // 탄의 속도벡터
		float cx, float cy,    // 회전 중심의 좌표
		float r,               // 반경
		float theta,           // 각도(라디안)
		float omega            // 한 번 이동할 때 변화하는 각도(라디안)
	);

	void SetDamagedSprite();
	void SetDefaultSprite();

	virtual void Damaged() override;
private:
	float fireDelayTime = 0.1;
	float fireDelayCurrTime = 0;
	
	float theta = 0.0;
	bool bReverseFire;

private:
	bool bDamaged;
	float damagedStateTime = 0.3;
	float currDamagedStateTime = 0;

};

