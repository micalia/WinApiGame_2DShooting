#pragma once

enum
{
	S_TEST = 1,
	S_EnterGame = 2,

	S_MyPlayer = 4,
	S_AddObject = 5,
	S_RemoveObject = 6,

	C_Move = 10,
	S_Move = 11,

	C_Projectile = 12,
	S_Projectile = 13,

	C_Score = 14,
	S_Score = 15,

	S_EnemyMove = 16,
	S_EnemyMissile = 17,

	S_PlayerMissileMove = 18,

	S_EnemyDamaged = 19,

	S_PlayerDamaged = 20,
};

struct BuffData
{
	uint64 buffId;
	float remainTime;
};

class ServerPacketHandler
{
public:
	static void HandlePacket(GameSessionRef session, BYTE* buffer, int32 len);

	// 받기
	static void Handle_C_Move(GameSessionRef session, BYTE* buffer, int32 len);
	static void Handle_C_Projectile(GameSessionRef session, BYTE* buffer, int32 len);
	static void Handle_C_Score(GameSessionRef session, BYTE* buffer, int32 len);
	
	// 보내기
	static SendBufferRef Make_S_TEST(uint64 id, uint32 hp, uint16 attack, vector<BuffData> buffs);
	static SendBufferRef Make_S_EnterGame();
	static SendBufferRef Make_S_MyPlayer(const Protocol::ObjectInfo& info);
	static SendBufferRef Make_S_AddObject(const Protocol::S_AddObject& pkt);
	static SendBufferRef Make_S_RemoveObject(const Protocol::S_RemoveObject& pkt);
	static SendBufferRef Make_S_Move(const Protocol::ObjectInfo& info);
	static SendBufferRef Make_S_Projectile(const Protocol::ObjectInfo& info);
	static SendBufferRef Make_S_PlayerMissileMove(const Protocol::ObjectInfo& info);
	static SendBufferRef Make_S_PlayerDamaged(const Protocol::ObjectInfo& info);
	static SendBufferRef Make_S_Score(const Protocol::ScoreInfo& scoreInfo);
	static SendBufferRef Make_S_EnemyMove(const Protocol::EnemyInfo& enemyInfo);
	static SendBufferRef Make_S_EnemyMissileMove(const Protocol::EnemyMissileInfo& enemyMissileInfo);
	static SendBufferRef Make_S_EnemyDamaged(const Protocol::EnemyInfo& enemyInfo);

	template<typename T>
	static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = make_shared<SendBuffer>(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		assert(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};

// https://minusi.tistory.com/entry/%EA%B5%AC%EA%B8%80-%ED%94%84%EB%A1%9C%ED%86%A0%EC%BD%9C-%EB%B2%84%ED%8D%BC-%EC%82%AC%EC%9A%A9%ED%95%98%EA%B8%B0with-visual-studio