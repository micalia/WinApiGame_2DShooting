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
	GET_SINGLE(ResourceManager)->LoadTexture(L"HalfMoonEnemyDamaged", L"Sprite\\Enemy\\HalfMoonEnemyDamaged.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"HalfMoonEnemyDamaged", GET_SINGLE(ResourceManager)->GetTexture(L"HalfMoonEnemyDamaged"));

	GET_SINGLE(ResourceManager)->LoadTexture(L"WhiteEnemy", L"Sprite\\Enemy\\WhiteEnemy.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"WhiteEnemy", GET_SINGLE(ResourceManager)->GetTexture(L"WhiteEnemy"));
	GET_SINGLE(ResourceManager)->LoadTexture(L"WhiteEnemyDamaged", L"Sprite\\Enemy\\WhiteEnemyDamaged.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"WhiteEnemyDamaged", GET_SINGLE(ResourceManager)->GetTexture(L"WhiteEnemyDamaged"));
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
	currSpawnDelayTime = SpawnDelayTime;
	//{
	//	Sprite* whiteEnemySprite = GET_SINGLE(ResourceManager)->GetSprite(L"WhiteEnemy");
	//	WhiteEnemy* whiteEnemy = GET_SINGLE(SceneManager)->GetCurrentScene()->SpawnActor<WhiteEnemy>(Vec2(80 * 1, 80), LAYER_Enemy);
	//	whiteEnemy->SetSprite(whiteEnemySprite);
	//	const Vec2Int size = whiteEnemySprite->GetSize();
	//	whiteEnemy->SetTarget(target);
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
	//		whiteEnemy->AddComponent(collider);
	//	}
	//}

	//{
	//	Sprite* HalfMoonEnemySprite = GET_SINGLE(ResourceManager)->GetSprite(L"HalfMoonEnemy");
	//	HalfMoonEnemy* halfMoonEnemy = GET_SINGLE(SceneManager)->GetCurrentScene()->SpawnActor<HalfMoonEnemy>(Vec2(80 * 3, 80), LAYER_Enemy);
	//	halfMoonEnemy->SetSprite(HalfMoonEnemySprite);
	//	const Vec2Int size = HalfMoonEnemySprite->GetSize();
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
	//
	//}

	
}

void EnemySpawnManager::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	currSpawnDelayTime += deltaTime;
	if (currSpawnDelayTime > SpawnDelayTime) {
		currSpawnDelayTime = 0;
		RandomEnemySpawn();
	}
}

void EnemySpawnManager::Render(HDC hdc)
{
	Super::Render(hdc);
	Utils::DrawCircle(hdc, _pos, 10);
}

void EnemySpawnManager::RandomEnemySpawn()
{	//  Y축 80일때 삭제 안됨
	int ranPosVal = Utils::RandomIntegerRange(1, 5);
	int ranEnemyVal = 1;
	//int ranEnemyVal = Utils::RandomIntegerRange(0,3);
	switch (ranEnemyVal)
	{
	case 0:
	{
		Sprite* whiteEnemySprite = GET_SINGLE(ResourceManager)->GetSprite(L"WhiteEnemy");
		WhiteEnemy* whiteEnemy = GET_SINGLE(SceneManager)->GetCurrentScene()->SpawnActor<WhiteEnemy>(Vec2(80 * ranPosVal, 80), LAYER_Enemy);
		whiteEnemy->SetSprite(whiteEnemySprite);
		const Vec2Int size = whiteEnemySprite->GetSize();
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
	}
		break;
	default:
	{
		Sprite* HalfMoonEnemySprite = GET_SINGLE(ResourceManager)->GetSprite(L"HalfMoonEnemy");
		HalfMoonEnemy* halfMoonEnemy = GET_SINGLE(SceneManager)->GetCurrentScene()->SpawnActor<HalfMoonEnemy>(Vec2(80 * ranPosVal, 80), LAYER_Enemy);
		halfMoonEnemy->SetSprite(HalfMoonEnemySprite);
		const Vec2Int size = HalfMoonEnemySprite->GetSize();
		halfMoonEnemy->SetTarget(target);
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
			halfMoonEnemy->AddComponent(collider);
		}
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(halfMoonEnemy);
	}
		break;
	}
}
