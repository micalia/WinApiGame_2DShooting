#pragma once
class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

	static PlayerRef CreatePlayer();
	static EnemyRef CreateEnemy();
public:
	Protocol::ObjectInfo info;
	GameRoomRef room;

private:
	static atomic<uint64> s_idGenerator;
};

