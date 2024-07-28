#pragma once
#include "SpriteActor.h"
class Enemy : public SpriteActor
{
	using Super = SpriteActor;
public:
	Enemy();
	virtual ~Enemy() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	void SetHp(int32 _hp) { _hp = hp; }
	int32 GetHp() { return hp; }
private:
	int32 hp = 100;
	float speed = 300;
};

