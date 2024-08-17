#include "pch.h"
#include "WhiteEnemy.h"
#include "ResourceManager.h"
#include "EnemyMissile.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"

WhiteEnemy::WhiteEnemy()
{

}

WhiteEnemy::~WhiteEnemy()
{

}

void WhiteEnemy::BeginPlay()
{
	Super::BeginPlay();

	speed = 50;
	hp = 5;
}

void WhiteEnemy::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	if (deltaTime > 0.1f) return;
	_pos.y += deltaTime * speed;
	SetPos(_pos);

	fireDelayCurrTime += deltaTime;
	if (fireDelayCurrTime > fireDelayTime) {
		fireDelayCurrTime = 0;
		Fire();
	}

	if (bDamaged) {
		currDamagedStateTime += deltaTime;
		if (currDamagedStateTime > damagedStateTime) {
			currDamagedStateTime = 0;
			bDamaged = false;
			SetDefaultSprite();
		}
	}
}

void WhiteEnemy::Render(HDC hdc)
{
	Super::Render(hdc);
}

void WhiteEnemy::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	Super::OnComponentBeginOverlap(collider, other);
}

void WhiteEnemy::Fire()
{
	float x = 0;
	float y = 0;
	float vx = 0;       // �̻����� x �ӵ�
	float vy = 0;       // �̻����� y �ӵ�
	float cx = 0;		 // ȸ�� �߽� x ��ǥ
	float cy = 0;		// ȸ�� �߽� y ��ǥ
	float r = 1.0f;       // �ݰ�
	float omega = 1.0f;		// ���� ��ȭ��
	MoveLoopingBullet(x, y, vx, vy, cx, cy, r, theta, omega);

	if (bReverseFire) {
		theta -=0.5;			
		if (theta < -2.5) {
			bReverseFire = false;
		}
	}
	else {
		theta +=0.5;			
		if (theta > 3.78) {
			bReverseFire = true;
		}
	}

	Vec2 dir = Vec2(x,y);
	{
		Sprite* EnemyMissileSprite = GET_SINGLE(ResourceManager)->GetSprite(L"EnemyMissile");

		EnemyMissile* enemyMissile = new EnemyMissile();
		enemyMissile->SetPos(_pos);
		enemyMissile->SetSprite(EnemyMissileSprite);
		enemyMissile->SetLayer(LAYER_BULLET);
		enemyMissile->SetDir(dir); 
		Vec2Int SpriteSize = EnemyMissileSprite->GetSize();
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			collider->SetSize(Vec2(SpriteSize.x, SpriteSize.y));
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			enemyMissile->AddComponent(collider);
		} 
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(enemyMissile);
	}
}

void WhiteEnemy::MoveLoopingBullet(
	float& x, float& y,    // ź�� ��ǥ
	float& vx, float& vy,  // ź�� �ӵ�����
	float cx, float cy,    // ȸ�� �߽��� ��ǥ
	float r,               // �ݰ�
	float theta,           // ����(����)
	float omega            // �� �� �̵��� �� ��ȭ�ϴ� ����(����)
) {
	// ������ ��ȭ��Ű��
	theta += omega;

	// ��ġ�� ����ϱ�
	x = cx + r * cos(theta);
	y = cy + r * sin(theta);

	// ź�� �ӵ�(�ʿ��� ����)
	vx = -r * omega * sin(theta);
	vy = r * omega * cos(theta);
}

void WhiteEnemy::SetDamagedSprite()
{
	Sprite* damagedSprite = GET_SINGLE(ResourceManager)->GetSprite(L"WhiteEnemyDamaged");
	SetSprite(damagedSprite);
}

void WhiteEnemy::SetDefaultSprite()
{
	Sprite* defaultSprite = GET_SINGLE(ResourceManager)->GetSprite(L"WhiteEnemy");
	SetSprite(defaultSprite);
}

void WhiteEnemy::Damaged()
{
 	hp--; 
	bDamaged = true;
	SetDamagedSprite();
}
