#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SceneManager.h"

SpriteActor::SpriteActor()
{

}

SpriteActor::~SpriteActor()
{

}

void SpriteActor::BeginPlay()
{
	Super::BeginPlay();


}

void SpriteActor::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_sprite == nullptr)
		return;

	Vec2Int size = _sprite->GetSize();
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	::TransparentBlt(hdc,
		(int32)_pos.x - size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
		(int32)_pos.y - size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		size.x,
		size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		RGB(255, 255, 255));
		//_sprite->GetTransparent());

		/* 이 함수가 투명도 없이 렌더링하기 때문에 미세하게 더 빠름
		::BitBlt(hdc,
			(int32)_pos.x - size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
			(int32)_pos.y - size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
			size.x,
			size.y,
			_sprite->GetDC(),
			_sprite->GetPos().x,
			_sprite->GetPos().y,
			SRCCOPY);*/
}
