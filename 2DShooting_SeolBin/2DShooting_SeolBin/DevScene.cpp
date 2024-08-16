#include "pch.h"
#include "DevScene.h"
#include "ResourceManager.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "Texture.h"
#include "Flipbook.h"
#include "Player.h"
#include "TileMap.h"
#include "TilemapActor.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "Missile.h"
#include "Background.h"
#include "DestroyZone.h"
#include "Wall.h"
#include "EnemySpawnManager.h"
#include "ExplosionEffect.h"

DevScene::DevScene()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Background", L"Sprite\\Map\\Background.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"BluePlayer", L"Sprite\\Player\\NewBluePlayerSpriteAnim.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->LoadTexture(L"RedPlayer", L"Sprite\\Player\\NewRedPlayerSpriteAnim.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"Background", GET_SINGLE(ResourceManager)->GetTexture(L"Background"));
	GET_SINGLE(ResourceManager)->LoadTexture(L"ExplosionEffect", L"Sprite\\Effect\\ExplosionEffect.bmp", RGB(255, 255, 255));
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
#pragma region BluePlayer Anim
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BluePlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BluePlayerIdle");
		fb->SetInfo({ texture, L"FB_BluePlayerIdle", {70, 70}, 0, 0, 0, 1.f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BluePlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BluePlayerLeft");
		fb->SetInfo({ texture, L"FB_BluePlayerLeft", {70, 70}, 0, 2, 2, 0.7f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BluePlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BluePlayerRight");
		fb->SetInfo({ texture, L"FB_BluePlayerRight", {70, 70}, 0, 2, 3, 0.7f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BluePlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BluePlayerRightReverse");
		fb->SetInfo({ texture, L"FB_BluePlayerRightReverse", {70, 70}, 1, 1, 4, 0.3f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BluePlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BluePlayerLeftReverse");
		fb->SetInfo({ texture, L"FB_BluePlayerLeftReverse", {70, 70}, 1, 1, 1, 0.3f, false });
	}
#pragma endregion
#pragma region RedPlayer Anim
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"RedPlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_RedPlayerIdle");
		fb->SetInfo({ texture, L"FB_RedPlayerIdle", {70, 70}, 0, 0, 0, 1.f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"RedPlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_RedPlayerLeft");
		fb->SetInfo({ texture, L"FB_RedPlayerLeft", {70, 70}, 0, 2, 2, 0.7f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"RedPlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_RedPlayerRight");
		fb->SetInfo({ texture, L"FB_RedPlayerRight", {70, 70}, 0, 2, 3, 0.7f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"RedPlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_RedPlayerRightReverse");
		fb->SetInfo({ texture, L"FB_RedPlayerRightReverse", {70, 70}, 1, 1, 4, 0.3f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"RedPlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_RedPlayerLeftReverse");
		fb->SetInfo({ texture, L"FB_RedPlayerLeftReverse", {70, 70}, 1, 1, 1, 0.3f, false });
	}
#pragma endregion

	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ExplosionEffect");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ExplosionEffect");
		fb->SetInfo({ texture, L"FB_ExplosionEffect", {350, 350}, 0, 5, 0, 1.f, false });
	}

	{
		//Player* BluePlayer = new Player();
		//
		//BluePlayer->SetLayer(LAYER_Player);
		//const Vec2Int size = Vec2Int(47, 67);
		//BluePlayer->SetPos(Vec2(242, 588));
		//{
		//	BoxCollider* collider = new BoxCollider();
		//	collider->SetShowDebug(true);
		//	//나의 콜리전 레이어
		//	collider->SetCollisionLayer(CLT_PLAYER);

		//	// 모든 콜리전 플래그 제거
		//	collider->ResetCollisionFlag();
		//	// 내가 충돌하고 싶은 레이어 추가
		//	collider->AddCollisionFlagLayer(CLT_WALL);
		//	collider->SetSize(Vec2(size.x, size.y));
		//	GET_SINGLE(CollisionManager)->AddCollider(collider);
		//	BluePlayer->AddComponent(collider);
		//}
		//AddActor(BluePlayer);
	}

	/*{
		EnemySpawnManager* EnemySpawnMgr = new EnemySpawnManager();
		EnemySpawnMgr->SetPos(Vec2(250, 15));
		AddActor(EnemySpawnMgr);
	}*/


	Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Background");
	{

		Background* background = new Background();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		const Vec2Int size = sprite->GetSize();
		float Ysize = size.y;
		background->SetPos(Vec2(size.x / 2, Ysize));
		AddActor(background);
	}

	{
		Background* background2 = new Background();
		background2->SetSprite(sprite);
		background2->SetLayer(LAYER_BACKGROUND);
		const Vec2Int size = sprite->GetSize();
		float Ysize = size.y * 2;
		background2->SetPos(Vec2(size.x / 2, Ysize));
		AddActor(background2);
	}

	{
		Background* background3 = new Background();
		background3->SetSprite(sprite);
		background3->SetLayer(LAYER_BACKGROUND);
		const Vec2Int size = sprite->GetSize();
		float Ysize = size.y * 3;
		background3->SetPos(Vec2(size.x / 2, Ysize));
		AddActor(background3);
	}
	
#pragma region Wall
	{ // Top Wall
		DestroyZone* destroyZone = new DestroyZone();
		destroyZone->SetLayer(LAYER_OBJECT);
		destroyZone->SetPos(Vec2(250.f, 10.f));
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			collider->SetSize(Vec2(460, 10));
			collider->SetCollisionLayer(CLT_WALL);
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			destroyZone->AddComponent(collider);
		}
		AddActor(destroyZone);
	}
	
	{ // Left Wall
		DestroyZone* destroyZone = new DestroyZone();
		destroyZone->SetLayer(LAYER_OBJECT);
		destroyZone->SetPos(Vec2(10.f, 365.f));
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			collider->SetSize(Vec2(10, 700));
			collider->SetCollisionLayer(CLT_WALL);
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			destroyZone->AddComponent(collider);
		}
		AddActor(destroyZone);
	}

	{ // Right Wall
		DestroyZone* destroyZone = new DestroyZone();
		destroyZone->SetLayer(LAYER_OBJECT);
		destroyZone->SetPos(Vec2(490.f, 365.f));
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			collider->SetSize(Vec2(10, 700));
			collider->SetCollisionLayer(CLT_WALL);
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			destroyZone->AddComponent(collider);
		}
		AddActor(destroyZone);
	}

	{ // Bottom Wall
		DestroyZone* destroyZone = new DestroyZone();
		destroyZone->SetLayer(LAYER_OBJECT);
		destroyZone->SetPos(Vec2(250.f, 720.f));
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			collider->SetSize(Vec2(460, 10));
			collider->SetCollisionLayer(CLT_WALL);
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			destroyZone->AddComponent(collider);
		}
		AddActor(destroyZone);
	}
#pragma endregion

	/*{
		Wall* wall = new Wall();
		wall->SetPos(Vec2(50.f, 400.f));
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			collider->SetSize(Vec2(80, 500));
			collider->SetCollisionLayer(CLT_WALL);
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			wall->AddComponent(collider);
		}
		AddActor(wall);
	}

	{
		Wall* wall = new Wall();
		wall->SetPos(Vec2(450.f, 400.f));
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			collider->SetSize(Vec2(80, 500));
			collider->SetCollisionLayer(CLT_WALL);
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			wall->AddComponent(collider);
		}
		AddActor(wall);
	}*/
	
	/*GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 0, 50, 50);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 50, 0, 50, 50);

	{
		TilemapActor* actor = new TilemapActor();
		AddActor(actor);

		_tilemapActor = actor;
		{
			auto* tm = GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap_01");
			tm->SetMapSize({ 10, 25 });
			tm->SetTileSize(50);

			GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Tilemap\\Tilemap_01.txt");

			_tilemapActor->SetTilemap(tm);
			_tilemapActor->SetShowDebug(false);
		}
	}*/

	Super::Init();
}

void DevScene::Update()
{
	Super::Update();

	/*if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_01", L"Tilemap\\Tilemap_01.txt");
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Tilemap\\Tilemap_01.txt");
	}*/
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);

	/*Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Background");

	::BitBlt(hdc,
		0,
		0,
		GWinSizeX,
		GWinSizeY,
		sprite->GetDC(),
		sprite->GetPos().x,
		sprite->GetPos().y,
		SRCCOPY);*/
}

bool DevScene::CanGo(Vec2Int cellPos)
{
	if (_tilemapActor == nullptr)
		return false;

	Tilemap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return false;

	Tile* tile = tm->GetTileAt(cellPos);
	if (tile == nullptr)
		return false;

	return tile->value != 1;
}

Vec2 DevScene::ConvertPos(Vec2Int cellPos)
{
	Vec2 ret = {};

	if (_tilemapActor == nullptr)
		return ret;

	Tilemap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return ret;

	int32 size = tm->GetTileSize();
	Vec2 pos = _tilemapActor->GetPos();

	ret.x = pos.x + cellPos.x * size + (size / 2);
	ret.y = pos.y + cellPos.y * size + (size / 2);

	return ret;
}
