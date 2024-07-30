#pragma once
#include "FlipbookActor.h"
class ExplosionEffect : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	ExplosionEffect();
	virtual ~ExplosionEffect() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

private:
	Flipbook* flipbookExplosion = nullptr;
};

