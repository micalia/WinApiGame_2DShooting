#pragma once
#include "Player.h"
class MyPlayer : public Player
{
	using Super = Player;
public:
	MyPlayer();
	virtual ~MyPlayer() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

private:
	void TickInput();
	void MoveAction();

private:
	float speed = 300; // Default Val : 470
	float Horizontal = 0;
	float Vertical = 0;
};

