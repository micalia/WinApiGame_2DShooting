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
	T* SpawnActor(Vec2 pos)
	{
		auto isGameObject = std::is_convertible_v<T*, Actor*>;
		assert(isGameObject);

		T* ret = new T();
		AddActor(ret);

		ret->BeginPlay();

		return ret;
	}

	void Handle_S_AddObject(Protocol::S_AddObject& pkt);
	void Handle_S_RemoveObject(Protocol::S_RemoveObject& pkt);

	GameObject* GetObject(uint64 id);
public:
	vector<Actor*> _actors[LAYER_MAXCOUNT];
	vector<UI*> _uis;
};

