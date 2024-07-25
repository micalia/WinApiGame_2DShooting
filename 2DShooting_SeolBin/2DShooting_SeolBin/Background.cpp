#include "pch.h"
#include "Background.h"
#include "Sprite.h"

Background::Background()
{

}

Background::~Background()
{

}

void Background::BeginPlay()
{
	Super::BeginPlay(); 
	SpriteHeight = _sprite->GetSize().y;
	SpriteWidth = _sprite->GetSize().x;
}

void Background::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	if (deltaTime > 0.1f) return;
	_pos.y += deltaTime * speed;

	if (_pos.y > SpriteHeight * 2) { 
		_pos.y -= (SpriteHeight * 3);
	}
}

void Background::Render(HDC hdc)
{
	Super::Render(hdc);
}
