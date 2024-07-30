#include "pch.h"
#include "HalfMoonEnemy.h"

HalfMoonEnemy::HalfMoonEnemy()
{

}

HalfMoonEnemy::~HalfMoonEnemy()
{

}

void HalfMoonEnemy::BeginPlay()
{
	Super::BeginPlay();

	speed = 50;
}

void HalfMoonEnemy::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (deltaTime > 0.1f) return;
	_pos.y += deltaTime * speed;
}

void HalfMoonEnemy::Render(HDC hdc)
{
	Super::Render(hdc);
}
