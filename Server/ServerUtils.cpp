#include "pch.h"
#include <iostream>
#include <random>
#include "ServerUtils.h"

int ServerUtils::RandomIntegerRange(int min, int max)
{
	// ���� ������ �ʱ�ȭ
	std::random_device rd;  // ���� ������ �õ�
	std::mt19937 gen(rd());  // Mersenne Twister ���� ���

	// ������ ������ ���� ����
	std::uniform_int_distribution<> dis(min, max);  // ���� ���� ����

	return dis(gen);
}
