#include "pch.h"
#include <iostream>
#include <random>
#include "ServerUtils.h"

int ServerUtils::RandomIntegerRange(int min, int max)
{
	// 난수 생성기 초기화
	std::random_device rd;  // 난수 생성기 시드
	std::mt19937 gen(rd());  // Mersenne Twister 엔진 사용

	// 생성할 난수의 범위 설정
	std::uniform_int_distribution<> dis(min, max);  // 균일 분포 설정

	return dis(gen);
}
