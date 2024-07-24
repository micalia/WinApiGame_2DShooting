#pragma once
#include "SpriteActor.h"

enum class PlayerColor
{
	Blue,
	Red
};

enum class PlayerState
{
	Idle,
	Move,
	Skill
};

class Player : public SpriteActor
{
	using Super = SpriteActor;
public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void MoveAction();

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
	/*Flipbook* FB_BluePlayer = nullptr;
	Flipbook* PupplePlayerMove[4] = {};*/

	void UpdateAnimation();
	Vec2Int _cellPos = {};
	PlayerColor Color = PlayerColor::Blue;
	Dir _dir = DIR_UP;
	PlayerState _state = PlayerState::Idle;
	bool _keyPressed = false;

	float speed = 600;
	float Horizontal = 0;
	float Vertical = 0;
};

