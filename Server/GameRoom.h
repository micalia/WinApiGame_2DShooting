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
	void Handle_C_Score(Protocol::C_Score& pkt);

	void AddObject(ActorRef gameObject);
	void RemoveObject(uint64 id);

	void ScoreCalculate(string playerName, int addScore);
	void Broadcast(SendBufferRef& sendBuffer);

	int GetBluePlayerScore(){return _bluePlayerScore;}
	int GetRedPlayerScore(){return _redPlayerScore;}

	void SetBluePlayerScore(int addScore) {  _bluePlayerScore += addScore; }
	void SetRedPlayerScore(int addScore) { _redPlayerScore += addScore; }

	map<uint64, PlayerRef> GetPlayerArr(){return _players;}

	Vector GetRespawnEndPos() { return respawnEndPos; }
	Vector GetRespawnStartPos() { return respawnStartPos; }
private:
	EnemySpawnMgrRef enemyMgr;

private:
	map<uint64, PlayerRef> _players;
	map<uint64, EnemyRef> _enemies;
	unordered_map<uint64, ActorRef> _objects;

private:
	Protocol::ScoreInfo scoreInfo;

	int _redPlayerScore = 0;
	int _bluePlayerScore = 0;

	int currUserCount = 0;

private:
	Vector respawnEndPos = Vector(242, 540);
	Vector respawnStartPos = Vector(242, 1088);
};

extern GameRoomRef GRoom;