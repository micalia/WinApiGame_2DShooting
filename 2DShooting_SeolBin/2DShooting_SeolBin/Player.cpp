#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "DevScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CameraComponent.h"
#include "Missile.h"
#include "Sprite.h"
#include "BoxCollider.h"
#include "CollisionManager.h"

Player::Player()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"BlueMissile", L"Sprite\\Projectile\\BlueMissile.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"BlueMissile", GET_SINGLE(ResourceManager)->GetTexture(L"BlueMissile"));
}

Player::~Player()
{

}

void Player::BeginPlay()
{
	Super::BeginPlay();
}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	MoveAction();
	
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// TODO : 미사일 발사

		Sprite* BlueMissileSprite = GET_SINGLE(ResourceManager)->GetSprite(L"BlueMissile");

		Missile* BlueMissile = new Missile();
		BlueMissile->SetPos(_pos);
		BlueMissile->SetSprite(BlueMissileSprite);
		BlueMissile->SetLayer(LAYER_BULLET); 
		BoxCollider* collider = new BoxCollider();
		collider->SetShowDebug(true);
		collider->SetSize(Vec2(21, 45));
		GET_SINGLE(CollisionManager)->AddCollider(collider);
		BlueMissile->AddComponent(collider);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(BlueMissile);
	}
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::MoveAction()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	// 거리 = 시간 * 속도

	Horizontal = 0;
	Vertical = 0;

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		Horizontal = -1;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		Horizontal = 1;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		Vertical = -1;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		Vertical = 1;
	}

	Vec2 dir = Vec2(Horizontal, Vertical);
	dir.Normalize();

	Vec2 moveDir = dir * speed* deltaTime;
	_pos += moveDir;
}

