#include "pch.h"
#include "WhiteEnemy.h"
#include "SeverTimeManager.h"
#include "GameRoom.h"
#include "Actor.h"
#include "SEnemyMissile.h"
#include "SBoxCollider.h"
#include "SCollisionManager.h"

void WhiteEnemy::Update()
{
	Super::Update();

	float deltaTime =  GET_SINGLE(SeverTimeManager)->GetDeltaTime();
	fireDelayCurrTime += deltaTime;
	if (fireDelayCurrTime > fireDelayTime) {
		fireDelayCurrTime = 0;
		Fire();
	}
}

void WhiteEnemy::Fire()
{
	float _x = 0;
	float _y = 0;
	float _vx = 0;       // 미사일의 x 속도
	float _vy = 0;       // 미사일의 y 속도
	float _cx = 0;		 // 회전 중심 x 좌표
	float _cy = 0;		// 회전 중심 y 좌표
	float _r = 1.0f;       // 반경
	float _omega = 1.0f;		// 각도 변화량

	MoveLoopingBullet(_x, _y, _vx, _vy, _cx, _cy, _r, theta, _omega);

	if (bReverseFire) {
		theta -= 0.5;
		if (theta < -2.5) {
			bReverseFire = false;
		}
	}
	else {
		theta += 0.5;
		if (theta > 3.78) {
			bReverseFire = true;
		}
	}

	Vector spawnPos = Vector(enemyInfo.posx(), enemyInfo.posy());
	Vector missileDir = Vector(_x, _y);

	EnemyMissileRef missileRef = Actor::CreateEnemyMissile(spawnPos, missileDir);
	{
		shared_ptr<SBoxCollider> collider = make_shared<SBoxCollider>();
		collider->SetSize(Vector(17, 17)); //Enemy Missile Sprite Pixel Size
		GET_SINGLE(SCollisionManager)->AddCollider(collider);
		missileRef->AddComponent(collider);
	}
	GRoom->AddObject(missileRef);
}

void WhiteEnemy::MoveLoopingBullet(
	float& x, float& y,    // 탄의 좌표
	float& vx, float& vy,  // 탄의 속도벡터
	float cx, float cy,    // 회전 중심의 좌표
	float r,               // 반경
	float theta,           // 각도(라디안)
	float omega            // 한 번 이동할 때 변화하는 각도(라디안)
) 
{
	// 각도를 변화시키기
	theta += omega;

	// 위치를 계산하기
	x = cx + r * cos(theta);
	y = cy + r * sin(theta);

	// 탄의 속도(필요할 때만)
	vx = -r * omega * sin(theta);
	vy = r * omega * cos(theta);
}

//void WhiteEnemy::Damaged()
//{
//	int currHp = GetHp();
//	SetHp(--currHp);
//
//	Super::Damaged();
//	/*bDamaged = true;
//	SetDamagedSprite();*/
//}
