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