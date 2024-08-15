#pragma once

#include "CorePch.h"

using GameSessionRef = shared_ptr<class GameSession>;
using GameRoomRef = shared_ptr<class GameRoom>;
using ActorRef = shared_ptr<class Actor>;
using PlayerRef = shared_ptr<class Player>;
using EnemyRef = shared_ptr<class Enemy>;

#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

#include "ServerPacketHandler.h"