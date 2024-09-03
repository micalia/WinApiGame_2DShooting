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
	
	/*Vec2 P0 = GetPos();
	Vec2 vt = dir * speed * deltaTime;
	Vec2 P = P0 + vt;
	SetPos(P);*/

}

void EnemyMissile::Render(HDC hdc)
{
	Super::Render(hdc);
}