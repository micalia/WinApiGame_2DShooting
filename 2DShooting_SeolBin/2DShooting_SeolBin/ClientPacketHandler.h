#pragma once
// ClientPacketHandler : 서버에서 보내준 패킷을 처리하는 역할
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

class Player;

class ClientPacketHandler
{
public:
	static void HandlePacket(ServerSessionRef session, BYTE* buffer, int32 len);

	// 받기
	static void Handle_S_TEST(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_EnterGame(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_MyPlayer(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_AddObject(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_RemoveObject(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_Move(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_Projectile(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_Score(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_EnemyMove(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_EnemyMissileMove(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_PlayerMissileMove(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_EnemyDamaged(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_PlayerDamaged(ServerSessionRef session, BYTE* buffer, int32 len);

	// 보내기
	static SendBufferRef Make_C_Move();
	static SendBufferRef Make_C_Projectile();
	static SendBufferRef Make_C_ScoreCalculate(Player* player);

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
	

