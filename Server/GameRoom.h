#pragma once
class GameRoom : public enable_shared_from_this<GameRoom>
{
public:
	GameRoom();
	virtual ~GameRoom();

	void Init();
	void Update();

	void EnterRoom(GameSessionRef session);
	void LeaveRoom(GameSessionRef session);
	ActorRef FindObject(uint64 id);
	GameRoomRef GetRoomRef(){return shared_from_this(); }

public:
	void Handle_C_Move(Protocol::C_Move& pkt);
	void Handle_C_Projectile(Protocol::C_Projectile& pkt);

	void AddObject(ActorRef gameObject);
	void RemoveObject(uint64 id);
	void Broadcast(SendBufferRef& sendBuffer);
private:
	map<uint64, PlayerRef> _players;
	map<uint64, EnemyRef> _enemies;
};

extern GameRoomRef GRoom;