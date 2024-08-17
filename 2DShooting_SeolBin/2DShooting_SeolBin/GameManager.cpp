#include "pch.h"
#include "GameManager.h"

void GameManager::Init()
{

}

void GameManager::Update()
{

}

void GameManager::Render(HDC hdc)
{
	HFONT hFont = CreateFont(23, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("�������"));
	// ���� ������ ��Ʈ�� DC�� ����
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
	{
		wstring str = std::format(L"Blue Score: {0}", GetBluePlayerScore());
		::TextOut(hdc, 30, 30, str.c_str(), static_cast<int32>(str.size()));
	}
	{
		wstring str = std::format(L"Red Score: {0}", GetBluePlayerScore());
		::TextOut(hdc, 300, 30, str.c_str(), static_cast<int32>(str.size()));
	}

	//// ���� ��Ʈ�� ����
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont); // ������ ��Ʈ ����

}

void GameManager::AddScore(string playerName, int addScore)
{
	if (playerName == "BluePlayer") {
		bluePlayerScore += addScore;
	}
	else if (playerName == "RedPlayer") {
		redPlayerScore += addScore;
	}
}
