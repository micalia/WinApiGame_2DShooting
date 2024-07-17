#pragma once
#include "FlipbookActor.h"

enum class PlayerColor
{
	Blue,
	Pupple
};

enum class PlayerState
{
	Idle,
	Move,
	Skill
};

class Player : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickSkill();

	void SetState(PlayerState state);
	void SetDir(Dir dir);

	bool HasReachedDest();
	bool CanGo(Vec2Int cellPos);
	void SetCellPos(Vec2Int cellPos, bool teleport = false);
private:
	void SetPlayerColor(PlayerColor color);

private:
	Flipbook* BluePlayerMove[4] = {};
	Flipbook* PupplePlayerMove[4] = {};
	Flipbook* BP_DefaultAnim = nullptr;

	void UpdateAnimation();
	Vec2Int _cellPos = {};
	PlayerColor Color = PlayerColor::Blue;
	Dir _dir = DIR_UP;
	PlayerState _state = PlayerState::Idle;
	bool _keyPressed = false;
};

