#pragma once
#include "Actor.h"
class TestLerpActor : public Actor
{
	using Super = Actor;
public:
	TestLerpActor();
	virtual ~TestLerpActor();

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render(HDC hdc);

	Vec2 startPos = Vec2(250, 150);
	Vec2 endPos = Vec2(250, 650);

	float moveTime = 5;
	float currMoveTime = 0;
};

