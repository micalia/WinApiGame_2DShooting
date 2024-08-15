#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "UI.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Enemy.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			SAFE_DELETE(actor);

	_actors->clear();

	for (UI* ui : _uis)
		SAFE_DELETE(ui);

	_uis.clear();
}

void Scene::Init()
{
	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->BeginPlay();

	for (UI* ui : _uis)
		ui->BeginPlay();
}

void Scene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	GET_SINGLE(CollisionManager)->Update();

	//// 거리 = 시간 * 속도
	for (const vector<Actor*> actors : _actors)
		for (Actor* actor : actors)
			actor->Tick(deltaTime);

	//for (UI* ui : _uis)
	//	ui->Tick();
}

void Scene::Render(HDC hdc)
{
	vector<Actor*>& actors = _actors[LAYER_OBJECT];
	std::sort(actors.begin(), actors.end(), [=](Actor* a, Actor* b) 
		{
			return a->GetPos().y < b->GetPos().y;
		});

	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Render(hdc);
	
	/*for (UI* ui : _uis)
		ui->Render(hdc);*/
}

void Scene::AddActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	vector<Actor*>& v = _actors[actor->GetLayer()];
	v.erase(std::remove(v.begin(), v.end(), actor), v.end());
}

void Scene::Handle_S_AddObject(Protocol::S_AddObject& pkt)
{
	uint64 myPlayerId = GET_SINGLE(SceneManager)->GetMyPlayerId();

	const int32 size = pkt.objects_size();
	for (int32 i = 0; i < size; i++)
	{
		const Protocol::ObjectInfo& info = pkt.objects(i);
		if (myPlayerId == info.objectid())
			continue;

		if (info.objecttype() == Protocol::OBJECT_TYPE_PLAYER)
		{
			Player* player = SpawnActor<Player>(Vec2{ info.posx(), info.posy() });
			player->SetState(info.playerdirtype());
			player->SetName(info.name());
			player->info = info;
		}
		else if (info.objecttype() == Protocol::OBJECT_TYPE_ENEMY)
		{
			Enemy* enemy = SpawnActor<Enemy>(Vec2{ info.posx(), info.posy() });
			enemy->info = info;
		}
	}
}

void Scene::Handle_S_RemoveObject(Protocol::S_RemoveObject& pkt)
{
	const int32 size = pkt.ids_size();
	for (int32 i = 0; i < size; i++)
	{
		int32 id = pkt.ids(i);

		Actor* object = GetObject(id);
		if (object)
			RemoveActor(object);
	}
}

Actor* Scene::GetObject(uint64 id)
{
	for (Actor* actor : _actors[LAYER_OBJECT])
	{
		if (actor && actor->info.objectid() == id)
			return actor;
	}

	return nullptr;
}
