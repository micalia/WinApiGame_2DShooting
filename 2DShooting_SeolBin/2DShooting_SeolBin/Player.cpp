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
#include "ExplosionEffect.h"

Player::Player()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"BlueMissile", L"Sprite\\Projectile\\BlueMissile.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"BlueMissile", GET_SINGLE(ResourceManager)->GetTexture(L"BlueMissile"));

	GET_SINGLE(ResourceManager)->LoadTexture(L"RedMissile", L"Sprite\\Projectile\\RedMissile.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"RedMissile", GET_SINGLE(ResourceManager)->GetTexture(L"RedMissile"));

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

	_playerTransparent			= GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FullTransparent");
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
	
	if (bRespawn) {
		currBlinkTime += deltaTime;
		if (currBlinkTime > blinkTime) {
			currBlinkTime = 0;
			blinkCurrCount++;
			bTransparent = (bTransparent == true) ? false : true;
			if (blinkCurrCount > blinkCount) {
				blinkCurrCount = 0;
				bTransparent = false;
				bRespawn = false;
			}
		}
	}
}

void Player::Render(HDC hdc)
{
	if(bTransparent) return;
	Super::Render(hdc);
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	Super::OnComponentBeginOverlap(collider, other);
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	Super::OnComponentEndOverlap(collider, other);
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

void Player::Fire(Protocol::ObjectInfo InInfo)
{
	// TODO : 미사일 발사
	Sprite* missileSprite = nullptr;
	if (InInfo.name() == "RedPlayer") {
		missileSprite = GET_SINGLE(ResourceManager)->GetSprite(L"RedMissile");
	}
	else {
		missileSprite = GET_SINGLE(ResourceManager)->GetSprite(L"BlueMissile");
	}

	Missile* missile = GET_SINGLE(SceneManager)->GetCurrentScene()->SpawnActor<Missile>(Vec2{ InInfo.posx(), InInfo.posy() }, LAYER_BULLET);
	missile->SetSprite(missileSprite);
	InInfo.set_objecttype(Protocol::OBJECT_TYPE_PLAYER_MISSILE);
	Vec2Int MissileSpriteSize = missileSprite->GetSize();
	missile->SetOwner(this);
	/*if(info.name() == InInfo.name())
	{
		BoxCollider* collider = new BoxCollider();
		collider->SetCollisionLayer(CLT_MISSILE);
		collider->SetShowDebug(true);
		collider->SetSize(Vec2(MissileSpriteSize.x, MissileSpriteSize.y));
		GET_SINGLE(CollisionManager)->AddCollider(collider);
		missile->AddComponent(collider);
	}*/
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(missile);
}

void Player::Damaged()
{
	ExplosionEffect* explosionEffect = GET_SINGLE(SceneManager)->GetCurrentScene()->SpawnActor<ExplosionEffect>(GetPos()); 
	SetPlayerState(RespawnScene);
	if (GetName() == "RedPlayer") {
		SetFlipbook(_redFlipbookIdle);
	}
	else if (GetName() == "BluePlayer") {
		SetFlipbook(_blueFlipbookIdle);
	}
	prevPlayerDir = PD_IDLE;
	bCrashing = false;
}

void Player::SetPlayerState(PlayerState playerState)
{
	switch (playerState)
	{
	case RespawnScene:
		SetPos(GET_SINGLE(SceneManager)->GetDevScene()->GetRespawnStartPos());
		break;
	case RespawnSceneComplete:
		break;
	default:
		break;
	}
	_playerState = playerState;
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

