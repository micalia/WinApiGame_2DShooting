#include "pch.h"
#include "EnemyMissile.h"

EnemyMissile::EnemyMissile()
{

}

EnemyMissile::~EnemyMissile()
{

}

void EnemyMissile::BeginPlay()
{
	Super::BeginPlay();

	startPos = GetPos();
}

void EnemyMissile::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	Vec2 P0 = GetPos();
	Vec2 vt = dir * speed * deltaTime;
	Vec2 P = P0 + vt;
	SetPos(P);

	/*Vec2 P0 = GetPos();
	Vec2 P = P0;
	dir.x = 1;
	dir.y = 0;
	MoveLoopingBullet(P.x, P.y, dir.x, dir.y, startPos.x, startPos.y, 2, 45, 45);
	SetPos(P);*/
}

void EnemyMissile::Render(HDC hdc)
{
	Super::Render(hdc);
}

void EnemyMissile::MoveLoopingBullet(
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