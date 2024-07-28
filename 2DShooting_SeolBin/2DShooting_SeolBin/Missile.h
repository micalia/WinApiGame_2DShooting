#pragma once
#include "Actor.h"
#include "SpriteActor.h"
class Missile : public SpriteActor
{
	using Super = SpriteActor;
public:
	Missile();
	virtual ~Missile() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

protected:

private:
	float speed = 300;
	
};

