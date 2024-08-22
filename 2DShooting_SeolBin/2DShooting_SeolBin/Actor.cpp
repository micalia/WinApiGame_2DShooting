#include "pch.h"
#include "Actor.h"
#include "Component.h"
#include "Collider.h"

Actor::Actor()
{

}

Actor::~Actor()
{
	for (Component* component : _components)
		SAFE_DELETE(component);
}

void Actor::BeginPlay()
{
	for (Component* component : _components)
	{
		component->BeginPlay();
	}
}

void Actor::Tick(float deltaTime)
{
	if (deltaTime > 0.1f) return;
	_dirtyFlag = false;

	for (Component* component : _components)
	{
		component->TickComponent();
	}
}

void Actor::Render(HDC hdc)
{
	for (Component* component : _components)
	{
		component->Render(hdc);
	}
}

void Actor::SetPos(Vec2 pos)
{
	_pos = Vec2(pos);
	info.set_posx(pos.x);
	info.set_posy(pos.y);
}

Vec2 Actor::GetPos()
{
	//return Vec2{info.posx(), info.posy()};
	return _pos;
}

void Actor::AddComponent(Component* component)
{
	if (component == nullptr)
		return;

	component->SetOwner(this);
	_components.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	auto findIt = std::find(_components.begin(), _components.end(), component);
	if (findIt == _components.end())
		return;

	_components.erase(findIt);
}

Collider* Actor::GetCollider()
{
	for (Component* component : _components)
	{
		if (auto actorCollider = dynamic_cast<Collider*>(component))
			return actorCollider;
	}

	return nullptr;
}

void Actor::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

}

void Actor::OnComponentEndOverlap(Collider* collider, Collider* other)
{

}
