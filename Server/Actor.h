#pragma once

class SCollider;
class SComponent;

class Actor : public enable_shared_from_this<Actor>
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update(){};

	static PlayerRef CreatePlayer();
	static SMissileRef CreatePlayerMissile(uint64 owner, Vector spawnPos);
	static EnemyRef CreateEnemy(Protocol::EnemyType enemyType, Vector spawnPos);
	static EnemyMissileRef CreateEnemyMissile(Vector spawnPos, Vector dir);

	Vector GetPos(){
		return _pos;
	}
	void SetPos(Vector pos){
		info.set_posx(pos.x);
		info.set_posy(pos.y);
		_pos = pos; 
	}

	void SetLayer(SLAYER_TYPE layer) { _layer = layer; }
	SLAYER_TYPE GetLayer() { return _layer; }

	void AddComponent(shared_ptr<SComponent> component);
	void RemoveComponent(shared_ptr<SComponent> component);

	shared_ptr<SCollider> GetCollider();

	virtual void OnComponentBeginOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other);
	virtual void OnComponentEndOverlap(shared_ptr<SCollider> collider, shared_ptr<SCollider> other);

	int64 GetObjectID() { return info.objectid(); }
	void SetObjectID(int64 id) { info.set_objectid(id); }

	void SetOwner(shared_ptr<Actor> owner) { _owner = owner; }
	shared_ptr<Actor> GetOwner() { return _owner; }
public:
	Protocol::ObjectInfo info;
	GameRoomRef room;

	static atomic<uint64> s_idGenerator;
protected:

	SLAYER_TYPE _layer = LAYER_OBJECT;
	vector<shared_ptr<SComponent>> _components;
	Vector _pos = { 0, 0 };

private:
	shared_ptr<Actor> _owner;
};

