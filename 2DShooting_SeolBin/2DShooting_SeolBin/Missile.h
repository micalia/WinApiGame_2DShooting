#pragma once
#include "Actor.h"
#include "SpriteActor.h"
class Missile : public SpriteActor
{
	using Super = SpriteActor;
public:
	Missile();
	virtual ~Missile() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	void SetCellPos(Vec2Int cellPos, bool teleport = false);

protected:

private:
	//Flipbook* FB_BlueMissile = nullptr;
	float speed = 800;
	Vec2Int _cellPos = {};
};

