#include "pch.h"
#include "GameRoom.h"
#include "Player.h"
#include "GameObject.h"
#include "GameSession.h"
#include "Enemy.h"

GameRoomRef GRoom = make_shared<GameRoom>();

GameRoom::GameRoom()
{

}

GameRoom::~GameRoom()
{

}

void GameRoom::Init()
{
	
}

void GameRoom::Update()
{

}

void GameRoom::EnterRoom(GameSessionRef session)
{
	PlayerRef player = GameObject::CreatePlayer();
	
	// ������ ���縦 ����
	session->gameRoom = GetRoomRef();
	session->player = player;
	player->session = session;

	//TEMP
	player->info.set_posx(242);
	player->info.set_posy(188);
	
	// ������ Ŭ�󿡰� ������ �����ֱ�
	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_MyPlayer(player->info);
		session->Send(sendBuffer);
	}
	// ��� ������Ʈ ���� ����
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
}

void GameRoom::LeaveRoom(GameSessionRef session)
{
	if(session == nullptr)
		return;
	if(session->player.lock() == nullptr)
		return;

	uint64 id = session->player.lock()->info.objectid();
	GameObjectRef gameObject = FindObject(id);
	RemoveObject(id);
}

GameObjectRef GameRoom::FindObject(uint64 id)
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

void GameRoom::AddObject(GameObjectRef gameObject)
{
	uint64 id = gameObject->info.objectid();
	
	auto objectType = gameObject->info.objecttype();

	switch (objectType) 
	{
		case Protocol::OBJECT_TYPE_PLAYER:
			_players[id] = static_pointer_cast<Player>(gameObject);
			break;
		case Protocol::OBJECT_TYPE_ENEMY: 
			_enemies[id] = static_pointer_cast<Enemy>(gameObject);
			break;
		default:
			return;
	}

	gameObject->room = GetRoomRef();
	//TODO �ű� ������Ʈ ����
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
	GameObjectRef gameObject = FindObject(id);
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
	
	// ������Ʈ ���� ����
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
