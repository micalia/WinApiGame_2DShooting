#include "pch.h"
#include "HalfMoonEnemy.h"
#include "EnemyMissile.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Sprite.h"
#include "Player.h"

HalfMoonEnemy::HalfMoonEnemy()
{

}

HalfMoonEnemy::~HalfMoonEnemy()
{

}

void HalfMoonEnemy::BeginPlay()
{
	Super::BeginPlay();

	speed = 50;
}

void HalfMoonEnemy::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	fireDelayCurrTime += deltaTime;
	if (fireDelayCurrTime > fireDelayTime) {
		fireDelayCurrTime = 0;
		FindPlayer();
		Fire();
	}

	if (deltaTime > 0.1f) return;
	_pos.y += deltaTime * speed;
	SetPos(_pos);
}

void HalfMoonEnemy::Render(HDC hdc)
{
	Super::Render(hdc);
}

void HalfMoonEnemy::Fire()
{
	if (target == nullptr) return;
	
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
