#include "pch.h"
#include "EnemySpawnManager.h"
#include "Sprite.h"
#include "HalfMoonEnemy.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"
#include "WhiteEnemy.h"

EnemySpawnManager::EnemySpawnManager()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"HalfMoonEnemy", L"Sprite\\Enemy\\HalfMoonEnemy.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"HalfMoonEnemy", GET_SINGLE(ResourceManager)->GetTexture(L"HalfMoonEnemy"));

	GET_SINGLE(ResourceManager)->LoadTexture(L"WhiteEnemy", L"Sprite\\Enemy\\WhiteEnemy.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"WhiteEnemy", GET_SINGLE(ResourceManager)->GetTexture(L"WhiteEnemy"));
}

EnemySpawnManager::~EnemySpawnManager()
{

}

void EnemySpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	auto& ActorArr = GET_SINGLE(SceneManager)->GetCurrentScene()->_actors[LAYER_Player];

	for (Actor* actor : ActorArr) {
		if (target = dynamic_cast<Player*>(actor)) break;
	}

	//{
	//	Sprite* HalfMoonEnemySprite = GET_SINGLE(ResourceManager)->GetSprite(L"HalfMoonEnemy");

	//	HalfMoonEnemy* halfMoonEnemy = new HalfMoonEnemy();
	//	halfMoonEnemy->SetSprite(HalfMoonEnemySprite);
	//	halfMoonEnemy->SetLayer(LAYER_Enemy);
	//	const Vec2Int size = HalfMoonEnemySprite->GetSize();
	//	halfMoonEnemy->SetPos(Vec2(242, 80));
	//	halfMoonEnemy->SetTarget(target);

	//	{
	//		BoxCollider* collider = new BoxCollider();
	//		collider->SetShowDebug(true);
	//		//나의 콜리전 레이어
	//		collider->SetCollisionLayer(CLT_ENEMY);

	//		// 모든 콜리전 플래그 제거
	//		collider->ResetCollisionFlag();
	//		// 내가 충돌하고 싶은 레이어 추가
	//		collider->AddCollisionFlagLayer(CLT_WALL);
	//		collider->AddCollisionFlagLayer(CLT_MISSILE);
	//		collider->AddCollisionFlagLayer(CLT_PLAYER);
	//		collider->SetSize(Vec2(size.x, size.y));
	//		GET_SINGLE(CollisionManager)->AddCollider(collider);
	//		halfMoonEnemy->AddComponent(collider);
	//	} 
	//	GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(halfMoonEnemy);
	//}
	{
		Sprite* whiteEnemySprite = GET_SINGLE(ResourceManager)->GetSprite(L"WhiteEnemy");

		WhiteEnemy* whiteEnemy = new WhiteEnemy();
		whiteEnemy->SetSprite(whiteEnemySprite);
		whiteEnemy->SetLayer(LAYER_Enemy);
		const Vec2Int size = whiteEnemySprite->GetSize();
		whiteEnemy->SetPos(Vec2(242, 380));
		whiteEnemy->SetTarget(target);

		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			//나의 콜리전 레이어
			collider->SetCollisionLayer(CLT_ENEMY);

			// 모든 콜리전 플래그 제거
			collider->ResetCollisionFlag();
			// 내가 충돌하고 싶은 레이어 추가
			collider->AddCollisionFlagLayer(CLT_WALL);
			collider->AddCollisionFlagLayer(CLT_MISSILE);
			collider->AddCollisionFlagLayer(CLT_PLAYER);
			collider->SetSize(Vec2(size.x, size.y));
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			whiteEnemy->AddComponent(collider);
		} 
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(whiteEnemy);
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
