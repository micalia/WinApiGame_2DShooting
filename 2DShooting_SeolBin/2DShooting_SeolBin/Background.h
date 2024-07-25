#pragma once
#include "SpriteActor.h"
class Background : public SpriteActor
{
	using Super = SpriteActor;
public:
	Background();
	virtual ~Background() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

private:
	float speed = 60;
	float SpriteHeight;
	float SpriteWidth;
};

