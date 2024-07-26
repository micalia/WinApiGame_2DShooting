#pragma once
#include "Actor.h"
class Wall : public Actor
{
	using Super = Actor;
public:
	Wall();
	virtual ~Wall() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;
};

