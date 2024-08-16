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
		float& x, float& y,    // ź�� ��ǥ
		float& vx, float& vy,  // ź�� �ӵ�����
		float cx, float cy,    // ȸ�� �߽��� ��ǥ
		float r,               // �ݰ�
		float theta,           // ����(����)
		float omega            // �� �� �̵��� �� ��ȭ�ϴ� ����(����)
	);
private:
	float speed = 200;
	Vec2 dir;
	Vec2 startPos;
};

