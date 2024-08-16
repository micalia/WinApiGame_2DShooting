#pragma once
#include "Player.h"
class MyPlayer : public Player
{
	using Super = Player;
public:
	MyPlayer();
	virtual ~MyPlayer() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(HDC hdc) override;

private:
	void TickInput();
	void MoveAction();

	void Server_Missile();
private:
	void SyncToServer();
	float currPacketSendDelay = 0;
	float PacketSendDelay = 0.0f;

private:
	float Horizontal = 0;
	float Vertical = 0;

};

