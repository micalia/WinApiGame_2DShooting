#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "UI.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Enemy.h"
#include "DevScene.h"
#include "EnemyManager.h"
#include "EnemyMissile.h"

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
	if (deltaTime > 0.1f) return;
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

	if (actor->GetLayer() == LAYER_EnemyMissile) {
		EnemyMissile* missile = static_cast<EnemyMissile*>(actor);
		if (DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene()) {
			scene->GetEnemyMgr()->AddMissile(actor->info.objectid(), missile);
		}
	}
	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	if (actor->GetLayer() == LAYER_EnemyMissile) {
		EnemyMissile* missile = static_cast<EnemyMissile*>(actor);
		if (DevScene* scene = GET_SINGLE(SceneManager)->GetDevScene()) {
			scene->GetEnemyMgr()->RemoveMissile(missile->info.objectid());
		}
	}
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

		switch (info.objecttype())
		{
		case Protocol::OBJECT_TYPE_PLAYER:
		{
			Player* player = SpawnActor<Player>(Vec2{ info.posx(), info.posy() }, LAYER_Player);
			player->SetState(info.playerdirtype());
			player->SetName(info.name());
			player->info = info;
		}
			break;
		case Protocol::OBJECT_TYPE_ENEMY:
		{
			auto EnemySpawnMgr = GET_SINGLE(SceneManager)->GetDevScene()->GetEnemyMgr();
			if (EnemySpawnMgr) { 
				if (info.name() == "HalfEnemy") {
					EnemySpawnMgr->HalfEnemySpawn(info);
				}
				else if (info.name() == "WhiteEnemy") {
					EnemySpawnMgr->WhiteEnemySpawn(info);
				}
			}
		}
			break;
		case Protocol::OBJECT_TYPE_ENEMY_MISSILE:
		{
			if (auto EnemyMgr = GET_SINGLE(SceneManager)->GetDevScene()->GetEnemyMgr()) {
				EnemyMgr->EnemyMissileSpawn(info);
			}
		}
			break;
		default:
			break;
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
	{	
		auto missile = GetEnemyMgr()->GetMissileObj(id);
		if(missile !=nullptr)
			return missile;
	}
	for (Actor* actor : _actors[LAYER_EnemyMissile])
	{
		if (actor && actor->info.objectid() == id)
			return actor;
	}
	for (Actor* actor : _actors[LAYER_Enemy])
	{
		if (actor && actor->info.objectid() == id)
			return actor;
	}
	for (Actor* actor : _actors[LAYER_Player])
	{
		if (actor && actor->info.objectid() == id)
			return actor;
	}
	for (Actor* actor : _actors[LAYER_BULLET])
	{
		if (actor && actor->info.objectid() == id)
			return actor;
	}
	for (Actor* actor : _actors[LAYER_OBJECT])
	{
		if (actor && actor->info.objectid() == id)
			return actor;
	}

	return nullptr;
}
