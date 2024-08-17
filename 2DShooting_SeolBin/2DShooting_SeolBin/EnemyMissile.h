#pragma once
#include "SpriteActor.h"

class EnemyMissile : public SpriteActor
{
	using Super = SpriteActor;
public:
	EnemyMissile();
	virtual ~EnemyMissile() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	void SetDir(Vec2 InDir) { dir = InDir; }

private:
	float speed = 200;
	Vec2 dir;
	Vec2 startPos;
};

