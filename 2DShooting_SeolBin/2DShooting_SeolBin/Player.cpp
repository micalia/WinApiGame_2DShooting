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

Player::Player()
{
//	FB_BluePlayer = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BluePlayer");
	GET_SINGLE(ResourceManager)->LoadTexture(L"BlueMissile", L"Sprite\\Projectile\\BlueMissile.bmp", RGB(255, 255, 255));
	GET_SINGLE(ResourceManager)->CreateSprite(L"BlueMissile", GET_SINGLE(ResourceManager)->GetTexture(L"BlueMissile"));
}

Player::~Player()
{

}

void Player::BeginPlay()
{
	Super::BeginPlay();

	SetState(PlayerState::Move);
	SetState(PlayerState::Idle);

	/*SetCellPos({ 5, 5 }, true);
	SetFlipbook(FB_BluePlayer);*/
}

void Player::Tick()
{
	Super::Tick();
	
	MoveAction();
	
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// TODO : 미사일 발사

		Sprite* BlueMissileSprite = GET_SINGLE(ResourceManager)->GetSprite(L"BlueMissile");

		Missile* BlueMissile = new Missile();
		BlueMissile->SetPos(_pos);
		BlueMissile->SetSprite(BlueMissileSprite);
		BlueMissile->SetLayer(LAYER_OBJECT); 
		/*const Vec2Int size = BlueMissileSprite->GetSize();
		BlueMissile->SetPos(Vec2(size.x / 2, size.y / 2));*/
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(BlueMissile);


		/*Missile* missile = new Missile();
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(missile);*/
	}

	return;
	switch (_state)
	{
	case PlayerState::Idle:
		TickIdle();
		break;
	case PlayerState::Move:
		TickMove();
		break;
	case PlayerState::Skill:
		TickSkill();
		break;
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

	auto Val = _sprite;
	auto pos = Val->GetPos();
	auto a = pos;
}

void Player::TickIdle()
{
	_keyPressed = true;
	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		SetDir(DIR_UP);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		/*if (CanGo(nextPos))
		{*/
			//SetCellPos(nextPos);
			SetState(PlayerState::Move);
		//}
	}
	else  if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetDir(DIR_DOWN);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		/*if (CanGo(nextPos))
		{*/
			//SetCellPos(nextPos);
			SetState(PlayerState::Move);
		//}
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		/*if (CanGo(nextPos))
		{*/
			//SetCellPos(nextPos);
			SetState(PlayerState::Move);
		//}
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		/*if (CanGo(nextPos))
		{*/
			//SetCellPos(nextPos);
			SetState(PlayerState::Move);
		//}
	}
	else
	{
		_keyPressed = false;
		SetDir(DIR_UP);
		if (_state == PlayerState::Idle)
			UpdateAnimation();
	}
}

void Player::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	
	/*Vec2 dir = (_destPos - _pos);
	if (dir.Length() < 10.f)
	{
		SetState(PlayerState::Idle);
		_pos = _destPos;
	}
	else
	{*/
		switch (_dir)
		{
		case DIR_UP:
			_pos.y -= 200 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 200 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 200 * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += 200 * deltaTime;
			break;
		}
	//}
}

void Player::TickSkill()
{

}

void Player::SetState(PlayerState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void Player::SetDir(Dir dir)
{
	_dir = dir;
	UpdateAnimation();
}

bool Player::HasReachedDest()
{
	Vec2 dir = (_destPos - _pos);
	return (dir.Length() < 10.f);
}

bool Player::CanGo(Vec2Int cellPos)
{
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return false;

	return scene->CanGo(cellPos);
}

void Player::SetCellPos(Vec2Int cellPos, bool teleport /*= false*/)
{
	_cellPos = cellPos;

	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	_destPos = scene->ConvertPos(cellPos);

	if (teleport)
		_pos = _destPos;
}

void Player::SetPlayerColor(PlayerColor color)
{

}

void Player::UpdateAnimation()
{
	/*switch (_state)
	{
	case PlayerState::Idle:
		if (_keyPressed)
			SetFlipbook(BluePlayerMove[_dir]);
		else
			SetFlipbook(BluePlayerMove[_dir]);
		break;
	case PlayerState::Move:
		SetFlipbook(BluePlayerMove[_dir]);
		break;
	case PlayerState::Skill:
		SetFlipbook(BluePlayerMove[_dir]);
		break;
	}*/
}
