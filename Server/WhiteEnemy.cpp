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
	float _vx = 0;       // �̻����� x �ӵ�
	float _vy = 0;       // �̻����� y �ӵ�
	float _cx = 0;		 // ȸ�� �߽� x ��ǥ
	float _cy = 0;		// ȸ�� �߽� y ��ǥ
	float _r = 1.0f;       // �ݰ�
	float _omega = 1.0f;		// ���� ��ȭ��

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
	float& x, float& y,    // ź�� ��ǥ
	float& vx, float& vy,  // ź�� �ӵ�����
	float cx, float cy,    // ȸ�� �߽��� ��ǥ
	float r,               // �ݰ�
	float theta,           // ����(����)
	float omega            // �� �� �̵��� �� ��ȭ�ϴ� ����(����)
) 
{
	// ������ ��ȭ��Ű��
	theta += omega;

	// ��ġ�� ����ϱ�
	x = cx + r * cos(theta);
	y = cy + r * sin(theta);

	// ź�� �ӵ�(�ʿ��� ����)
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
