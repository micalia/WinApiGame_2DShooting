#pragma once
#include "Actor.h"
#include "FlipbookActor.h"
class Missile : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Missile();
	virtual ~Missile() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetCellPos(Vec2Int cellPos, bool teleport = false);

protected:

private:
	Flipbook* FB_BlueMissile = nullptr;
	float speed = 800;
	Vec2Int _cellPos = {};
};

