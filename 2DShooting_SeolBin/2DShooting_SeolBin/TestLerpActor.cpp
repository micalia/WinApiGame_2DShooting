#include "pch.h"
#include "TestLerpActor.h"

TestLerpActor::TestLerpActor()
{

}

TestLerpActor::~TestLerpActor()
{

}

void TestLerpActor::BeginPlay()
{

}

void TestLerpActor::Tick(float deltaTime)
{
	currMoveTime+= deltaTime;
	if (currMoveTime > moveTime) {
		currMoveTime = 0;
	}
	else {
		float alpha = currMoveTime / moveTime;
		SetPos(Vec2(GetPos().x, lerp(startPos.y, endPos.y, alpha)));
	}
}

void TestLerpActor::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 15);
}
