// ClientPacketHandler : �������� ������ ��Ŷ�� ó���ϴ� ����
#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "DevScene.h"
#include "SceneManager.h"
#include "MyPlayer.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Missile.h"
#include "Struct.pb.h"
#include "GameManager.h"
#include "Enemy.h"
#include "EnemyMissile.h"
#include "EnemyManager.h"

void ClientPacketHandler::HandlePacket(ServerSessionRef session, BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	switch (header.id)
	{
	case S_EnterGame:
		Handle_S_EnterGame(session, buffer, len);
		break;
	case S_MyPlayer:
		Handle_S_MyPlayer(session, buffer, len);
		break;
	case S_AddObject:
		Handle_S_AddObject(session, buffer, len);
		break;
	case S_RemoveObject:
		Handle_S_RemoveObject(session, buffer, len);
		break;
	case S_Move:
		Handle_S_Move(session, buffer, len);
		break;
	case S_Projectile:
		Handle_S_Projectile(session, buffer, len);
		break;
	case S_Score:
		Handle_S_Score(session, buffer, len);
		break;
	case S_EnemyMove:
		Handle_S_EnemyMove(session, buffer, len);
		break;
	case S_EnemyMissile:
		Handle_S_EnemyMissileMove(session, buffer, len);
		break;
	case S_PlayerMissileMove:
		Handle_S_PlayerMissileMove(session, buffer, len);
		break;
	case S_EnemyDamaged:
		Handle_S_EnemyDamaged(session, buffer, len);
		break;
	case S_PlayerDamaged:
		Handle_S_PlayerDamaged(session, buffer, len);
		break;
	}
}

void ClientPacketHandler::Handle_S_TEST(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	//uint16 id = header->id;
	uint16 size = header->size;

	Protocol::S_TEST pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	uint64 id = pkt.id();
	uint32 hp = pkt.hp();
	uint16 attack = pkt.attack();

	cout << "ID: " << id << " HP : " << hp << " ATT : " << attack << endl;

	for (int32 i = 0; i < pkt.buffs_size(); i++)
	{
		const Protocol::BuffData& data = pkt.buffs(i);
		cout << "BuffInfo : " << data.buffid() << " " << data.remaintime() << endl;
	}
}

void ClientPacketHandler::Handle_S_EnterGame(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	//uint16 id = header->id;
	uint16 size = header->size;

	Protocol::S_EnterGame pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	bool success = pkt.success();
	uint64 accountId = pkt.accountid();
}

void ClientPacketHandler::Handle_S_MyPlayer(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	//uint16 id = header->id;
	uint16 size = header->size;

	Protocol::S_MyPlayer pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));
	 
	//
	const Protocol::ObjectInfo& info = pkt.info();

	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene)
	{
		MyPlayer* myPlayer = scene->SpawnActor<MyPlayer>(Vec2{ info.posx(), info.posy()}, LAYER_Player, info);
		//MyPlayer* myPlayer = scene->SpawnActor<MyPlayer>(Vec2{ info.posx(), info.posy() });
		//myPlayer->SetLayer(LAYER_Player);
		myPlayer->SetName(info.name().c_str());
		const Vec2Int size = Vec2Int(47, 67);
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetShowDebug(true);
			//���� �ݸ��� ���̾�
			collider->SetCollisionLayer(CLT_PLAYER);

			// ��� �ݸ��� �÷��� ����
			collider->ResetCollisionFlag();
			// ���� �浹�ϰ� ���� ���̾� �߰�
			collider->AddCollisionFlagLayer(CLT_WALL);
			collider->AddCollisionFlagLayer(CLT_ENEMY_MISSILE);
			myPlayer->SetPlayerCollisionFlag(collider->GetCollisionFlag());
			collider->SetSize(Vec2(size.x, size.y));
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			myPlayer->AddComponent(collider);
		}
		GET_SINGLE(SceneManager)->SetMyPlayer(myPlayer);
	}
}

void ClientPacketHandler::Handle_S_AddObject(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	//uint16 id = header->id;
	uint16 size = header->size;

	Protocol::S_AddObject pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene)
		scene->Handle_S_AddObject(pkt);
}

void ClientPacketHandler::Handle_S_RemoveObject(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	//uint16 id = header->id;
	uint16 size = header->size;

	Protocol::S_RemoveObject pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene)
		scene->Handle_S_RemoveObject(pkt);
}

void ClientPacketHandler::Handle_S_Move(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	//uint16 id = header->id;
	uint16 size = header->size;

	Protocol::S_Move pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	const Protocol::ObjectInfo& info = pkt.info();

	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene) {
		uint64 myPlayerId = GET_SINGLE(SceneManager)->GetMyPlayerId();
		if(myPlayerId == info.objectid())
			return;

		Actor* actor = scene->GetObject(info.objectid());
		if (actor) {
			actor->SetState(info.playerdirtype());
			actor->SetPos(Vec2{info.posx(), info.posy()});
		}
	}
}

