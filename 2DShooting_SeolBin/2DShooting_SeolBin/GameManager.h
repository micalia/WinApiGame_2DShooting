#pragma once
class GameManager
{
	DECLARE_SINGLE(GameManager)

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void AddScore(string playerName, int addScore);
	int GetBluePlayerScore(){return bluePlayerScore; }
	int GetRedPlayerScore(){return redPlayerScore; }
private:
	int bluePlayerScore = 0;
	int redPlayerScore = 0;
};

