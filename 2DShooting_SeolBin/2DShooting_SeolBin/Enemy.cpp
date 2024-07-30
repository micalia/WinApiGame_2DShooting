#include "pch.h"
#include "Enemy.h"
#include "Player.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "EnemyMissile.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Scene.h"

Enemy::Enemy()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"EnemyMissile", L"Sprite\\Projectile\\EnemyBullet.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"EnemyMissile", GET_SINGLE(ResourceManager)->GetTexture(L"EnemyMissile"));
}

Enemy::~Enemy()
{

}

void Enemy::BeginPlay()
{
	Super::BeginPlay();
}

void Enemy::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (target != nullptr) {
		fireDelayCurrTime += deltaTime;
		if (fireDelayCurrTime > fireDelayTime) {
			fireDelayCurrTime = 0;

			Fire();
		}
	}
}

void Enemy::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Enemy::Fire()
{ 
	Vec2 dir = target->GetPos() - GetPos();
	dir.Normalize();

	{
		Sprite* EnemyMissileSprite = GET_SINGLE(ResourceManager)->GetSprite(L"EnemyMissile");

		EnemyMissile* enemyMissile = new EnemyMissile();
		enemyMissile->SetPos(_pos);
		enemyMissile->SetSprite(EnemyMissileSprite);
		enemyMissile->SetLayer(LAYER_BULLET);
		enemyMissile->SetDir(dir);
		Vec2Int SpriteSize = EnemyMissileSprite->GetSize();
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			collider->SetSize(Vec2(SpriteSize.x, SpriteSize.y));
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			enemyMissile->AddComponent(collider);
		} 
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(enemyMissile);
	}
}
