#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "DevScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CameraComponent.h"
#include "BoxCollider.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "Missile.h"
#include "CollisionManager.h"

Player::Player()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"BlueMissile", L"Sprite\\Projectile\\BlueMissile.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"BlueMissile", GET_SINGLE(ResourceManager)->GetTexture(L"BlueMissile"));

	_blueFlipbookIdle			= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayerIdle");
	_blueFlipbookLeft			= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayerLeft");
	_blueFlipbookRight			= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayerRight");
	_blueFlipbookLeftReverse	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayerLeftReverse");
	_blueFlipbookRightReverse	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayerRightReverse");

	_redFlipbookIdle			= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_RedPlayerIdle");
	_redFlipbookLeft			= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_RedPlayerLeft");
	_redFlipbookRight			= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_RedPlayerRight");
	_redFlipbookLeftReverse		= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_RedPlayerLeftReverse");
	_redFlipbookRightReverse	= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_RedPlayerRightReverse");
}

Player::~Player()
{

}

void Player::BeginPlay()
{
	Super::BeginPlay();

	bCrashing = false;

	if (GetName() == "RedPlayer") {
		SetFlipbook(_redFlipbookIdle);
	}
	else {
		SetFlipbook(_blueFlipbookIdle);
	}
}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	MoveAction();
	ReverseAnimDelay(deltaTime);

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
	//_pos = Vec2(info.posx(), info.posy());
	
	SetState(info.playerdirtype());
	
	UpdateAnimation();
}

void Player::UpdateAnimation()
{
	if (bReverseAnimOn == true) return;
	if (prevPlayerDir == playerDir) return;

	switch (info.playerdirtype())
	{
	case PD_IDLE:
		if (prevPlayerDir == PD_IDLE) {
			if (GetName() == "RedPlayer") {
				SetFlipbook(_redFlipbookIdle);
			}
			else {
				SetFlipbook(_blueFlipbookIdle);
			}
		}
		else if (prevPlayerDir == PD_LEFT) {
			if (GetName() == "RedPlayer") {
				SetFlipbook(_redFlipbookLeftReverse);
			}
			else {
				SetFlipbook(_blueFlipbookLeftReverse);
			}
			bReverseAnimOn = true;
		}
		else if (prevPlayerDir == PD_RIGHT) {
			if (GetName() == "RedPlayer") {
				SetFlipbook(_redFlipbookRightReverse);
			}
			else {
				SetFlipbook(_blueFlipbookRightReverse);
			}
			bReverseAnimOn = true;
		}
		break;
	case PD_LEFT:
		if (GetName() == "RedPlayer") {
			SetFlipbook(_redFlipbookLeft);
		}
		else {
			SetFlipbook(_blueFlipbookLeft);
		}
		break;
	case PD_RIGHT:
		if (GetName() == "RedPlayer") {
			SetFlipbook(_redFlipbookRight);
		}
		else {
			SetFlipbook(_blueFlipbookRight);
		}
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

	info.set_playerdirtype(InDir);
	playerDir = InDir;
	UpdateAnimation();
	_dirtyFlag = true;
}

void Player::Fire(Protocol::ObjectInfo info)
{
	// TODO : 미사일 발사
	Sprite* BlueMissileSprite = GET_SINGLE(ResourceManager)->GetSprite(L"BlueMissile");

	Missile* BlueMissile = new Missile();
	BlueMissile->SetPos(Vec2{ info.posx(), info.posy() });
	BlueMissile->SetSprite(BlueMissileSprite);
	BlueMissile->SetLayer(LAYER_BULLET);
	info.set_objecttype(Protocol::OBJECT_TYPE_PLAYER_MISSILE);
	Vec2Int MissileSpriteSize = BlueMissileSprite->GetSize();
	{
		BoxCollider* collider = new BoxCollider();
		collider->SetCollisionLayer(CLT_MISSILE);
		collider->SetShowDebug(true);
		collider->SetSize(Vec2(MissileSpriteSize.x, MissileSpriteSize.y));
		GET_SINGLE(CollisionManager)->AddCollider(collider);
		BlueMissile->AddComponent(collider);
	}
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(BlueMissile);
}

void Player::ReverseAnimDelay(float InDeltaTime)
{
	if (bReverseAnimOn) {
		currReverseAnimDelayTime += InDeltaTime;
		if (currReverseAnimDelayTime > reverseAnimDelayTime) {
			bReverseAnimOn = false;
			currReverseAnimDelayTime = 0;
			if (GetName() == "RedPlayer") {
				SetFlipbook(_redFlipbookIdle);
			}
			else {
				SetFlipbook(_blueFlipbookIdle);
			}
		}
	}
}

