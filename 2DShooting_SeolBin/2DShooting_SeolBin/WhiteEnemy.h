#pragma once
#include "Enemy.h"
class WhiteEnemy : public Enemy
{
	using Super = Enemy;
public:
	WhiteEnemy();
	virtual ~WhiteEnemy() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;

	void Fire();

	void MoveLoopingBullet(
		float& x, float& y,    // ź�� ��ǥ
		float& vx, float& vy,  // ź�� �ӵ�����
		float cx, float cy,    // ȸ�� �߽��� ��ǥ
		float r,               // �ݰ�
		float theta,           // ����(����)
		float omega            // �� �� �̵��� �� ��ȭ�ϴ� ����(����)
	);

	void SetDamagedSprite();
	void SetDefaultSprite();

	virtual void Damaged() override;
private:
	float fireDelayTime = 0.1;
	float fireDelayCurrTime = 0;
	
	float theta = 0.0;
	bool bReverseFire;

private:
	bool bDamaged;
	float damagedStateTime = 0.3;
	float currDamagedStateTime = 0;

};

