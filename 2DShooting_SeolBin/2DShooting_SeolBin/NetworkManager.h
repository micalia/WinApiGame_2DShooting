#pragma once
//네트워크를 연결하고, 관련된 세션들을 저장하는 역할

using ServerSessionRef = shared_ptr<class ServerSession>;

class NetworkManager
{
	DECLARE_SINGLE(NetworkManager)
public:
	void Init();
	void Update();

	ServerSessionRef CreateSession();
	void SendPacket(SendBufferRef sendBuffer);

private:
	ClientServiceRef _service;
	ServerSessionRef _session;
};

