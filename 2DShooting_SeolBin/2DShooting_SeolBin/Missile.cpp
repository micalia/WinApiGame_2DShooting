#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "DevScene.h"
#include "SceneManager.h"
#include "Sprite.h"

Missile::Missile()
{

}

Missile::~Missile()
{

}

void Missile::BeginPlay()
{
	Super::BeginPlay();


}

void Missile::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	if (deltaTime > 0.1f) return;
	_pos.y -= deltaTime * speed;
	
	//_sprite->SetPos
	//// Ãæµ¹
	//const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	//for (Object* object : objects)
	//{
	//	if (object == this)
	//		continue;

	//	if (object->GetObjectType() != ObjectType::Monster)
	//		continue;

	//	Pos p1 = GetPos();
	//	Pos p2 = object->GetPos();

	//	const float dx = p1.x - p2.x;
	//	const float dy = p1.y - p2.y;
	//	float dist = sqrt(dx * dx + dy * dy);

	//	if (dist < 25)
	//	{
	//		GET_SINGLE(ObjectManager)->Remove(object); // ±¦ÂúÀ»..±î?
	//		GET_SINGLE(ObjectManager)->Remove(this); // ±¦ÂúÀ»..±î?
	//		return;
	//	}
	//}

	//// TODO
	//if (_pos.y < -100)
	//{
	//	GET_SINGLE(ObjectManager)->Remove(this);
	//	return;
	//}
}

void Missile::Render(HDC hdc)
{
	Super::Render(hdc);
}