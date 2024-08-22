#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "GameSession.h"
#include "GameRoom.h"

void ServerPacketHandler::HandlePacket(GameSessionRef session, BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case C_Move:
		Handle_C_Move(session, buffer, len);
		break;
	case C_Projectile:
		Handle_C_Projectile(session, buffer, len);
		break;
	case C_Score:
		Handle_C_Score(session, buffer, len);
		break;
	default:
		break;
	}
}

void ServerPacketHandler::Handle_C_Move(GameSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	//uint16 id = header->id;
	uint16 size = header->size;

	Protocol::C_Move pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	GameRoomRef gameRoom = session->gameRoom.lock();
	if(gameRoom)
		gameRoom->Handle_C_Move(pkt);
}

void ServerPacketHandler::Handle_C_Projectile(GameSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	//uint16 id = header->id;
	uint16 size = header->size;

	Protocol::C_Projectile pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	GameRoomRef gameRoom = session->gameRoom.lock();
	if (gameRoom)
		gameRoom->Handle_C_Projectile(pkt);
}

void ServerPacketHandler::Handle_C_Score(GameSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::C_Score pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	GameRoomRef gameRoom = session->gameRoom.lock();
	if (gameRoom)
		gameRoom->Handle_C_Score(pkt);
}

SendBufferRef ServerPacketHandler::Make_S_TEST(uint64 id, uint32 hp, uint16 attack, vector<BuffData> buffs)
{
	Protocol::S_TEST pkt;

	pkt.set_id(10);
	pkt.set_hp(100);
	pkt.set_attack(10);

	{
		Protocol::BuffData* data = pkt.add_buffs();
		data->set_buffid(100);
		data->set_remaintime(1.2f);
		{
			data->add_victims(10);
		}
	}
	{
		Protocol::BuffData* data = pkt.add_buffs();
		data->set_buffid(200);
		data->set_remaintime(2.2f);
		{
			data->add_victims(20);
		}
	}

	return MakeSendBuffer(pkt, S_TEST);
}
// [2byte][2byte][           ] => 앞에 2b바이트 2개에는 패킷사이즈와 아이디 정보를 넣는다.
SendBufferRef ServerPacketHandler::Make_S_EnterGame()
{
	Protocol::S_EnterGame pkt;

	pkt.set_success(true);
	pkt.set_accountid(0);

	return MakeSendBuffer(pkt, S_EnterGame);
}

SendBufferRef ServerPacketHandler::Make_S_MyPlayer(const Protocol::ObjectInfo& info)
{
	Protocol::S_MyPlayer pkt;

	Protocol::ObjectInfo* objectInfo = pkt.mutable_info();
	*objectInfo = info;
	
	return MakeSendBuffer(pkt, S_MyPlayer);
}

SendBufferRef ServerPacketHandler::Make_S_AddObject(const Protocol::S_AddObject& pkt)
{
	return MakeSendBuffer(pkt, S_AddObject);
}

SendBufferRef ServerPacketHandler::Make_S_RemoveObject(const Protocol::S_RemoveObject& pkt)
{
	return MakeSendBuffer(pkt, S_RemoveObject);
}

SendBufferRef ServerPacketHandler::Make_S_Move(const Protocol::ObjectInfo& info)
{
	Protocol::S_Move pkt;

	Protocol::ObjectInfo* objectInfo = pkt.mutable_info();
	*objectInfo = info;

	return MakeSendBuffer(pkt, S_Move);
}

SendBufferRef ServerPacketHandler::Make_S_Projectile(const Protocol::ObjectInfo& info)
{
	Protocol::S_Projectile pkt;

	Protocol::ObjectInfo* objectInfo = pkt.mutable_info();
	*objectInfo = info;

	return MakeSendBuffer(pkt, S_Projectile);
}

SendBufferRef ServerPacketHandler::Make_S_Score(const Protocol::ScoreInfo& scoreInfo)
{
	Protocol::S_Score pkt;

	Protocol::ScoreInfo* objectInfo = pkt.mutable_scoreinfo();
	*objectInfo = scoreInfo;

	return MakeSendBuffer(pkt, S_Score);
}

SendBufferRef ServerPacketHandler::Make_S_EnemyMove(const Protocol::EnemyInfo& enemyInfo)
{
	Protocol::S_EnemyMove pkt;

	Protocol::EnemyInfo* objectInfo = pkt.mutable_enemymoveinfo();
	*objectInfo = enemyInfo;

	return MakeSendBuffer(pkt, S_EnemyMove);
}

SendBufferRef ServerPacketHandler::Make_S_EnemyMissileMove(const Protocol::EnemyMissileInfo& enemyMissileInfo)
{
	Protocol::S_EnemyMissile pkt;

	Protocol::EnemyMissileInfo* objectInfo = pkt.mutable_enemymissileinfo();
	*objectInfo = enemyMissileInfo;

	return MakeSendBuffer(pkt, S_EnemyMissile);
}
