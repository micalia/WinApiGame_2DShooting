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

enum PlayerState {
	RespawnScene,
	RespawnSceneComplete,
};

class ObjectInfo;
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

	virtual void SetState(PlayerDir InDir) override;

	string GetName(){ return _name; }
	void SetName(string name){ _name = name; }

	void Fire(Protocol::ObjectInfo InInfo);

	int GetHp(){return _hp;}
	void SetHp(int hp) {_hp = hp;}

	void Damaged();

	void SetPlayerState(PlayerState playerState);
	PlayerState GetPlayerState(){ return _playerState; }
protected:
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

	void MoveAction();
	void UpdateAnimation();

protected:
	float speed = 300; // Default Val : 470
	bool bCrashing = false;

	Flipbook* _blueFlipbookIdle = nullptr;

protected:
	Vec2 CrashingPos;
private:
	PlayerDir playerDir = PD_IDLE;
	PlayerDir prevPlayerDir = PD_IDLE;
	PlayerColor Color = PlayerColor::Blue;
	PlayerState _playerState = PlayerState::RespawnScene;


	Flipbook* _blueFlipbookLeft = nullptr;
	Flipbook* _blueFlipbookRight = nullptr;
	Flipbook* _blueFlipbookLeftReverse = nullptr;
	Flipbook* _blueFlipbookRightReverse = nullptr;

	Flipbook* _redFlipbookIdle = nullptr;
	Flipbook* _redFlipbookLeft = nullptr;
	Flipbook* _redFlipbookRight = nullptr;
	Flipbook* _redFlipbookLeftReverse = nullptr;
	Flipbook* _redFlipbookRightReverse = nullptr;

	Flipbook* _playerTransparent = nullptr;

	string _name = "";
protected:
	void ReverseAnimDelay(float InDeltaTime);
	bool bReverseAnimOn;
	float reverseAnimDelayTime = 0.2;
	float currReverseAnimDelayTime = 0;

private:
	int _hp = 3;

protected:
	bool bRespawn = false;
private:
	int blinkCount = 18;
	int blinkCurrCount = 0;
	float blinkTime = 0.2;
	float currBlinkTime = 0;
	bool bTransparent = false;
};

