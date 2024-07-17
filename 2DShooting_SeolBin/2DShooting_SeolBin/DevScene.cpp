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

DevScene::DevScene()
{

}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Background", L"Sprite\\Map\\Background.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"BluePlayer", L"Sprite\\Player\\BluePlayer.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"Background", GET_SINGLE(ResourceManager)->GetTexture(L"Background"));

	// BluePlayer
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BluePlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BluePlayerUP");
		fb->SetInfo({ texture, L"FB_BluePlayer", {80, 80}, 2, 2, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BluePlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BluePlayerLeft");
		fb->SetInfo({ texture, L"FB_BluePlayer", {80, 80}, 1, 1, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BluePlayer");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BluePlayerRight");
		fb->SetInfo({ texture, L"FB_BluePlayer", {80, 80}, 3, 3, 0, 0.5f });
	}

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Background");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		const Vec2Int size = sprite->GetSize();
		background->SetPos(Vec2(size.x / 2, size.y / 2));
		auto Val = background->GetPos();
		AddActor(background);
	}
	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 0, 50, 50);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 50, 0, 50, 50);
	
	{ 
		Player* player = new Player();
		AddActor(player);
	}

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
	}

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
