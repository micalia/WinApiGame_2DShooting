#pragma once
class Actor : public enable_shared_from_this<Actor>
{
public:
	Actor();
	virtual ~Actor();

	static PlayerRef CreatePlayer();
	static EnemyRef CreateEnemy();
public:
	Protocol::ObjectInfo info;
	GameRoomRef room;

private:
	static atomic<uint64> s_idGenerator;
};
