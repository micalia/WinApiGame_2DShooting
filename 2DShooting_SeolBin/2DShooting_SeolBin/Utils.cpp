#include "pch.h"
#include "Utils.h"
#include <iostream>
#include <random>

void Utils::DrawText(HDC hdc, Pos pos, const wstring& str)
{
	::TextOut(hdc, static_cast<int32>(pos.x), static_cast<int32>(pos.y), str.c_str(), static_cast<int32>(str.size()));
}

void Utils::DrawRect(HDC hdc, Pos pos, int32 w, int32 h)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - w / 2), static_cast<int32>(pos.y - h / 2), static_cast<int32>(pos.x + w / 2), static_cast<int32>(pos.y + h / 2));
}

void Utils::DrawCircle(HDC hdc, Pos pos, int32 radius)
{
	::Ellipse(hdc, static_cast<int32>(pos.x - radius), static_cast<int32>(pos.y - radius), static_cast<int32>(pos.x + radius), static_cast<int32>(pos.y + radius));
}

void Utils::DrawLine(HDC hdc, Pos from, Pos to)
{
	::MoveToEx(hdc, static_cast<int32>(from.x), static_cast<int32>(from.y), nullptr);
	::LineTo(hdc, static_cast<int32>(to.x), static_cast<int32>(to.y));
}

int Utils::RandomIntegerRange(int min, int max)
{
	// 난수 생성기 초기화
	std::random_device rd;  // 난수 생성기 시드
	std::mt19937 gen(rd());  // Mersenne Twister 엔진 사용

	// 생성할 난수의 범위 설정
	std::uniform_int_distribution<> dis(min, max);  // 균일 분포 설정

	return dis(gen);
}
