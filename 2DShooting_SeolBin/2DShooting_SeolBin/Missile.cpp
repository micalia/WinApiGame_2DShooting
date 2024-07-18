#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "DevScene.h"
#include "SceneManager.h"

Missile::Missile()
{
	FB_BlueMissile = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BlueMissile");

	//BeginPlay();
}

Missile::~Missile()
{

}

void Missile::BeginPlay()
{
	Super::BeginPlay();
	SetCellPos({ 5, 5 }, true);
	SetFlipbook(FB_BlueMissile);
}

void Missile::Tick()
{
	Super::Tick();
	return;
	Pos p1 = GetPos();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f) return;
	_pos.y -= deltaTime * speed;

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
	Utils::DrawCircle(hdc, _pos, 5);
}

void Missile::SetCellPos(Vec2Int cellPos, bool teleport /*= false*/)
{
	_cellPos = cellPos;

	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	_destPos = scene->ConvertPos(cellPos);

	if (teleport)
		_pos = _destPos;
}
