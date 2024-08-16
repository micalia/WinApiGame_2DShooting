#pragma once
#include "SpriteActor.h"

class EnemyMissile : public SpriteActor
{
	using Super = SpriteActor;
public:
	EnemyMissile();
	virtual ~EnemyMissile() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	void SetDir(Vec2 InDir) { dir = InDir; }

	void MoveLoopingBullet(
		float& x, float& y,    // 탄의 좌표
		float& vx, float& vy,  // 탄의 속도벡터
		float cx, float cy,    // 회전 중심의 좌표
		float r,               // 반경
		float theta,           // 각도(라디안)
		float omega            // 한 번 이동할 때 변화하는 각도(라디안)
	);
private:
	float speed = 200;
	Vec2 dir;
	Vec2 startPos;
};

