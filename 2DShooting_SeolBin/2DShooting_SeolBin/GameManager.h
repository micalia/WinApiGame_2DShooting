#pragma once
class GameManager
{
	DECLARE_SINGLE(GameManager)

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void SetScore(string playerName, int setScore);
	int GetBluePlayerScore(){return bluePlayerScore; }
	int GetRedPlayerScore(){return redPlayerScore; }
private:
	int bluePlayerScore = 0;
	int redPlayerScore = 0;
};

