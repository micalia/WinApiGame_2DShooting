#include "pch.h"
#include "EnemySpawnManager.h"
#include "Sprite.h"
#include "HalfMoonEnemy.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"

EnemySpawnManager::EnemySpawnManager()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"HalfMoonEnemy", L"Sprite\\Enemy\\HalfMoonEnemy.bmp", RGB(255, 255, 255));

	GET_SINGLE(ResourceManager)->CreateSprite(L"HalfMoonEnemy", GET_SINGLE(ResourceManager)->GetTexture(L"HalfMoonEnemy"));
}

EnemySpawnManager::~EnemySpawnManager()
{

}

void EnemySpawnManager::BeginPlay()
{
	Super::BeginPlay();

	{
		Sprite* HalfMoonEnemySprite = GET_SINGLE(ResourceManager)->GetSprite(L"HalfMoonEnemy");

		HalfMoonEnemy* halfMoonEnemy = new HalfMoonEnemy();
		halfMoonEnemy->SetSprite(HalfMoonEnemySprite);
		halfMoonEnemy->SetLayer(LAYER_Enemy);
		const Vec2Int size = HalfMoonEnemySprite->GetSize();
		halfMoonEnemy->SetPos(Vec2(242, 188));
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			//나의 콜리전 레이어
			collider->SetCollisionLayer(CLT_PLAYER);

			// 모든 콜리전 플래그 제거
			collider->ResetCollisionFlag();
			// 내가 충돌하고 싶은 레이어 추가
			collider->AddCollisionFlagLayer(CLT_WALL);
			collider->SetSize(Vec2(size.x, size.y));
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			halfMoonEnemy->AddComponent(collider);
		} 
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(halfMoonEnemy);
	}
}

void EnemySpawnManager::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void EnemySpawnManager::Render(HDC hdc)
{
	Super::Render(hdc);
	Utils::DrawCircle(hdc, _pos, 10);
}
