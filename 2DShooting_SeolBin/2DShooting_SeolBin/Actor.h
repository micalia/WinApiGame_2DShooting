#pragma once

#include "Enum.pb.h"
using PlayerDir = Protocol::PLAYER_DIR_TYPE;

#define PD_IDLE Protocol::PLAYER_DIR_TYPE_IDLE
#define PD_LEFT Protocol::PLAYER_DIR_TYPE_LEFT
#define PD_RIGHT Protocol::PLAYER_DIR_TYPE_RIGHT

class Component;
class Collider;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render(HDC hdc);

	//액터의 정중앙
	void SetPos(Vec2 pos);
	Vec2 GetPos();

	void SetLayer(LAYER_TYPE layer) { _layer = layer; }
	LAYER_TYPE GetLayer() { return _layer; }

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	Component* GetCollider();

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

	int64 GetObjectID() { return info.objectid(); }
	void SetObjectID(int64 id){info.set_objectid(id); }

	virtual void SetState(PlayerDir InDir){};
protected:
	Vec2 _pos = { 0, 0 };
	Vec2 _destPos = { 0, 0 };
	LAYER_TYPE _layer = LAYER_OBJECT;
	vector<Component*> _components;

	bool _dirtyFlag = false;
public:
	Protocol::ObjectInfo info;

	void SetNetRecvPos(Vec2 netRecvPos) { _netRecvPos = netRecvPos; }
	Vec2 GetNetRecvPos() { return _netRecvPos; }
	void SetPrevRecvPos(Vec2 prevRecvPos) { _prevRecvPos = prevRecvPos; }
	Vec2 GetPrevRecvPos() { return _prevRecvPos; }
private:
	Vec2 _netRecvPos = { 0, 0 };
	Vec2 _prevRecvPos = { 0, 0 };
};

