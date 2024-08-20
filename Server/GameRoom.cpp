#include "pch.h"
#include "GameRoom.h"
#include "Player.h"
#include "Actor.h"
#include "GameSession.h"
#include "Enemy.h"
#include "ServerEnemySpawnMgr.h"
#include "SeverTimeManager.h"

GameRoomRef GRoom = make_shared<GameRoom>();

GameRoom::GameRoom()
{

}

GameRoom::~GameRoom()
{

}

void GameRoom::Init()
{
	enemyMgr = make_shared<ServerEnemySpawnMgr>();
	GET_SINGLE(SeverTimeManager)->Init();
}

void GameRoom::Update()
{
	//if (currUserCount == 2) {
	GET_SINGLE(SeverTimeManager)->Update();
		enemyMgr->Update();
	//}
}

void GameRoom::EnterRoom(GameSessionRef session)
{
	PlayerRef player = Actor::CreatePlayer();
	
	// 서로의 존재를 연결
	session->gameRoom = GetRoomRef();
	session->player = player;
	player->session = session;
	
	// 첫번째 입장은 무조건 BluePlayer
	if (_players.size() == 0) {
		player->info.set_name("BluePlayer");
	}
	else {
		for (auto it = _players.begin(); it != _players.end(); it ++)
		{
			if (it->second->name == "BluePlayer") {
				player->info.set_name("RedPlayer");
				break;
			}
			else if (it->second->name == "RedPlayer") {
				player->info.set_name("BluePlayer");
				break;
			}
		}
	}

	//TEMP
	player->info.set_posx(242);
	player->info.set_posy(540);
	

	// 입장한 클라에게 정보를 보내주기
	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_MyPlayer(player->info);
		session->Send(sendBuffer);
	}
	// 모든 오브젝트 정보 전송
	{
		Protocol::S_AddObject pkt;

		for (auto& item : _players)
		{
			Protocol::ObjectInfo* info = pkt.add_objects();
			*info = item.second->info;
		}

		for (auto& item : _enemies)
		{
			Protocol::ObjectInfo* info = pkt.add_objects();
			*info = item.second->info;
		}

		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_AddObject(pkt);
		session->Send(sendBuffer);
	}

	AddObject(player);
	++currUserCount;
}

void GameRoom::LeaveRoom(GameSessionRef session)
{
	if(session == nullptr)
		return;
	if(session->player.lock() == nullptr)
		return;

	uint64 id = session->player.lock()->info.objectid();
	ActorRef gameObject = FindObject(id);
	RemoveObject(id);
	--currUserCount;
}

ActorRef GameRoom::FindObject(uint64 id)
{
	{
		auto findIt = _players.find(id);
		if(findIt != _players.end())
			return findIt->second;
	}
	{
		auto findIt = _enemies.find(id);
		if(findIt != _enemies.end())
			return findIt->second;
	}

	return nullptr;
}

void GameRoom::Handle_C_Move(Protocol::C_Move& pkt)
{
	uint64 id = pkt.info().objectid();
	ActorRef gameObject = FindObject(id);
	if (gameObject == nullptr)
		return;

	// TODO : Validation
	gameObject->info.set_playerdirtype(pkt.info().playerdirtype());
	gameObject->info.set_posx(pkt.info().posx());
	gameObject->info.set_posy(pkt.info().posy());

	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_Move(pkt.info());
		Broadcast(sendBuffer);
	}
}

void GameRoom::Handle_C_Projectile(Protocol::C_Projectile& pkt)
{
	uint64 id = pkt.info().objectid();
	ActorRef gameObject = FindObject(id);
	if (gameObject == nullptr)
		return;

	// TODO : Validation

	gameObject->info.set_name(pkt.info().name());
	gameObject->info.set_objecttype(pkt.info().objecttype());
	gameObject->info.set_posx(pkt.info().posx());
	gameObject->info.set_posy(pkt.info().posy());

	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_Projectile(pkt.info());
		Broadcast(sendBuffer);
	}
}

void GameRoom::Handle_C_Score(Protocol::C_Score& pkt)
{
	// TODO : Validation
	scoreInfo.set_playername(pkt.scoreinfo().playername());
	if (pkt.scoreinfo().playername() == "RedPlayer") {
		SetRedPlayerScore(pkt.scoreinfo().enemyscore());
		scoreInfo.set_fullscore(GetRedPlayerScore());
	}
	else if (pkt.scoreinfo().playername() == "BluePlayer") {
		SetBluePlayerScore(pkt.scoreinfo().enemyscore());
		scoreInfo.set_fullscore(GetBluePlayerScore());
	}

	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_Score(scoreInfo);
		Broadcast(sendBuffer);
	}
}

void GameRoom::AddObject(ActorRef gameObject)
{
	uint64 id = gameObject->info.objectid();
	
	auto objectType = gameObject->info.objecttype();

	switch (objectType) 
	{
	case Protocol::OBJECT_TYPE_PLAYER: 
			{
				string playerName;
				if (_players.size() == 0) {
					gameObject->info.set_name("BluePlayer");
					playerName = "BluePlayer";
				}
				else {
					for (auto it = _players.begin(); it != _players.end(); it++)
					{
						if (it->second->name == "BluePlayer") {
							gameObject->info.set_name("RedPlayer");
							playerName = "RedPlayer";
							break;
						}
						else if (it->second->name == "RedPlayer") {
							gameObject->info.set_name("BluePlayer");
							playerName = "BluePlayer";
							break;
						}
					}
				}
				_players[id] = static_pointer_cast<Player>(gameObject);
				_players[id]->name = playerName;
			}
			break;
		case Protocol::OBJECT_TYPE_ENEMY: 
			_enemies[id] = static_pointer_cast<Enemy>(gameObject);
			break;
		default:
			return;
	}

	gameObject->room = GetRoomRef();
	//TODO 신규 오브젝트 전송
	{
		Protocol::S_AddObject pkt;
		Protocol::ObjectInfo* info = pkt.add_objects();
		*info = gameObject->info;

		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_AddObject(pkt);
		Broadcast(sendBuffer);
	}
}

void GameRoom::RemoveObject(uint64 id)
{
	ActorRef gameObject = FindObject(id);
	if(gameObject == nullptr)
		return;

	switch (gameObject->info.objecttype())
	{
	case Protocol::OBJECT_TYPE_PLAYER:
		_players.erase(id);
		break;
	case Protocol::OBJECT_TYPE_ENEMY:
		_enemies.erase(id);
		break;
	default:
		return;
	}

	gameObject->room = nullptr;
	
	// 오브젝트 삭제 전송
	{
		Protocol::S_RemoveObject pkt;
		pkt.add_ids(id);

		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_RemoveObject(pkt);
		Broadcast(sendBuffer);
	}
}

void GameRoom::Broadcast(SendBufferRef& sendBuffer)
{
	for (auto& item : _players)
	{
		item.second->session->Send(sendBuffer);
	}
}
