#pragma once
#include "SpriteActor.h"

enum class PlayerColor
{
	Blue,
	Red
};

class BoxCollider;

class Player : public SpriteActor
{
	using Super = SpriteActor;
public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;

private:
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

	void MoveAction();

private:
	PlayerColor Color = PlayerColor::Blue;
	bool _keyPressed = false;

	float speed = 700;
	float Horizontal = 0;
	float Vertical = 0;

	bool bCrashing;
	Vec2 CrashingPos;
};

