#include "pch.h"
#include "MyPlayer.h"
#include "InputManager.h"
#include "TimeManager.h"

MyPlayer::MyPlayer()
{

}

MyPlayer::~MyPlayer()
{

}

void MyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void MyPlayer::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	TickInput();
	MoveAction();
}

void MyPlayer::Render(HDC hdc)
{
	Super::Render(hdc);
}

void MyPlayer::TickInput()
{
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

	if (Horizontal > 0) {
		SetState(PD_RIGHT);
	}
	else if (Horizontal < 0)
	{
		SetState(PD_LEFT);
	}
	else {
		SetState(PD_IDLE);
	}
}

void MyPlayer::MoveAction()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	Vec2 dir = Vec2(Horizontal, Vertical);
	dir.Normalize();

	Vec2 moveDir = dir * speed * deltaTime;
	_pos += moveDir;
}
