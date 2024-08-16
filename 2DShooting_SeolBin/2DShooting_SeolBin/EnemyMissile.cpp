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
	float& x, float& y,    // 탄의 좌표
	float& vx, float& vy,  // 탄의 속도벡터
	float cx, float cy,    // 회전 중심의 좌표
	float r,               // 반경
	float theta,           // 각도(라디안)
	float omega            // 한 번 이동할 때 변화하는 각도(라디안)
) {
	// 각도를 변화시키기
	theta += omega;

	// 위치를 계산하기
	x = cx + r * cos(theta);
	y = cy + r * sin(theta);

	// 탄의 속도(필요할 때만)
	vx = -r * omega * sin(theta);
	vy = r * omega * cos(theta);
}