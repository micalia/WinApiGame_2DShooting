#pragma once

class Actor;

class ActorManager
{
public:
	DECLARE_SINGLE(ActorManager);

	~ActorManager();

	void Add(Actor* object);
	void Remove(Actor* object);
	void Clear();

	const vector<Actor*>& GetObjects() { return _objects; }

	template<typename T>
	T* CreateObject()
	{
		// type trait
		static_assert(std::is_convertible_v<T*, Object*>);

		T* object = new T();
		object->Init();

		return object;
	}


private:
	vector<Object*> _objects;
};

