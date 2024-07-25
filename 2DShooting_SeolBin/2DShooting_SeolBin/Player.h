#pragma once
#include "SpriteActor.h"

enum class PlayerColor
{
	Blue,
	Red
};

class Player : public SpriteActor
{
	using Super = SpriteActor;
public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	void MoveAction();

private:
	PlayerColor Color = PlayerColor::Blue;
	bool _keyPressed = false;

	float speed = 600;
	float Horizontal = 0;
	float Vertical = 0;
};

