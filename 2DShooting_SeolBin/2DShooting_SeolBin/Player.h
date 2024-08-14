#pragma once
#include "FlipbookActor.h"

enum class PlayerColor
{
	Blue,
	Red
};

enum PlayerAnimState {
	PA_Left,
	PA_LeftReady,
	PA_Idle,
	PA_RightReady,
	PA_Right
};

enum class PlayerDir
{
	Idle,
	Left,
	Right
};

class BoxCollider;
class Flipbook;

class Player : public FlipbookActor
{
	using Super = FlipbookActor;
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
	void UpdateAnimation();

	void SetState(PlayerDir InDir);
private:
	PlayerDir playerDir = PlayerDir::Idle;
	PlayerDir prevPlayerDir = PlayerDir::Idle;
	PlayerColor Color = PlayerColor::Blue;
	bool _keyPressed = false;

	float speed = 300; // Default Val : 470
	float Horizontal = 0;
	float Vertical = 0;

	bool bCrashing;
	Vec2 CrashingPos;

	Flipbook* _flipbookIdle = nullptr;
	Flipbook* _flipbookLeft = nullptr;
	Flipbook* _flipbookRight = nullptr;
	Flipbook* _flipbookLeftReverse = nullptr;
	Flipbook* _flipbookRightReverse = nullptr;

private:
	void ReverseAnimDelay(float InDeltaTime);
	bool bReverseAnimOn;
	float reverseAnimDelayTime = 0.2;
	float currReverseAnimDelayTime = 0;
};