void ClientPacketHandler::Handle_S_Projectile(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	//uint16 id = header->id;
	uint16 size = header->size;

	Protocol::S_Move pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	const Protocol::ObjectInfo& info = pkt.info();

	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene) {
		switch (info.objecttype()) {
			case Protocol::OBJECT_TYPE_PLAYER_MISSILE:
			{
				auto myPlayer = GET_SINGLE(SceneManager)->GetMyPlayer();
				myPlayer->Fire(info);
			}
				break;
		}
	}
}

void ClientPacketHandler::Handle_S_Score(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_Score pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	const Protocol::ScoreInfo& scoreInfo = pkt.scoreinfo();
	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene) {
		GET_SINGLE(GameManager)->SetScore(scoreInfo.playername(), scoreInfo.fullscore());
	}
}

void ClientPacketHandler::Handle_S_EnemyMove(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_EnemyMove pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));
	//
	const Protocol::EnemyInfo& info = pkt.enemymoveinfo();

	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene)
	{
		Enemy* enemy  = static_cast<Enemy*>(scene->GetObject(info.objectid()));
		if (enemy)
		{
			enemy->SetPos(Vec2(info.posx(), info.posy()));
			enemy->SetServerNewLocation(Vec2(info.posx(), info.posy()));
			enemy->OnRep_ServerLoc();
		}
	}
}

void ClientPacketHandler::Handle_S_EnemyMissileMove(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_EnemyMissile pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));
	
	const Protocol::EnemyMissileInfo& info = pkt.enemymissileinfo();

	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene)
	{
		EnemyMissile* missile = static_cast<EnemyMissile*>(scene->GetEnemyMgr()->GetMissileObj(info.objectid()));
		if (missile)
		{
			missile->SetPos(Vec2(info.posx(), info.posy()));
			missile->SetServerNewLocation(Vec2(info.posx(), info.posy()));
			missile->OnRep_ServerLoc();
		}
	}
}

void ClientPacketHandler::Handle_S_PlayerMissileMove(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_PlayerMissileMove pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	const Protocol::ObjectInfo& info = pkt.missileinfo();

	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene)
	{
		Missile* missile = static_cast<Missile*>(scene->GetMissileObj(info.objectid()));
		if (missile)
		{
			missile->SetPos(Vec2(info.posx(), info.posy()));
			missile->SetServerNewLocation(Vec2(info.posx(), info.posy()));
			missile->OnRep_ServerLoc();
		}
	}
}

void ClientPacketHandler::Handle_S_EnemyDamaged(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_EnemyDamaged pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));
	//
	const Protocol::EnemyInfo& info = pkt.enemyinfo();

	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene)
	{
		Enemy* enemy = static_cast<Enemy*>(scene->GetObject(info.objectid()));
		if (enemy)
		{
			enemy->SetHp(info.hp());
			enemy->Damaged();
		}
	}
}

void ClientPacketHandler::Handle_S_PlayerDamaged(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_PlayerDamaged pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));
	
	const Protocol::ObjectInfo& info = pkt.info();

	DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene();
	if (scene)
	{
		Player* player = dynamic_cast<Player*>(scene->GetObject(info.objectid()));
		if (player) {
			player->SetRespawn(true);
			player->Damaged();
			player->SetPos(Vec2{ info.posx(), info.posy() });
		}
	}
}

SendBufferRef ClientPacketHandler::Make_C_Move()
{
	Protocol::C_Move pkt;

	MyPlayer* myPlayer = GET_SINGLE(SceneManager)->GetMyPlayer();
	*pkt.mutable_info() = myPlayer->info;

	return MakeSendBuffer(pkt, C_Move);
}

SendBufferRef ClientPacketHandler::Make_C_Projectile()
{
	Protocol::C_Projectile pkt;

	MyPlayer* myPlayer = GET_SINGLE(SceneManager)->GetMyPlayer();
	Protocol::ObjectInfo missileInfo = myPlayer->info;
	missileInfo.set_objectownerid(myPlayer->GetObjectID());
	*pkt.mutable_info() = missileInfo;

	return MakeSendBuffer(pkt, C_Projectile);
}

SendBufferRef ClientPacketHandler::Make_C_ScoreCalculate(Player* player)
{
	Protocol::C_Score pkt;
	if(player == nullptr) return nullptr;
	*pkt.mutable_scoreinfo() = player->scoreInfo;

	return MakeSendBuffer(pkt, C_Score);
}
