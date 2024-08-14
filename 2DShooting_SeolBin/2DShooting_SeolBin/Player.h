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

#include "Enum.pb.h"
using PlayerDir = Protocol::PLAYER_DIR_TYPE;

#define PD_IDLE Protocol::PLAYER_DIR_TYPE_IDLE
#define PD_LEFT Protocol::PLAYER_DIR_TYPE_LEFT
#define PD_RIGHT Protocol::PLAYER_DIR_TYPE_RIGHT
//enum class PlayerDir
//{
//	Idle,
//	Left,
//	Right
//};

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

	void SetState(PlayerDir InDir);
protected:
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

	void MoveAction();
	void UpdateAnimation();

private:
	PlayerDir playerDir = PD_IDLE;
	PlayerDir prevPlayerDir = PD_IDLE;
	PlayerColor Color = PlayerColor::Blue;

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

