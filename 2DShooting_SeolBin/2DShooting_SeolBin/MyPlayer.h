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

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;

	void RespawnSceneMove(float deltaTime);
	void SetPlayerCollisionFlag(uint32 collFlag){ playerCollisionFlag = collFlag;}
	uint32 GetPlayerCollisionFlag(){ return playerCollisionFlag;}
private:
	void TickInput();
	void MoveAction();

	void Server_Missile();
private:
	void SyncToServer();
	float currPacketSendDelay = 0;
	float PacketSendDelay = 0.02f;

private:
	float Horizontal = 0;
	float Vertical = 0;

	float fireTermTime = 0.2;
	float currFireTermTime = 0;

	uint32 playerCollisionFlag = 0;
};

