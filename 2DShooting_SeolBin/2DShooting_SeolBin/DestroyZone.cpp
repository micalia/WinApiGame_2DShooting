#include "pch.h"
#include "DestroyZone.h"

DestroyZone::DestroyZone()
{

}

DestroyZone::~DestroyZone()
{

}

void DestroyZone::BeginPlay()
{
	Super::BeginPlay();
}

void DestroyZone::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void DestroyZone::Render(HDC hdc)
{
	Super::Render(hdc);
	Utils::DrawRect(hdc, _pos, 5, 5);
}
