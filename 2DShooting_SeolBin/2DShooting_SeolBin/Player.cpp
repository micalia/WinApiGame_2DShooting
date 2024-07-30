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
#include "Flipbook.h"

Player::Player()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"BlueMissile", L"Sprite\\Projectile\\BlueMissile.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"BlueMissile", GET_SINGLE(ResourceManager)->GetTexture(L"BlueMissile"));

	_flipbookIdle = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayerIdle");
	_flipbookLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayerLeft");
	_flipbookRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayerRight");
	_flipbookLeftReverse = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayerLeftReverse");
	_flipbookRightReverse = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayerRightReverse");
}

Player::~Player()
{

}

void Player::BeginPlay()
{
	Super::BeginPlay();

	bCrashing = false;
	SetFlipbook(_flipbookIdle);

	
}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	MoveAction();
	ReverseAnimDelay(deltaTime);

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// TODO : 미사일 발사

		Sprite* BlueMissileSprite = GET_SINGLE(ResourceManager)->GetSprite(L"BlueMissile");

		Missile* BlueMissile = new Missile();
		BlueMissile->SetPos(_pos);
		BlueMissile->SetSprite(BlueMissileSprite);
		BlueMissile->SetLayer(LAYER_BULLET); 
		Vec2Int MissileSpriteSize = BlueMissileSprite->GetSize();
		BoxCollider* collider = new BoxCollider();
		collider->SetShowDebug(true);
		collider->SetSize(Vec2(MissileSpriteSize.x, MissileSpriteSize.y));
		GET_SINGLE(CollisionManager)->AddCollider(collider);
		BlueMissile->AddComponent(collider);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(BlueMissile);
	}

	if (bCrashing) {
		SetPos(CrashingPos);
	}
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	Super::OnComponentBeginOverlap(collider, other);
	bCrashing = true;
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);
	if (b1 == nullptr || b2 == nullptr)
		return;

	AdjustCollisionPos(b1, b2);
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	Super::OnComponentEndOverlap(collider, other);
	bCrashing = false;
}

void Player::AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vec2 pos = GetPos();
	RECT intersect = {};
	if (::IntersectRect(&intersect, &r1, &r2)) {
		int32 w = intersect.right - intersect.left;
		int32 h = intersect.bottom - intersect.top;

		if (w > h) {
			if (intersect.top == r2.top) {
				pos.y -= h;
			}
			else {
				pos.y += h;
			}
		}
		else {
			if (intersect.left == r2.left) {
				pos.x -= w;
			}
			else {
				pos.x += w;
			}
		}
	}

	CrashingPos = pos;
	SetPos(CrashingPos);
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

	if (Horizontal > 0) {
		SetState(PlayerDir::Right);
	}
	else if(Horizontal < 0)
	{
		SetState(PlayerDir::Left);
	}
	else {
		SetState(PlayerDir::Idle);
	}

	
	UpdateAnimation();
}

void Player::UpdateAnimation()
{
	if (bReverseAnimOn == true) return;
	if (prevPlayerDir == playerDir) return;

	switch (playerDir)
	{
	case PlayerDir::Idle:
		if (prevPlayerDir == PlayerDir::Idle) {
			SetFlipbook(_flipbookIdle);
		}
		else if (prevPlayerDir == PlayerDir::Left) {
			SetFlipbook(_flipbookLeftReverse);
			bReverseAnimOn = true;
		}
		else if (prevPlayerDir == PlayerDir::Right) {
			SetFlipbook(_flipbookRightReverse);
			bReverseAnimOn = true;
		}
		break;
	case PlayerDir::Left:
		SetFlipbook(_flipbookLeft);
		break;
	case PlayerDir::Right:
		SetFlipbook(_flipbookRight);
		break;
	default:
		break;
	}
	prevPlayerDir = playerDir;
}

void Player::SetState(PlayerDir InDir)
{
	if (playerDir == InDir)
		return;

	playerDir = InDir;
	UpdateAnimation();
}

void Player::ReverseAnimDelay(float InDeltaTime)
{
	if (bReverseAnimOn) {
		currReverseAnimDelayTime += InDeltaTime;
		if (currReverseAnimDelayTime > reverseAnimDelayTime) {
			bReverseAnimOn = false;
			currReverseAnimDelayTime = 0;
			SetFlipbook(_flipbookIdle);
		}
	}
}

