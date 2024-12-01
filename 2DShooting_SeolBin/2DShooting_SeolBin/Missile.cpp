#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "DevScene.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "Component.h"

Missile::Missile()
{

}

Missile::~Missile()
{

}

void Missile::BeginPlay()
{
	Super::BeginPlay();

	startPos = GetPos();
}

void Missile::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	return;
	ClientTimeSinceUpdate += deltaTime;
	if (ClientTimeBetweenLastUpdate < UE_KINDA_SMALL_NUMBER)
	{
		return;
	}
	const Vec2 EstimateLocation = GetServerNewLocation() + (Vec2(0, -1) * ClientTimeBetweenLastUpdate);
	const float LerpRatio = ClientTimeSinceUpdate / ClientTimeBetweenLastUpdate;

	float ClientNewX = lerp(GetServerNewLocation().x, EstimateLocation.x, LerpRatio);
	float ClientNewY = lerp(GetServerNewLocation().y, EstimateLocation.y, LerpRatio);
	const Vec2 ClientNewLoc = Vec2(ClientNewX, ClientNewY);
	SetPos(ClientNewLoc);

	/*if (deltaTime > 0.1f) return;
	_pos.y -= deltaTime * speed;
	SetPos(_pos);*/
	
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