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
	SyncToServer();

	currFireTermTime+=deltaTime;
	if (currFireTermTime > fireTermTime) {
		currFireTermTime = 0;
		return;
		_dirtyFlag = true;
		Server_Missile();
	}
}

void MyPlayer::Render(HDC hdc)
{
	Super::Render(hdc);

	Utils::DrawCircle(hdc, _pos, 10);
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

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		_dirtyFlag = true;
		Server_Missile();
	}
}

void MyPlayer::MoveAction()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	Vec2 dir = Vec2(Horizontal, Vertical);
	dir.Normalize();

	Vec2 moveDir = dir * speed * deltaTime;
	_pos += moveDir;

	info.set_posx(_pos.x);
	info.set_posy(_pos.y);

	_dirtyFlag = true;
	currPacketSendDelay+=deltaTime;
	if (currPacketSendDelay > PacketSendDelay) {
		currPacketSendDelay = 0;
	}
}

void MyPlayer::Server_Missile()
{
	if (_dirtyFlag == false)
		return;

	SendBufferRef sendBuffer = ClientPacketHandler::Make_C_Projectile();
	GET_SINGLE(NetworkManager)->SendPacket(sendBuffer);
}

void MyPlayer::SyncToServer()
{
	if(_dirtyFlag == false)
		return;

	SendBufferRef sendBuffer = ClientPacketHandler::Make_C_Move();
	GET_SINGLE(NetworkManager)->SendPacket(sendBuffer);
}
