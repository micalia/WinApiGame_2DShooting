#include "pch.h"
#include "DevScene.h"
#include "ResourceManager.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "Texture.h"

DevScene::DevScene()
{

}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Background", L"Sprite\\Map\\Background.bmp");

	/*GET_SINGLE(ResourceManager)->CreateSprite(L"Background", GET_SINGLE(ResourceManager)->GetTexture(L"Background"), 0, 0, 0, 0);

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Background");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		const Vec2Int size = sprite->GetSize();
		background->SetPos(Vec2(size.x / 2, size.y / 2));

		AddActor(background);
	}*/

	Super::Init();
}

void DevScene::Update()
{
	Super::Update();

}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);

	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Background");

	::BitBlt(hdc, 200, 0, 1500, 1000, tex->GetDC(), 0, 0, SRCCOPY);
}
