#pragma once
#include "Enemy.h"
class WhiteEnemy : public Enemy
{
	using Super = Enemy;
public:
	virtual void Update() override;
	void Fire();
private:
	void MoveLoopingBullet(
		float& x, float& y,    // ź�� ��ǥ
		float& vx, float& vy,  // ź�� �ӵ�����
		float cx, float cy,    // ȸ�� �߽��� ��ǥ
		float r,               // �ݰ�
		float theta,           // ����(����)
		float omega            // �� �� �̵��� �� ��ȭ�ϴ� ����(����)
	);

private:
	float fireDelayTime = 600;//0.1;
	float fireDelayCurrTime = 599;//0;

	float theta = 0.0;
	bool bReverseFire;

	
};

