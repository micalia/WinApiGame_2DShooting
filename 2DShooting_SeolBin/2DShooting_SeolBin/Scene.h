#pragma once

class GameObject;
class Actor;
class UI;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	template<typename T>
	T* SpawnActor(Vec2 pos, LAYER_TYPE layerType = LAYER_OBJECT)
	{
		auto isGameObject = std::is_convertible_v<T*, Actor*>;
		assert(isGameObject);

		T* ret = new T();
		ret->SetLayer(layerType);
		AddActor(ret);

		ret->SetPos(pos);
		ret->BeginPlay();

		return ret;
	}

	void Handle_S_AddObject(Protocol::S_AddObject& pkt);
	void Handle_S_RemoveObject(Protocol::S_RemoveObject& pkt);

	Actor* GetObject(uint64 id);
public:
	vector<Actor*> _actors[LAYER_MAXCOUNT];
	vector<UI*> _uis;
};

